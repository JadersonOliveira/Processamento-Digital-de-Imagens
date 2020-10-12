# Processamento Digital de Imagens
Repositório para a disciplina de Processamento Digital de Imagens da Universidade Federal do Rio Grande do Norte (UFRN), ministrada pelo professor doutor Agostinho de Medeiros Brito Junior.

O intuito deste repositório é manter e expor as resoluções dos exercícios propostos na disciplina.

## Requisitos básicos
* C++ 
* OpenCV

## Exercícios
Aqui será exposto apenas o resultado, o algoritmo se encontra na sua própria pasta aqui do repositório.

**2. Manipulando pixels em uma imagem**
   - **2.2 Exercício 1** 
      <p align="justify"><i>Utilizando o programa exemplos/pixels.cpp como referência, implemente um programa regions.cpp. Esse programa deverá solicitar ao usuário as coordenadas de dois pontos P1 e P2 localizados dentro dos limites do tamanho da imagem e exibir que lhe for fornecida. Entretanto, a região definida pelo retângulo de vértices opostos definidos pelos pontos P1 e P2 será exibida com o negativo da imagem na região correspondente. O efeito é ilustrado na Figura 4.</i></p>
            
      ***[Solução](#)***
      ```cpp
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
      ```
      <p align="center">
         <img alt="Figura 4" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/Figura4.png">
         <img alt="Biel" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/biel.png">
         <img alt="Saída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/Sa%C3%ADda.png">
        <br>
          <em>Exemplo de saída (Figura 4)&emsp;&emsp;&emsp;&emsp;Figura de entrada (Biel.png)&emsp;&emsp;&emsp;&emsp;Figura de saída (Saída.png)</em>
      </p>
   
   - **2.2 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/pixels.cpp como referência, implemente um programa trocaregioes.cpp. Seu programa deverá trocar os quadrantes em diagonal na imagem. Explore o uso da classe Mat e seus construtores para criar as regiões que serão trocadas. O efeito é ilustrado na Figura 5.</i></p>

      ***[Solução](#)***
      ```cpp
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
      ```
       <p align="center">
         <img alt="Figura 5" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%202/Figura5.png">
         <img alt="Biel" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%202/biel.png">
         <img alt="Saída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%202/Saida.png">
        <br>
          <em>Exemplo de saída (Figura 5)&emsp;&emsp;&emsp;&emsp;Figura de entrada (Biel.png)&emsp;&emsp;&emsp;&emsp;Figura de saída (Saída.png)</em>
      </p>
**3. Preenchendo regiões**
   - **3.2 Exercício 1**
      <p align="justify"><i>Observando-se o programa labeling.cpp como exemplo, é possível verificar que caso existam mais de 255 objetos na cena, o processo de rotulação poderá ficar comprometido. Identifique a situação em que isso ocorre e proponha uma solução para este problema.</i></p>
      
      ***[Solução](#)***
      ```txt
         Como a região à qual o pixel pertence será rotulada com tom de cinza igual ao número de contagem de objetos atual,
      poderá haver casos em que o número de regiões ou objetos será maior que 256, então o tom de cinza nao poderá estar 
      relacionado ao número de contagem de objetos, logo uma solução para isso poderia ser dar um tom de  cinza para aqueles
      objetos que compartilham as mesmas características.
      ```
      
   - **3.2 Exercício 2**
      <p align="justify"><i>Aprimore o algoritmo de contagem apresentado para identificar regiões com ou sem buracos internos que existam na cena. Assuma que objetos com mais de um buraco podem existir. Inclua suporte no seu algoritmo para não contar bolhas que tocam as bordas da imagem. Não se pode presumir, a priori, que elas tenham buracos ou não.</i></p>
      
      ***[Solução](#)***
      ```cpp
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
      ```
      <p align="center">
         <img alt="bolhas" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/3.2%20Exercicio%202/bolhas.png">
         <img alt="Saída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/3.2%20Exercicio%202/labeling.png">
        <br>
          <em>Figura de entrada (bolhas.png)&emsp;&emsp;&emsp;&emsp;Figura de saída (labeling.png)</em>
      </p>
      
**4. Manipulação de histogramas** 
   - **4.2 Exercício 1**
      <p align="justify"><i>Utilizando o programa exemplos/histogram.cpp como referência, implemente um programa equalize.cpp. Este deverá, para cada imagem capturada, realizar a equalização do histogram antes de exibir a imagem. Teste sua implementação apontando a câmera para ambientes com iluminações variadas e observando o efeito gerado. Assuma que as imagens processadas serão em tons de cinza.</i></p>
      
      ***[Solução](#)***
      ```cpp
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
      ```
      <p align="center">
         <img alt="Alta" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%201/Alta.png">
         <img alt="AltaSaída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%201/AltaSaida.png">
        <br>
          <em>&emsp;&emsp;Resultado de ambiente com iluminação</em>
      </p>
      <p align="center">
         <img alt="Alta" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%201/Pouca.png">
         <img alt="AltaSaída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%201/SaidaPouca.png">
        <br>
          <em>&emsp;&emsp;Resultado de ambiente com pouca iluminação</em>
      </p>
      
      **OBS:** O resultado não saiu tão bom talvez devido a qualidade da câmera do notebook e também o ângulo de iluminação do ambiente, mas se
      comparar o canto superior direito das saídas das imagens, dá pra notar bem a diferença de uma equalização com muita e pouca iluminação.
      
   - **4.2 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/histogram.cpp como referência, implemente um programa motiondetector.cpp. Este deverá continuamente calcular o histograma da imagem (apenas uma componente de cor é suficiente) e compará-lo com o último histograma calculado. Quando a diferença entre estes ultrapassar um limiar pré-estabelecido, ative um alarme. Utilize uma função de comparação que julgar conveniente.</i></p>
      
      ***[Solução](#)***
      ```cpp
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
      ```
      <p align="center">
         <img alt="Parado" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%202/Parado.png">
         <img alt="Movimentado" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/4.2%20Exercicio%202/Movimentado.png">
        <br>
          <em>Figura com objeto parado&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figura com objeto movimentado</em>
      </p>
      
**5. Filtragem no domínio espacial I**
   - **5.2 Exercício 1**
      <p align="justify"><i>Utilizando o programa exemplos/filtroespacial.cpp como referência, implemente um programa laplgauss.cpp. O programa deverá acrescentar mais uma funcionalidade ao exemplo fornecido, permitindo que seja calculado o laplaciano do gaussiano das imagens capturadas. Compare o resultado desse filtro com a simples aplicação do filtro laplaciano.</i></p>
      
      ***[Solução](#)***
      ```cpp
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
      ```
      <p align="center">
         <img alt="Original" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/Original.png">
         <img alt="laplaciano" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/laplaciano.png">
         <img alt="laplaciano_gaussiano" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/laplaciano_gaussiano.png">
        <br>
          <em>Figura original&emsp;&emsp;&emsp;&emsp;Figura laplaciano&emsp;&emsp;&emsp;&emsp;Figura laplaciano gaussiano</em>
      </p>
      
      **OBS:** De uma imagem para outra pode haver alguma diferença devido a movimentação na hora de fazer a captura da imagem.
               Para ver imagens de outros filtros basta acessar a pasta aqui no repositório deste exercício.
               
**6. Filtragem no domínio espacial II**
   - **6.1 Exercício 1**
      <p align="justify"><i>Utilizando o programa exemplos/addweighted.cpp como referência, implemente um programa tiltshift.cpp. Três ajustes deverão ser providos na tela da interface:</br>
         <ul>
            <li>um ajuste para regular a altura da região central que entrará em foco;</li>
            <li>um ajuste para regular a força de decaimento da região borrada;</li>
            <li>um ajuste para regular a posição vertical do centro da região que entrará em foco. Finalizado o programa, a imagem produzida deverá ser salva em arquivo.</li>
         </ul>
      </i></p>
      
   - **6.1 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/addweighted.cpp como referência, implemente um programa tiltshiftvideo.cpp. Tal programa deverá ser capaz de processar um arquivo de vídeo, produzir o efeito de tilt-shift nos quadros presentes e escrever o resultado em outro arquivo de vídeo. A ideia é criar um efeito de miniaturização de cenas. Descarte quadros em uma taxa que julgar conveniente para evidenciar o efeito de stop motion, comum em vídeos desse tipo.</i></p>

## Bibliografia 
* https://agostinhobritojr.github.io/tutorial/pdi/#_pref%C3%A1cio
* Processamento Digital de Imagens by Ogê Marques Filho, Hugo Vieira Neto
* Processamento Digital de Imagens by Rafael C. Gonzalez, Richard E. Woods



