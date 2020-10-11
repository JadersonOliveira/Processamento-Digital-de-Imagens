#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image, realce;	//Definição de objetos da classe Mat para armazenamento das imagens
    int width, height; //Definição das variáveis para armazenar a largura e altura da imagem
    int nobjects;	//Definição da variável para armazenar o total de bolhas sem buraco
    int nobjects_ComBuraco; //Definição da variável para armazenar o total de bolhas com buraco
    int total_objetos;	//Definição da variável para armazenar o total de bolhas 
    int objcolor;	//Definição de variável para armazenar o número da cor

	/* Criação de um objeto do tipo Point, para indicar a semente de preenchimento
	que é usada no floodFill() */
    Point p;
	
	/* Uso da função imread() para leitura de uma imagem 
	e o formato que a imagem será interpretada */
    image = imread("bolhas.png", IMREAD_GRAYSCALE);

	//Caso a imagem não seja aberta, apresente a mensagem de erro
    if(!image.data)
    {
        cout << "imagem nao carregou corretamente\n";
        return(-1);
    }

	//Obtenção da largura e altura da imagem
    width=image.cols;
    height=image.rows;
    cout << endl << "Dimensao: ";
    cout << width << "x" << height << endl;

	//Definição das coordenadas X e Y da nossa semente p
    p.x=0;
    p.y=0;
	
	//for() para remoção das bolhas que tocam as bordas verticais 
    for(int i=0; i<height; i++)
    {
        //Verifica a borda da lateral esquerda
		if(image.at<uchar>(i,0) == 255)
        {
            p.x=0;
            p.y=i;
            floodFill(image,p,0);
        }

		//Verifica a borda da lateral direita
        if(image.at<uchar>(i,width-1) == 255)
        {
            p.x=width-1;
            p.y=i;
            floodFill(image,p,0);
        }
    }

	//for() para remoção das bolhas que tocam as bordas horizontais 
    for(int j=1; j<width; j++)
    {
        //Verifica a borda superior
		if(image.at<uchar>(0,j) == 255)
        {
            p.x=j;
            p.y=0;
            floodFill(image,p,0);
        }

		//Verifica a borda inferior
        if(image.at<uchar>(height-1,j) == 255)
        {
            p.x=j;
            p.y=height-1;
            floodFill(image,p,0);
        }
    }

    //Aplica floodfill no ponto(0,0) e pinta o fundo de tom de cinza 1
    p.x=0;
    p.y=0;
    floodFill(image,p,1);


    //Inicializa as variáveis
    nobjects_ComBuraco = 0;
    objcolor = 250;
	
	//for() para localizar bolhas com buracos
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
			//Se o pixel possui tom de cinza == 0, é ocorrência de buraco
            if(image.at<uchar>(i,j) == 0)
            {
                /* Verifica o pixel anterior ao do buraco para pintar ele com o valor do objcolor.
				Isso foi feito apenas por questão estética, para deixar todas as bolhas com o
				tom de cinza e ficar melhor de visualizar. */
                if(image.at<uchar>(i,j-1) == 255)
                {
                    nobjects_ComBuraco++;
                    p.y=i;
                    p.x=j-1;
                    floodFill(image,p, objcolor);
                }

            }
        }
    }

    //Inicializa as variáveis
    nobjects=0;
    objcolor = 250;
	
	//for() para localizar bolhas com buracos
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
			//Se o pixel possui tom de cinza == 255, é ocorrência de bolha
            if(image.at<uchar>(i,j) == 255)
            {
                nobjects++;
                p.x=j;
                p.y=i;
                floodFill(image,p, objcolor);
            }
        }
    }

	//Calcula o total de bolhas
    total_objetos = nobjects + nobjects_ComBuraco;

    cout << "A figura tem " << nobjects << " objetos sem buracos\n";
    cout << "A figura tem " << nobjects_ComBuraco << " objetos com buracos\n";
    cout << "A figura tem " << total_objetos << " objetos\n\n";

	//Definição da função imshow() para exibir a imagem  modificada
    imshow("image", image);
	
	//Definição da função imwrite() para criar a imagem  labeling
    imwrite("labeling.png", image);

	//Função para aguardar o uso de alguma tecla para depois encerrar o programa
    waitKey();
	
    return 0;
}
