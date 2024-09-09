Esse programa usa um algoritmo de busca em largura para resolver o problema das N rainhas. Ele recebe o input do usuário, que é usado para o número N de rainhas, bem como o tamanho (N x N) do tabuleiro. Quando um resultado válido é encontrado, ele é impresso no terminal com as coordenadas das rainhas em conjuntos de tuplas. O pseudocódigo não serve propósito funcional, mas serve para explicar de forma simples o funcionamento de cada função.

AVISO 2: Esse algoritmo trava para inputs muito maiores que 10. Como o uso de memória para um algoritmo de pesquisa por largura cresce exponencilamente, tentar computar valores muito maiores do que um tabuleiro de tamanho 10 poderia crashar o programa ou até congelar o computador. Descobri na prática. Para que isso não aconteca, esse código estabelece m limite máximo de computação, excedendo ele o programa para com segfault. De modo geral, esse é um péssimo algoritmo para resolver o problema das N rainhas, e foi feito por motivos acadêmicos, não para ser usado na prática.