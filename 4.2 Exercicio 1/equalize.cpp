#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//Definição de objetos da classe Mat para armazenamento das imagens
    Mat image, image_Equa;
	
	//Definição das variáveis para armazenar a largura e altura da imagem
    int width, height;
	
	//Definição de um objeto(cap) da classe VideoCapture para captura de vídeo
    VideoCapture cap;
	
	//Definição dos componentes de cor do histograma em matrizes independentes nos vetores planes e planesEqua
    vector<Mat> planes, planesEqua;
	
	//Definição de objetos da classe Mat para armazenamento dos histogramas de suas respectivas cores
    Mat histR, histG, histB;
	
	//Definição do tamanho de vetor utilizado para armazenamento dos histogramas
    int nbins = 64;
	
	//Definição da faixa de tons de cinza
    float range[] = {0, 255};
	
	//Definição da faixa de valores presentes na imagem cujo histograma será calculado
    const float *histrange = { range };
	
	
    bool uniform = true;
    bool acummulate = false;
	
	//Variável para receber valor da tecla
    int key;

	//Uso do método .open() para conexão do dispositivo de captura de vídeo de acordo com o identificador
    cap.open(0);

	//Caso a conexão do dispositivo de vídeo não seja realizada, apresente a mensagem de erro
    if(!cap.isOpened())
    {
        cout << "cameras indisponiveis";
        return -1;
    }

	//Uso do método .set() para atribuir tamanho aos quadros capturados pela câmera
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	
	//Leitura da largura e altura dos quadros disponibilizados pelo dispositivo
    width = cap.get(CAP_PROP_FRAME_WIDTH);
    height = cap.get(CAP_PROP_FRAME_HEIGHT);
	
	//Impressão da lagura e altura
    cout << "largura = " << width << endl;
    cout << "altura  = " << height << endl;

	//Definição da largura e altura das imagens que serão usadas para desenhar os histogramas
    int histw = nbins, histh = nbins/2;
    Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
    Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
    Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));

    while(1)
    {
		
        cap >> image;	//Captura da imagem
        flip(image, image, 1);	//Uso da função flip() para inversão horizontal da imagem

        cvtColor(image, image_Equa, CV_BGR2GRAY);	//Muda o formato de cor da imagem para YCrCb
        split(image_Equa, planesEqua);	//Uso da função split() para separação dos planos de cor
        equalizeHist(planesEqua[0], planesEqua[0]);	//Equaliza histograma para o primeiro canal Y
        merge(planesEqua, image_Equa);	//Usa a função merge() para juntar os planos

        split(image, planes);	//Uso da função split() para separação dos planos de cor
		
		//Cálculo dos histogramas para cada componente de cor
        calcHist(&planes[0], 1, 0, Mat(), histR, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
        calcHist(&planes[1], 1, 0, Mat(), histG, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
        calcHist(&planes[2], 1, 0, Mat(), histB, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

		//Normalização dos histogramas para uma faixa de valores
        normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
        normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
        normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());

        //Geração das imagens com os desenhos dos histogramas, geradas inicialmente com 0(cor preta)
		histImgR.setTo(Scalar(0));
        histImgG.setTo(Scalar(0));
        histImgB.setTo(Scalar(0));

		//Desenho dos histogramas na forma de um gráfico de barras usando a função line()
        for(int i=0; i<nbins; i++)
        {
            line(histImgR,
                 Point(i, histh),
                 Point(i, histh-cvRound(histR.at<float>(i))),
                 Scalar(0, 0, 255), 1, 8, 0);
            line(histImgG,
                 Point(i, histh),
                 Point(i, histh-cvRound(histG.at<float>(i))),
                 Scalar(0, 255, 0), 1, 8, 0);
            line(histImgB,
                 Point(i, histh),
                 Point(i, histh-cvRound(histB.at<float>(i))),
                 Scalar(255, 0, 0), 1, 8, 0);
        }
		
		//Copia das imagens dos histogramas para a imagem capturada na câmera
        histImgR.copyTo(image(Rect(0, 0,nbins, histh)));
        histImgG.copyTo(image(Rect(0, histh,nbins, histh)));
        histImgB.copyTo(image(Rect(0, 2*histh,nbins, histh)));

		//Definição da função namedWindow() para criação de uma janela auto-ajustável
        namedWindow("Imagem Original", CV_WINDOW_AUTOSIZE);
        namedWindow("Imagem Equalizada", CV_WINDOW_AUTOSIZE);

		//Definição da função imshow() para exibir as imagens
        imshow("Imagem Original", image);
        imshow("Imagem Equalizada", image_Equa);

		//Espera o uso da tecla SPACE para encerrar o programa
        key = waitKey(32);  //CEP 32 ==  SPACE
        if(key == 32) break;
    }
	
    return 0;
}
