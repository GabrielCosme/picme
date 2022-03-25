# Teoria dos Jogos

Algoritmos relacionados a [Teoria dos Jogos](https://pt.wikipedia.org/wiki/Teoria_dos_jogos), baseados no livro [Tópicos da Teoria dos Jogos em Computação](https://www.ic.unicamp.br/~rafael/publicacoes/ttjc/livroAGT.pdf).

## [Tragédia dos Comuns](src/CommonsTrajedy)

A [Tragédia dos Comuns](https://pt.wikipedia.org/wiki/Trag%C3%A9dia_dos_comuns) é uma situação na qual pessoas agindo individualmente e racionalmente atingem um resultado contrário ao bem comum.
O código simula uma situação conhecida como Compartilhamento de Banda, buscando demonstrar o conceito descrito.

## [Balanceamento de Carga](src/LoadBalancing)

O [Balanceamento de Carga](https://pt.wikipedia.org/wiki/Balanceamento_de_carga) é um problema de distribuir uniformemente a carga de trabalho entre duas ou mais máquinas.
O código simula uma situação onde cada um dos indivíduos age pelo bem próprio e a falta de coordenação pode gerar custos desnecessários. Também foi feita uma animação demonstrando o funcionamento do algoritmo.

## [Roteamento](src/Routing)

O roteamento consiste de escolher rotas em uma rede com o objetivo de enviar uma demanda do seu ponto de origem ao seu ponto de destino.
O código busca demonstrar que as ações egoístas de cada jogador resultam em um equilíbrio que não necessariamente é a melhor situação para todos.

## [Mecanismos de Coordenação](src/Vickrey)

São mecanismos que incentivam a coordenação dos jogadores de maneira a obter equilíbrios com bons valores de preço da anarquia. Nesta seção será apresentada uma aplicação de um [mecanismo VCG](https://en.wikipedia.org/wiki/Vickrey%E2%80%93Clarke%E2%80%93Groves_auction) em um jogo de caminho mínimo. Baseado no código descrito no livro [Vickrey Pricing in Network Routing: Fast Payment Computation](http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=7D30FD1DC08EB4A1DF3C1746F89C05AE?doi=10.1.1.25.1887&rep=rep1&type=pdf).
