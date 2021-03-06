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
      <p>Para solucionar essa questão, basicamente eu recebo as coordenados dos dois pontos e utilizo loops aninhados para varrer as linhas e colunas, gerando uma região onde será aplicado o efeito negativo, o efeito é realizado através do método .at, que modifica os pixeis dessa região especificada. O trecho onde isso ocorre pode ser visto abaixo.</p>
      
      ```cpp
         for(int i = x1; i < x2; i++)
         {
            for(int j = y1; j < y2; j++)
            { 
               image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
            }
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
      <p>Nesta questão, segui a recomendação de usar a classe Mat, então criei quatro objetos da classe Mat para armazenar imagens mapeadas de uma região retangular (através do construtor rect()) de uma imagem, como pode ser visto a seguir: </p>
   
      ```cpp
         Mat imagem1(imagem, Rect(0,0, height2, width2));
         Mat imagem2(imagem, Rect(width2,0, height2, width2));
         Mat imagem3(imagem, Rect(0,height2,height2,width2));
         Mat imagem4(imagem, Rect(height2,width2, height2, width2));
      ```
      
      <p>Após isso fiz o uso do método .copyTo para copiar as imagens mapeadas para a imagem nova e fiz o uso da função imshow() para exibir as imagens.</p>
      
      ```cpp
         imagem1.copyTo(imagemModificada(Rect(0,0, height2, width2)));
         imagem4.copyTo(imagemModificada(Rect(height2,width2, height2, width2)));
         imagem2.copyTo(imagemModificada(Rect(0,height2,height2,width2)));
         imagem3.copyTo(imagemModificada(Rect(width2,0, height2, width2)));
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
      poderá haver casos em que o número de regiões ou objetos será maior que 256, então o tom de cinza não poderá estar 
      relacionado ao número de contagem de objetos, logo uma solução para isso poderia ser dar um mesmo tom de cinza para aqueles
      objetos que compartilham as mesmas características.
      ```
      
   - **3.2 Exercício 2**
      <p align="justify"><i>Aprimore o algoritmo de contagem apresentado para identificar regiões com ou sem buracos internos que existam na cena. Assuma que objetos com mais de um buraco podem existir. Inclua suporte no seu algoritmo para não contar bolhas que tocam as bordas da imagem. Não se pode presumir, a priori, que elas tenham buracos ou não.</i></p>
      
      ***[Solução](#)***
      <p>A estratégia inicial para solucionar este exercícío foi remover os objetos/bolhas que tocam as bordas, então utilizei loops para percorrer a altura e largura verificando se os pixeis têm tom de cinza igual a 255, se sim, aplica o floodFill passando a coordenada desse pixel como referência além de passar o tom de cinza 0 para remover o objeto.</p>
      
      ```cpp
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
      ```
      
      <p>Após isso faço o uso dos loops para percorrer os pixeis da imagem e localizar as bolhas com e sem buracos, quando um objeto é encontrado, ele é contabilizado e aplicado o floodFill naquele pixel. </p>
      
      ```cpp
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
                  Isso foi feito apenas por questão estética, para deixar todas as bolhas com o mesmo
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
      <p>Nesta questão o grande diferencial para solucioná-la foi feito dentro do laço while, nele primeiramente fiz o uso do objeto cap para fazer a captura do frame, com o frame capturado utilizei a função flip() para inverter a imagem e gerar aquele efeito de espelho, após isso mudei o formato da cor com a função cvtColor(), em seguida fiz o uso da função split() para separar os planos de cor e também apliquei a função equalizeHist() para equalizar o histograma, por último fiz o uso da função merge() para juntar os planos. Esse trecho principal pode ser visto abaixo.</p>
      
      ```cpp
         cap >> image;	
         flip(image, image, 1);	

         cvtColor(image, image_Equa, CV_BGR2GRAY);	
         split(image_Equa, planesEqua);	
         equalizeHist(planesEqua[0], planesEqua[0]);	
         merge(planesEqua, image_Equa);	
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
      <p>Neste problema, eu criei duas variáveis principais, correlação e tolerância. A correlação é para receber o valor da comparação dos histogramas dos frames, feito através da função compareHist(). Já a variável tolerância é para definir o limiar, caso o valor da correlação ultrapasse esse limiar, é emitida uma mensagem de alerta na tela utilizando a função putText(). O trecho descrito acima pode ser visto logo abaixo. </p>
      
      ```cpp
   
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
      <p>Nesta questão foi seguido a lógica do exemplo apresentado. Após pesquisas realizadas, utilizei uma máscara encontrada nessas pesquisas para implementar o filtro laplaciano do gaussiano, a máscara possui uma matriz de 5 x 5, então a variável mask recebe a matriz 5 x 5 ao invés de uma 3 x 3 como utilizada nos outros filtros.</p>
      <p>Fonte da pesquisa: http://www.ic.uff.br/~aconci/gabor.pdf</p>
      
      ```cpp
         float laplgauss[]={ 0, 0, -1, 0,  0,
                             0, -1, -2, -1,  0,
                            -1,  -2,  16,  -2, -1,
                             0, -1, -2, -1,  0,
                             0, 0, -1, -0,  0,};

      ```
      <p align="center">
         <img alt="Original" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/Original.png" width="250" height="250">
         <img alt="laplaciano" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/laplaciano.png" width="250" height="250">
         <img alt="laplaciano_gaussiano" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/5.2%20Exercicio%201/laplaciano_gaussiano.png" width="250" height="250">
        <br>
          <em>&emsp;&emsp;Figura original&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figura laplaciano&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figura laplaciano gaussiano</em>
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
      
      ***[Solução](#)***
      <p>Na solução deste exercício, primeiramente foi tentado gerar o efeito de borramento na imagem, seguindo a dica do material de apoio utilizamos o filtro da média, então foi aplicado o filtro 10 vezes na cópia da imagem para gerar essa aparência de borramento.</p>
      
      ```cpp
         //Máscara da média
	      float media[] = {1,1,1,
					 1,1,1,
					 1,1,1};
					 
         image2.convertTo(image2, CV_32FC3);
         mask1 = Mat(3, 3, CV_32F, media);
         scaleAdd(mask1, 1/9.0, Mat::zeros(3,3,CV_32F), mask2);
	
         for(int i = 0; i < 10; i++){
            filter2D(image2, image2, image2.depth(), mask2, Point(1,1),0);
         }
      ```
      
      <p>Como o material fala, esse efeito não altera a região central da imagem modificada para gerar o efeito tiltshift, para resolver isso, foi utilizado a função on_trackbar_height(), para indicar o centro da imagem original e a partir dela definir o centro da região que irá ficar focada.</p>
      
      ```cpp
         void on_trackbar_height(int, void*){
            image1.copyTo(imageTop);

            int center = center_slider*(height-1)/100;
            int focusedHeight = top_slider*(height-1)/200;

            Mat tmp = image2(Rect(0, 0, width, limitHeightBound(center-focusedHeight)));
            tmp.copyTo(imageTop(Rect(0, 0, width, limitHeightBound(center-focusedHeight))));
            tmp = image2(Rect(0, limitHeightBound(center+focusedHeight), width,limitHeightBound(height-(center+focusedHeight))));
            tmp.copyTo(imageTop(Rect(0, limitHeightBound(center+focusedHeight), width,limitHeightBound(height-(center+focusedHeight)))));
            on_trackbar_blend(alfa_slider,0);
         }
      ```
      
      <p>Para definição da força do decaimento da região oriunda da imagem original para a região oriunda da  imagem borrada foi utilizado a própria função do exemplo addweighted.cpp.</p>
      
      <p>O resultado do programa pode ser visto abaixo.</p>
      
       <p align="center">
         <img alt="Imagem original" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/6.1%20Exercicio%201/Natal_PontaNegra.jpg" width="400" height="400">
         <img alt="Saída" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/6.1%20Exercicio%201/saida.PNG" width="400" height="400">
        <br>
          <em>Imagem original&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Exemplo de saída</em>
      </p>
      
      **OBS:** Para visualizar melhor o resultado abra a imagem "Exemplo de saída" em uma nova guia.
      
   - **6.1 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/addweighted.cpp como referência, implemente um programa tiltshiftvideo.cpp. Tal programa deverá ser capaz de processar um arquivo de vídeo, produzir o efeito de tilt-shift nos quadros presentes e escrever o resultado em outro arquivo de vídeo. A ideia é criar um efeito de miniaturização de cenas. Descarte quadros em uma taxa que julgar conveniente para evidenciar o efeito de stop motion, comum em vídeos desse tipo.</i></p>

**8. Detecção de bordas com o algoritmo de Canny**
  - **8.3 Exercício 1**
     <p align="justify"><i>Utilizando os programas exemplos/canny.cpp e exemplos/pontilhismo.cpp como referência, implemente um programa cannypoints.cpp. A idéia é usar as bordas produzidas pelo algoritmo de Canny para melhorar a qualidade da imagem pontilhista gerada. A forma como a informação de borda será usada é livre. Entretanto, são apresentadas algumas sugestões de técnicas que poderiam ser utilizadas:<br>
	 <ul>
            <li>Desenhar pontos grandes na imagem pontilhista básica;</li>
            <li>Usar a posição dos pixels de borda encontrados pelo algoritmo de Canny para desenhar pontos nos respectivos locais na imagem gerada;</li>
            <li>Experimente ir aumentando os limiares do algoritmo de Canny e, para cada novo par de limiares, desenhar círculos cada vez menores nas posições encontradas. A Figura 19 foi desenvolvida usando essa técnica.</li>
         </ul></i></p>
	 <p><i>Escolha uma imagem de seu gosto e aplique a técnica que você desenvolveu.</i></p>
	 <p><i>Descreva no seu relatório detalhes do procedimento usado para criar sua técnica pontilhista.</i></p>
	 
	***[Solução](#)***
	<p>Neste exercício foi seguido a sugestão dada de usar a posição dos pixels de borda encontrados pelo algoritmo de Canny para desenhar pontos nos respectivos locais na imagem gerada. A idéia como o próprio problema diz é usar as bordas produzidas pelo algoritmo de Canny para melhorar a qualidade da imagem pontilhista gerada.<br><br>
	Para fazer isso que foi proposto, utilizou-se a função findContours() do OpenCV, ela tem como objetivo encontrar contornos em uma imagem binária, com os contornos encontrados, foi utilizado a função circle() para desenhar circulos nesses contornos.<br><br></p>
	
	<p>Fonte da pesquisa da função findContours() : https://docs.opencv.org/3.4/df/d0d/tutorial_find_contours.html e 	     https://docs.opencv.org/3.4/d3/dc0/group__imgproc__shape.html#ga17ed9f5d79ae97bd4c7cf18403e1689a<br></p>
	
	<p>O algoritmo dessa parte mais importante pode ser visto abaixo.</p>

	```cpp
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(border, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
	for( size_t i = 0; i< contours.size(); i++ )
	{
		for( size_t j = 0; j< contours[i].size(); j++ )
		{
			gray = image.at<uchar>(contours[i][j].y, contours[i][j].x);
			circle(points,
				cv::Point(contours[i][j].x, contours[i][j].y),
				2,
				CV_RGB(gray,gray,gray),
				-1,
				CV_AA);
		}
	}
	```
	
	<p align="center">
         <img alt="Saída1" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/8.3%20Exercicio%201/Saida1.PNG" width="400" height="700">
         <img alt="Saída2" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/8.3%20Exercicio%201/Saida2.PNG" width="400" height="700">
        <br>
          <em>Exemplo 1 de saída&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Exemplo 2 de saída</em>
      </p>
      
      **OBS:** Para visualizar melhor o resultado abra as imagens em novas guias.
      
**9. Quantização vetorial com k-means**
  - **9.2 Exercício 1**
      <p align="justify"><i>Utilizando o programa kmeans.cpp como exemplo prepare um programa exemplo onde a execução do código se dê usando o parâmetro nRodadas=1 e inciar os centros de forma aleatória usando o parâmetro KMEANS_RANDOM_CENTERS ao invés de KMEANS_PP_CENTERS. Realize 10 rodadas diferentes do algoritmo e compare as imagens produzidas. Explique porque elas podem diferir tanto.</i></p>
      
      ***[Solução](#)***
      <p>Nesta questão fiz as modificações como recomendadas no problema e basicamente utilizei um loop para realizar as iterações necessárias, não teve nada de muito diferente do código base kmeans.cpp, então não tem nada de tão importante no código para se destacar aqui.<br></p>
      
      <p>Abaixo tem um gif para mostrar as imagens resultantes das iterações.<br></p>
      
      <p align="center">
         <img alt="GifResultado" src="https://github.com/JadersonOliveira/Processamento-Digital-de-Imagens/blob/main/9.2%20Exercicio%201/GifResultado.gif">
        <br>
          <em>&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Gif do resultado&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;</em>
      </p>
      
      <p><br>Através da execução do algoritmo, foi possível observar que a saída de todas as iterações apresentou alterações, mas algumas de forma mais clara que outras, por exemplo, as imagens resultantes das iterações 0 e 1 apresentaram alterações bem sutis, já as imagens resultantes  das iterações 2 e 3 apresentaram alterações bem nítidas. Logo, esse comportamente pode ser pelo fato do algoritmo ser repetido apenas 1 vez (nRodadas = 1) como definido no problema ou também por causa do uso do parâmetro KMEANS_RANDOM_CENTERS que define os centros de forma aleatória..</p>
      
      **OBS:** Para visualizar as imagens de cada iteração basta acessar a pasta do problema.
      
## Bibliografia 
* https://agostinhobritojr.github.io/tutorial/pdi/#_pref%C3%A1cio
* https://agostinhobritojr.github.io/curso/pdi/
* Processamento Digital de Imagens by Ogê Marques Filho, Hugo Vieira Neto
* Processamento Digital de Imagens by Rafael C. Gonzalez, Richard E. Woods



