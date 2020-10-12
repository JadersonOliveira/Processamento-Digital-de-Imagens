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
      ![Figura 4](https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/Figura4.png?raw=true "Figura4.png")
      ![Biel](https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/biel.png?raw=true "Biel.png")
      ![Saída](https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/2.2%20Exercicio%201/Sa%C3%ADda.png?raw=true "Saída.png")
      *image_caption*
      <pre>
         Exemplo de saída (Figura 4)  Figura de entrada (Biel.png)  Figura de saída (Saída.png)
      </pre>
   
   - **2.2 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/pixels.cpp como referência, implemente um programa trocaregioes.cpp. Seu programa deverá trocar os quadrantes em diagonal na imagem. Explore o uso da classe Mat e seus construtores para criar as regiões que serão trocadas. O efeito é ilustrado na Figura 5.</i></p>

**3. Preenchendo regiões**
   - **3.2 Exercício 1**
      <p align="justify"><i>Observando-se o programa labeling.cpp como exemplo, é possível verificar que caso existam mais de 255 objetos na cena, o processo de rotulação poderá ficar comprometido. Identifique a situação em que isso ocorre e proponha uma solução para este problema.</i></p>
      
   - **3.2 Exercício 2**
      <p align="justify"><i>Aprimore o algoritmo de contagem apresentado para identificar regiões com ou sem buracos internos que existam na cena. Assuma que objetos com mais de um buraco podem existir. Inclua suporte no seu algoritmo para não contar bolhas que tocam as bordas da imagem. Não se pode presumir, a priori, que elas tenham buracos ou não.</i></p>
      
**4. Manipulação de histogramas** 
   - **4.2 Exercício 1**
      <p align="justify"><i>Utilizando o programa exemplos/histogram.cpp como referência, implemente um programa equalize.cpp. Este deverá, para cada imagem capturada, realizar a equalização do histogram antes de exibir a imagem. Teste sua implementação apontando a câmera para ambientes com iluminações variadas e observando o efeito gerado. Assuma que as imagens processadas serão em tons de cinza.</i></p>
      
   - **4.2 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/histogram.cpp como referência, implemente um programa motiondetector.cpp. Este deverá continuamente calcular o histograma da imagem (apenas uma componente de cor é suficiente) e compará-lo com o último histograma calculado. Quando a diferença entre estes ultrapassar um limiar pré-estabelecido, ative um alarme. Utilize uma função de comparação que julgar conveniente.</i></p>
      
**5. Filtragem no domínio espacial I**
   - **5.2 Exercício 1**
      <p align="justify"><i>Utilizando o programa exemplos/filtroespacial.cpp como referência, implemente um programa laplgauss.cpp. O programa deverá acrescentar mais uma funcionalidade ao exemplo fornecido, permitindo que seja calculado o laplaciano do gaussiano das imagens capturadas. Compare o resultado desse filtro com a simples aplicação do filtro laplaciano.</i></p>
      
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



