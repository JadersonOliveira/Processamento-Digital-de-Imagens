#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printmask(Mat &m)
{
    for (int i = 0; i < m.size().height; i++)
    {
        for (int j = 0; j < m.size().width; j++)
        {
            cout << m.at<float>(i, j) << ",";
        }
        cout << "\n";
    }
}

int main(int, char **)
{
	//Definição de um objeto(cap) da classe VideoCapture para captura de vídeo
    VideoCapture cap;
	
	//Definição das máscaras
    float media[] = { 0.1111, 0.1111, 0.1111, 
					  0.1111, 0.1111, 0.1111,
					  0.1111, 0.1111, 0.1111};
					
    float gauss[] = { 0.0625, 0.125,  0.0625, 
					  0.125, 0.25, 0.125,
					  0.0625, 0.125,  0.0625};
							
    float horizontal[] = { -1, 0, 1,
						   -2, 0, 2,
						   -1, 0, 1};
	
    float vertical[] = { -1, -2, -1,
						  0, 0, 0,
						  1, 2, 1};
	
    float laplacian[] = { 0, -1, 0,
						 -1, 4, -1,
						  0, -1, 0};
	
    float boost[] = { 0, -1, 0,
					 -1, 5.2, -1,
					  0, -1, 0};
						   
	/* Máscara 5x5 encontrada em pesquisas na internet
	fonte: http://www.ic.uff.br/~aconci/gabor.pdf */
	float laplgauss[]={ 0, -1, -2, -1,  0,
					   -1,  0,  2,  0, -1,
					   -2,  2,  8,  2, -2,
					   -1,  0,  2,  0, -1,
						0, -1, -2, -1,  0};

	//Definição de objetos da classe Mat para armazenamento das imagens
    Mat frame, framegray, frame32f, frameFiltered;
    Mat result;
	
	//Definição de uma matriz 3x3 que será usada como máscara de filtragem
	Mat mask(3, 3, CV_32F);
    
	//Definição das variáveis para armazenar a largura, altura, valor de tecla
    double width, height;
    int absolut;
    char key;

	//Uso do método .open() para conexão do dispositivo de captura de vídeo de acordo com o identificador
    cap.open(0);

	//Caso a conexão do dispositivo de vídeo não seja realizada, apresente a mensagem de erro
    if (!cap.isOpened())
	{
		cout << "cameras indisponiveis";
		return -1;
	}
        
	//Uso do método .set() para atribuir tamanho aos quadros capturados pela câmera
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	
	//Leitura da largura e altura dos quadros disponibilizados pelo dispositivo
    width = cap.get(CAP_PROP_FRAME_WIDTH);
    height = cap.get(CAP_PROP_FRAME_HEIGHT);
	
	//Impressões na tela
    cout << "largura=" << width << "\n";
    cout << "altura =" << height << "\n";
    cout << "fps    =" << cap.get(CAP_PROP_FPS) << "\n";
    cout << "format =" << cap.get(CAP_PROP_FORMAT) << "\n";

	//Definição da função namedWindow() para criação de uma janela auto-ajustável
    namedWindow("filtroespacial", cv::WINDOW_NORMAL);
    namedWindow("original", cv::WINDOW_NORMAL);

    mask = Mat(3, 3, CV_32F, media);

    absolut = 1;

    for (;;)
    {
        cap >> frame;  //Captura de um novo frame
        cvtColor(frame, framegray, COLOR_BGR2GRAY);	//Muda o formato de cor da imagem para COLOR_BGR2GRAY
        flip(framegray, framegray, 1);	//Uso da função flip() para inversão horizontal da imagem
        imshow("original", framegray);	//Definição da função imshow() para exibir a imagem
        
		//Conversão do frame para ponto flutuante(frame32f)
		framegray.convertTo(frame32f, CV_32F);
        
		//Uso da função filter2d() para fazer os cálculos da filtragem
		filter2D(frame32f, frameFiltered, frame32f.depth(), mask,
                 Point(1, 1), 0);
		
		//Verifica o status de absolut, se ok, o cálculo é precedido
        if (absolut)
        {
            frameFiltered = abs(frameFiltered);
        }
		
		//Filtragem da imagem para tons de cinza
        frameFiltered.convertTo(result, CV_8U);

		//Definição da função imshow() para exibir a imagem
        imshow("filtroespacial", result);
		
		//Espera o uso da tecla ESC para encerrar o programa
        key = (char)waitKey(10);
        if (key == 27) break;
		
		//Switch() para escolha dos filtros
        switch (key)
        {
        case 'a':
            absolut = !absolut;
            break;
        case 'm':	// média
            mask = Mat(3, 3, CV_32F, media);
            printmask(mask);
            break;
        case 'g':	// gaussiano 
            mask = Mat(3, 3, CV_32F, gauss);
            printmask(mask);
            break;
        case 'h':	// detector de bordas horizontais
            mask = Mat(3, 3, CV_32F, horizontal);
            printmask(mask);
            break;
        case 'v':	// detector de bordas verticais
            mask = Mat(3, 3, CV_32F, vertical);
            printmask(mask);
            break;
        case 'l':	// laplaciano
            mask = Mat(3, 3, CV_32F, laplacian);
            printmask(mask);
            break;
        case 'b': // boost
            mask = Mat(3, 3, CV_32F, boost);
			printmask(mask);
            break;
		case 'p': // laplaciano do gaussiano
            mask = Mat(5, 5, CV_32F, laplgauss);
			printmask(mask);
            break;	
        default:
            break;
        }
    }
    return 0;
}
