# Fluxo em Redes

Algoritmos relacionados a [Fluxos em Redes](https://pt.wikipedia.org/wiki/Rede_de_fluxo), baseados nas aulas do curso [Algoritmos em Grafos (MAC0328)](https://www.ime.usp.br/~pf/algoritmos_para_grafos/).

## Fluxo Máximo

Considere um digrafo com capacidades nos arcos e um par de vértices s e t.  Um fluxo de s a t é um valor positivo atribuído a cada arco do digrafo menor ou igual à sua capacidade tal que a quantidade de fluxo que entra em cada vértice seja igual à quantidade que sai, exceto nos vértices s e t.  O valor de um fluxo de s a t é a quantidade de fluxo que sai de s. O problema consiste em calcular um fluxo de s a t com valor máximo. Como solução, foram implementados algoritmos que utilizam caminhos aumentadores mínimos e caminhos aumentadores de máxima capacidade, além de filas e filas de prioridade.
