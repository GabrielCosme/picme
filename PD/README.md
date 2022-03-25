# Programação Dinâmica

Algoritmos que utilizam o método de [Programação Dinâmica](https://pt.wikipedia.org/wiki/Programa%C3%A7%C3%A3o_din%C3%A2mica), baseado nas aulas do curso [Análise de Algoritmos (MAC0338)](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/dynamic-programming.html).

## [Segmento de Soma Máxima](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/max-sum-segment.html)

Dado um vetor de números inteiros, o problema é encontrar um segmento do vetor que tenha soma máxima. Uma solução simples pode ser encontrada com complexidade cúbica, que pode ser otimizado através da Divisão e Conquista para O(n log n). Mas através da programação dinâmica, a complexidade pode ser reduzida para O(n).

## [Subsequência Crescente Máxima](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/sscm.html)

Dada uma sequência de números qualquer, o problema é encontrar sua subsequência crescente de maio tamanho. Através da Programação Dinâmica, foi implementado um algoritmo que resolve o problema em O(n log n).

## [Subset Sum](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/mochila-subsetsum.html)

Dado um conjunto de números, o problema é encontrar um subconjunto cuja soma é igual a algum valor definido. Através da utilização de recursão pura, a resolução do problema possui complexidade exponencial. Com a implementação da Programação Dinâmica, a complexidade passa a depender do valor definido c, sendo igual a O(nc).

## [Mochila Booleana](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/mochila-bool.html)

É uma versão um pouco mais complexa do Subset Sum, no qual dado um conjunto de objetos, cada um com um certo peso e um certo valor. Quais dos objetos devo colocar na minha mochila para que o valor total seja o maior possível?

## [Online Judge](https://onlinejudge.org/index.php)

Também foram resolvidos alguns problemas relacionados a Programação Dinâmica encontrados no [Online Judge](https://onlinejudge.org/index.php):

- [The Twin Towers](https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1007)
- [Weights and Measures](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1095)
