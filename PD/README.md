# Programação Dinâmica

Algoritmos que utilizam o método de [Programação Dinâmica](https://pt.wikipedia.org/wiki/Programa%C3%A7%C3%A3o_din%C3%A2mica), baseado nas aulas do curso [Análise de Algoritmos (MAC0338)](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/dynamic-programming.html).

## [Segmento de Soma Máxima](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/max-sum-segment.html)

Dada uma sequência de n números inteiros, o problema é encontrar um segmento da sequência que tenha soma máxima. Uma solução simples pode ser encontrada com complexidade cúbica, que pode ser otimizado através da Divisão e Conquista para O(n log n). Mas através da programação dinâmica, a complexidade pode ser reduzida para O(n).

## [Subsequência Crescente Máxima](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/sscm.html)

Dada uma sequência de n números, o problema é encontrar sua subsequência crescente de maior tamanho. Através da Programação Dinâmica, foi implementado um algoritmo que resolve o problema em O(n²).

## [Subset Sum](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/mochila-subsetsum.html)

Dado um conjunto de n números, o problema é encontrar um subconjunto cuja soma é igual a algum valor definido c. Através da utilização de recursão pura, a resolução do problema possui complexidade exponencial. Com a implementação da Programação Dinâmica, a complexidade passa a depender de c, sendo O(nc).

## [Mochila Booleana](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/mochila-bool.html)

É uma versão um pouco mais complexa do Subset Sum, na qual é dada a capacidade máxima de uma mochila e um peso e valor para cada elemento do conjunto de objetos. O problema é decidir quais dos objetos colocar na mochila para que o valor total seja o maior possível e a capacidade da mochila seja respeitada.

## [Online Judge](https://onlinejudge.org/index.php)

Também foram implementadas soluções de alguns problemas relacionados a Programação Dinâmica encontrados no [Online Judge](https://onlinejudge.org/index.php):

- [The Twin Towers](https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1007)
- [Weights and Measures](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1095)
