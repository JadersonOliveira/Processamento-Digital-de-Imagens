#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    //Definição de objetos da classe Mat para armazenamento das imagens
	Mat image;	
    Mat lastHist;
	Mat histR;
	
	//Definição das variáveis para armazenar a largura e altura da imagem
	int width, height;	
	
	//Definição de um objeto(cap) da classe VideoCapture para captura de vídeo
    VideoCapture cap;
    
    //Definição da variável de correlação
    double correlacao;
	
	//Variável para receber valor da tecla
    int key;
	
	//Definição dos componentes de cor do histograma em matrizes independentes no vetor planes
    vector<Mat> planes;
	
	//Definição da variável de tolerância
    double tolerancia = 0.995;
	
	
    bool uniform = true;
    bool acummulate = false;
    int nbins = 64;	//Definição do tamanho de vetor utilizado para armazenamento dos histogramas
    float range[] = {0, 256};	//Definição da faixa de tons de cinza
    const float *histrange = { range };	//Definição da faixa de valores presentes na imagem cujo histograma será calculado

	//Uso do método .open() para conexão do dispositivo de captura de vídeo de acordo com o identificador
    cap.open(0);

	//Caso a conexão do dispositivo de vídeo não seja realizada, apresente a mensagem de erro
    if(!cap.isOpened())
    {
        cout << "cameras indisponiveis";
        return -1;
    }

	//Uso do método .set() para atribuir tamanho aos quadros capturados pela câmera
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	
	//Leitura da largura e altura dos quadros disponibilizados pelo dispositivo
    width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	//Impressão da lagura e altura
    cout << "largura = " << width << endl;
    cout << "altura  = " << height << endl;

	//Definição da largura e altura das imagens que serão usadas para desenhar os histogramas
    int histw = nbins, histh = nbins/2;

    //Captura da imagem
	cap >> lastHist;
	
	//Uso da função split() para separação dos planos de cor
    split (lastHist, planes);	
    
	//Cálculo do histograma para componente de cor
	calcHist(&planes[0], 1, 0, Mat(), lastHist, 1,
             &nbins, &histrange,
             uniform, acummulate);
    
	//Normalização do histograma para uma faixa de valores
	normalize(lastHist, lastHist, 0, 1, NORM_MINMAX, -1, Mat());

	//Definição do valor de normalização
    correlacao = 1;

    while(1)
    {
        //Captura da imagem
		cap >> image;
		
		//Uso da função split() para separação dos planos de cor
        split (image, planes);	
        
		//Cálculo do histograma para componente de cor
		calcHist(&planes[0], 1, 0, Mat(), histR, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
        
		//Normalização do histograma para uma faixa de valores
		normalize(histR, histR, 0, 1, NORM_MINMAX, -1, Mat());

		//Definição do valor de normalização baseado na comparação entre os histogramas 
        correlacao = compareHist(histR, lastHist, CV_COMP_CORREL);
        
		//Cria uma cópia do histograma 
		lastHist = histR.clone();

		//Definição da string para exibir na imagem
        string resultado = "Correlacao: " + to_string(correlacao);

        //Uso da função putText() para inserir a string na imagem
        putText(image, resultado, cvPoint(10,30),
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,255,239), 1, CV_AA);
		
		//Verifica se a correlação é menor que a tolerância, se sim, gera alerta na tela com um texto
        if (correlacao < tolerancia)
        {
            putText(image, "Alteracao Detectada!", cvPoint(10,55),
                    FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,255), 1, CV_AA);
        }

		//Definição da função imshow() para exibir a imagem
        imshow("Imagem", image);

		//Espera o uso da tecla SPACE para encerrar o programa
        key = waitKey(32);
        if(key == 32) break;
    }
	
    return 0;
}
