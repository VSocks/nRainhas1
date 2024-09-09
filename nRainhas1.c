//AVISO: esse algoritmo somente funciona até tabuleiros de tamanho 12.
//Como o uso de memória para um algoritmo de pesquisa por largura cresce exponencilamente,
//Tentar computar valores muito maiores do que um tabuleiro de tamanho 10 poderia crashar
//O programa ou até congelar o computador. Descobri na prática. Para que isso não aconteca,
//Esse código estabelece m limite máximo de computação, excedendo ele o programa para com segfault.
//De modo geral, esse é um péssimo algoritmo para resolver o problema das N rainhas, e foi feito
//Por motivos acadêmicos, não para ser usado na prática.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Struct que guarda o estado do tabuleiro
typedef struct{
    int *positions;  //positions[i] guarda a coordenada ca coluna da rainha
    int row;         //linha atual na qual estamos tentando colocar a rainha
} State;

//Verifica se a posição atual é válida
//Para isso, primeiro se itera em todas as colunas anteriores
//Checando por conflitos com as rainhas já colocadas
//prevCol == col checa se há conflitos verticais
//abs(prevCol - col) == abs(i - row) checa se há conflitos diagonais
//Não há necessidade de checar conflitos horizontais já que o algoritmo só coloca uma rainha por linha
//Caso haja algum conflito, retorna false, e solveNQueens chama isSafe na próxima posição
//Caso não haja, retorna true, indicando que se pode colocar a rainha aqui
bool isSafe(int *positions, int row, int col){
    for(int i = 0; i < row; i++){
        int prevCol = positions[i];
        if(prevCol == col || abs(prevCol - col) == abs(i - row)){
            return false;
        }
    }
    return true;
}

//Converte índice de coluna para letra (A, B, C,...)
char convertToLetter(int col){
    return 'A' + col;
}

void printSolution(int *positions, int n){
    printf("Solução: ");
    for(int i = 0; i < n; i++){
        printf("(%c, %d) ", convertToLetter(positions[i]), i + 1);
    }
    printf("\n");
}

void solveNQueens(int n){
    //Fila que guarda o estado do tabuleiro.
    //Possui tamanho máximo, então não é eficiente,
    //Mas evita congelar o computador por uso excessivo
    //De memória.
    State *queue = (State *)malloc(sizeof(State) * 1000000);
    int front = 0, rear = 0;

    //Inicia tabuleiro vazio
    State initialState;
    initialState.positions = (int *)malloc(sizeof(int) * n);
    initialState.row = 0;
    queue[rear++] = initialState;

    while(front < rear){
        State currentState = queue[front++];

        //Quando todas rainhas forem colocadas, printa solução
        if(currentState.row == n){
            printSolution(currentState.positions, n);
            free(currentState.positions);
            break;  //Para algoritmo ao encontrar primeira solução
        }

        //Tenta colocar rainhas em cada coluna da linha atual
        for(int col = 0; col < n; col++){
            if(isSafe(currentState.positions, currentState.row, col)){
                //Cria novo estado para cada rainha colocada
                State newState;
                newState.positions = (int *)malloc(sizeof(int) * n);
                for(int i = 0; i < currentState.row; i++){
                    newState.positions[i] = currentState.positions[i];
                }
                newState.positions[currentState.row] = col;
                newState.row = currentState.row + 1;

                queue[rear++] = newState;
            }
        }
        free(currentState.positions);
    }
    free(queue);
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    if (n <= 0){
        printf("Tamanho inválido.\n");
        return 1;
    }

    solveNQueens(n);

    return 0;
}