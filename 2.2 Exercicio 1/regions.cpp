#include <iostream>
#include <opencv2/opencv.hpp>	//Definição da biblioteca para uso das funcionalidades

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image;	//Definição de um objeto(image) da classe Mat para armazenamento da imagem

	//Definições das coordenadas dos pontos P1 e P2
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;

    /* Definição da função imread() para leitura de uma imagem 
	e o formato que a imagem será interpretada */
	image = imread("biel.png", IMREAD_GRAYSCALE);	
   
	// caso a imagem não seja aberta, apresente a mensagem de erro
	if(!image.data)
    {
        cout << "nao abriu a imagem!" << endl;
    }
	
	//Definição da função para criação de uma janela auto-ajustável
    namedWindow("image", WINDOW_AUTOSIZE);

	//Leitura das coordenadas dos pontos
    cout << "Digite as coordenadas do ponto P1:"<<endl;
    cout << "x1: ";
    cin >> x1;
    cout << "y1: ";
    cin >> y1;

    cout << endl << "Digite as coordenadas do ponto P2:"<<endl;
    cout << "x2: ";
    cin >> x2;
    cout << "y2: ";
    cin >> y2;

	// for() para criar a forma geométrica de acordo com as coordenadas de P1 e P2
    for(int i = x1; i < x2; i++)
    {
        for(int j = y1; j < y2; j++)
        {
            //Uso do método .at para acessar e modificar os pixels dessa região
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }
	
	//Definição da função imshow() para exibir a imagem  modificada
    imshow("image", image);
	
    waitKey(); //Função para aguardar o uso de alguma tecla para depois encerrar o programa
  
	return 0;
}
