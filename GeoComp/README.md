# Geometria Computacional

Algoritmos que visam resolver problemas geométricos em um plano 2D com a melhor eficiência possível. Foram baseados no texto que acompanhou o curso [Convite a Geometria Computacional](https://www.ime.usp.br/~cris/jai2009/), também foram utilizadas referências da matéria MAC0331 - Geometria Computacional.

Para melhor visualização dos algoritmos, foi utilizada a plataforma do Alexis Sakurai Landgraf, desenvolvida em um dos oferecimentos da disciplina MAC0331 - Geometria Computacional.

## Par de Pontos mais próximos

Dado um conjunto de n pontos, o algoritmo deve encontrar o par mais próximo. Este problema tem aplicações em controle de tráfego aéreo ou marítimo, onde pode-se querer saber quais são os objetos mais próximos para se detectar potenciais colisões.

### Algoritmo Elementar

Calcula todas as possíveis distâncias entre os pontos e armazena a menor calculada até o momento. Possui complexidade O(n²).

![](assets/dist-brute.gif)

### Algoritmo de Shamos e Hoey

Divide o plano em 2 recursivamente de forma semelhante a um merge sort, calculando a menor distância entre os pontos de uma mesma divisão e das divisões adjacentes, enquanto armazena a menor das 3 distâncias. Possui complexidade O(n log n).

![](assets/dist-sh.gif)

## Fecho convexo de um conjunto de Pontos

Dado um conjunto de n pontos, o algoritmo deve encontrar o menor polígono convexo que cobre todos esses pontos. Uma aplicação deste problema se encontra em robótica, onde se deseja evitar que um robô em movimento colida com outros objetos.

### Algoritmo Incremental

Analisa um ponto de cada vez, incrementando o fecho convexo caso o ponto analisado não esteja incluído no fecho já existente. Possui complexidade O(n²).

![](assets/fecho-inc.gif)

### Algoritmo do Embrulho de Presente

Incrementa o fecho com o ponto mais extremo no sentido anti-horário, até retornar ao ponto inicial. Com isso, possui complexidade dependente do tamanho do fecho h: O(hn).

![](assets/fecho-pres.gif)

### Algoritmo de Graham

Semelhante ao algoritmo incremental, mas realiza uma ordenação angular em torno do ponto de menor coordenada y, de forma que um novo ponto sempre é adicionado substituindo os mais recentes, aumentando a eficiência. Possui complexidade O(n log n).

![](assets/fecho-graham.gif)

## Interseção de Segmentos

Dada uma coleção de n segmentos no plano, o algoritmo deve decidir se existem dois segmentos que se intersectam. Tem várias aplicações, como o ray tracing, que na computação gráfica é um método importante para o processamento digital de cenas.

### Algoritmo Elementar

Padroniza os segmentos para terem sempre o primeiro ponto à esquerda e depois testa todas as possibilidades de interseções entre os segmentos. Possui complexidade O(n²).

![](assets/intersec-brute.gif)

### Algoritmo de Shamos e Hoey

Utiliza uma linha de varredura que percorre o plano da esquerda para a direita, de forma que se torna necessário somente testar as interseções em segmentos que tocaram a linha em sequência. Possui complexidade O(n log n).

![](assets/intersec-sh.gif)

## Triangulação de Polígonos

Dado um polígono formado por n vértices, o algoritmo deve encontrar o conjunto de triângulos que formam o polígono, sem nenhuma interseção de arestas. Pode ser aplicada na simplificação de modelos 3D, reduzindo o tempo de processamento em renderizações.

### Algoritmo N4

Encontra uma diagonal utilizando força bruta e repete o processo recursivamente nos polígonos de cada lado da diagonal até restar somente triângulos. Possui complexidade O(n⁴).

![](assets/triang-n4.gif)

### Algoritmo N3

Percorre ciclicamente os vertices adjacentes no polígono em busca de pontas de orelha, quando encontra alguma, ela é fechada com uma diagonal e o vértice é removido da lista, até que só sobre um triângulo. Possui complexidade O(n³).

![](assets/triang-n3.gif)

### Algoritmo N2

Semelhante ao algoritmo N3, mas utiliza uma lista ligada para armazenar os vértices e marca as orelhas já no início do algoritmo, reduzindo a complexidade total para O(n²).

![](assets/triang-n2.gif)

### Triangulação de Polígonos Monótonos

Um polígono é monótono em relação a uma reta L se é conexo para toda reta perpendicular a L. Se L é o eixo y, dizemos que o polígono é y-monótono. O algoritmo funciona realizando a divisão em polígonos y-monótonos e depois triangulando cada um deles, atingindo uma complexidade O(n log n).

![](assets/triang-mono.gif)

## Como Executar

Para executar as simulações, rode o comando `python3 tkgeocomp.py` no terminal. Uma interface gráfica será aberta, onde você poderá escolher o conjunto de dados e o algoritmo que será executado. Para mais detalhes, veja o [README da plataforma](src/README.md).
