# Compartilhamento de Largura de Banda

## Descrição
O problema do compartilhamento de banda consiste em n jogadores querendo transmitir dados por um cabo de transmissão que tem capacidade máxima 1 (largura de banda).
Cada jogador pode transmitir um fluxo de dados entre 0 e 1, mas a medida que o fluxo total se aproxima da capacidade do cabo,
a qualidade da transmissão se deteriora e com isso diminui o benefício dos jogadores.

Chamando de t a banda ainda livre no cabo, e x<sub>i</sub> a banda consumida pelo jogador i. O benefício de cada jogador é definido por t*x<sub>i</sub>. Sendo que os jogadores buscam maximizar esse benefício.
Ou seja, sempre aproximando a banda consumida x<sub>i</sub> de (1-t)/2.
A consequência disso é que a cada rodada a banda de cada jogador se aproxima de 1/(n+1), o que resulta em um benefício total de n/(n+1)².
Resultado consideravelmente inferior a situação onde todos jogadores decidem definir seu fluxo como 1/(2n) que gera um benefício total de 1/4.

Esta situação é um exemplo da Trajédia dos Comuns, na qual as ações indivduais buscando benefício próprio geram resultados piores que as ações pensadas coletivamente.

## Utilização do Código
### [commons.c](commons.c)
Após definir o número de jogadores e banda inicial de cada um, o código mostrara a quantidade de banda livre, a quantidade de banda consumida por cada jogador,
o ganho de cada jogador e o ganho total, em seguida, será possível definir uma nova quantidade de banda consumida para algum dos jogadores, ou para todos ao mesmo tempo
se digitar -1. Com isso, deverá digitar para qual valor deseja alterar o consumo da banda, que pode ser um número entre 0 e 1, -1 se quiser que o jogador faça a escolha de maior benefício para todos, 
ou 2 se quiser que o jogador faça a escolha de melhor benefício para ele mesmo.

A partir disso, pode-se demonstrar diversas situações distintas:

- A situação onde todos fazem escolhas egoístas não é a de maior benefício total;
- Escolhas egoístas em cada rodada levam a um [Equílibrio de Nash](https://pt.wikipedia.org/wiki/Equil%C3%ADbrio_de_Nash) [(commons_equilibrium.c)](commons_equilibrium.c);
- Se o jogo se encontra nessa situação de equilíbrio, e um jogador decide fazer a escolha de maior benefício para todos, seu benefício próprio diminui;
- A situação de maior benefício para todos não é um Equilibrio de Nash.
