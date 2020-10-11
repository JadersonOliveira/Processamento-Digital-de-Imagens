#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//Definições de objetos da classe Mat para armazenamento das imagens
    Mat imagem;
    Mat imagemModificada;

	//Leitura de uma imagem e o formato que a imagem será interpretada
    imagem= imread("biel.png", IMREAD_GRAYSCALE);
    
	// Caso a imagem não seja aberta, apresente a mensagem de erro
	if(!imagem.data)
    {
        cout << "nao abriu a imagem!" << endl;
    }
    
	//Definição da função para criação de uma janela auto-ajustável
	namedWindow("Imagem Real",WINDOW_AUTOSIZE);

	//Método .copyTo para copiar os dados de uma matriz para outra
    imagem.copyTo(imagemModificada);

	//Definição das variáveis para armazenar as larguras e alturas da imagens
    int width, height;
    int width2, height2;

	//Obtenção dos tamanhos
    width = imagem.size().width;
    height = imagem.size().height;
    width2 = width / 2;
    height2 = height / 2;

	/* Criação de objetos da classe Mat para armazenar imagens mapeadas de uma
	região retangular(através do construtor rect()) de uma imagem */
    Mat imagem1(imagem, Rect(0,0, height2, width2));
    Mat imagem2(imagem, Rect(width2,0, height2, width2));
    Mat imagem3(imagem, Rect(0,height2,height2,width2));
    Mat imagem4(imagem, Rect(height2,width2, height2, width2));

	/* Uso do método .copyTo para copiar as imagens mapeadas para a imagem nova */
    imagem1.copyTo(imagemModificada(Rect(0,0, height2, width2)));
    imagem4.copyTo(imagemModificada(Rect(height2,width2, height2, width2)));
    imagem2.copyTo(imagemModificada(Rect(0,height2,height2,width2)));
    imagem3.copyTo(imagemModificada(Rect(width2,0, height2, width2)));

	//Definição da função imshow() para exibir as imagens
    imshow("Imagem Real", imagem);
    imshow("Imagem Modificada", imagemModificada);

    //Função para aguardar o uso de alguma tecla para depois encerrar o programa
	waitKey();	
	
    return 0;
}
