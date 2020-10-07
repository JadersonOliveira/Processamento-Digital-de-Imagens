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
         - um ajuste para regular a altura da região central que entrará em foco;</br>
         - um ajuste para regular a força de decaimento da região borrada;</br>
         - um ajuste para regular a posição vertical do centro da região que entrará em foco. Finalizado o programa, a imagem produzida deverá ser salva em arquivo.</br>
      </i></p>
   - **6.1 Exercício 2**
      <p align="justify"><i>Utilizando o programa exemplos/addweighted.cpp como referência, implemente um programa tiltshiftvideo.cpp. Tal programa deverá ser capaz de processar um arquivo de vídeo, produzir o efeito de tilt-shift nos quadros presentes e escrever o resultado em outro arquivo de vídeo. A ideia é criar um efeito de miniaturização de cenas. Descarte quadros em uma taxa que julgar conveniente para evidenciar o efeito de stop motion, comum em vídeos desse tipo.</i></p>

## Bibliografia 
* https://agostinhobritojr.github.io/tutorial/pdi/#_pref%C3%A1cio
* Processamento Digital de Imagens by Ogê Marques Filho, Hugo Vieira Neto
* Processamento Digital de Imagens by Rafael C. Gonzalez, Richard E. Woods



