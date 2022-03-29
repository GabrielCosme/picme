# Grafos

Algoritmos relacionados a [Grafos](https://pt.wikipedia.org/wiki/Teoria_dos_grafos), baseados nas aulas do curso [Algoritmos em Grafos (MAC0328)](https://www.ime.usp.br/~pf/algoritmos_para_grafos/).

## [Grafos Topológicos](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/topo-graphs.html)

Um grafo dirigido (dígrafo) é topológico se admite uma numeração topológica dos vértices. Uma numeração topo[] dos vértices é topológica se topo[v] < topo[w] para todo arco v-w. São apresentados dois algoritmos para realizar a numeração: Um "ao pé da letra" com complexidade V²(V + A), e outro que utiliza uma fila, e possui complexidade V + A.

## [Busca em Profundidade (DFS)](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html)

Depth First Search é um algoritmo que visita todos os vértices de um dígrafo e os numera em relação à ordem que foram visitados. Esta busca foi utilizada para definir se um grafo dirigido possui ciclos ou se é um dígrafo acíclico (dag, do inglês, directed acyclic graph), utilizando tanto a numeração prévia quanto a "on the fly" com complexidade linear.

## [Componentes Conexos](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/components.html)

Um grafo é conexo se cada um de seus vértices está ao alcance de cada um dos demais, e é biconexo quando existem dois caminhos sem arestas em comum conectando cada um dos seus vértices. Foram desenvolvidos algoritmos para encontrar os componentes conexos de um grafo, decidir se um grafo possui circuitos, decidir se um grafo é biconexo e encontrar seus componentes biconexos.

## [Conexão Forte](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/strong-graphs.html)

Um vértice de um dígrafo é fortemente ligado a outro se um está ao alcance do outro e vice-versa. Foram implementados os algoritmos altamente eficientes de Tarjan e de Kosaraju para encontrar as componentes fortemente ligadas de um grafo.

## [Coloração de Vértices](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/vertex-coloring.html)

Uma coloração válida de um grafo é uma de atribuição de uma cor a cada vértice de forma que duas pontas de cada aresta têm cores diferentes. Foi desenvolvido um algoritmo guloso para colorir um grafo, além de um algoritmo para decidir se um grafo pode ser colorido com apenas duas cores.

## [Custos nos Arcos e Arestas](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/weightedgraphs.html)

Foi abordado o problema da Árvore Geradora de Custo Mínimo (MST), utilizando o Algoritmo de Prim e o algoritmo de Kruskal para sua solução. Também foi tratado o problema do caminho mínimo, para o qual foram implementados os algoritmos de Bellman-Ford e de Dijkstra.
