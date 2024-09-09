//AVISO: esse algoritmo trava para inputs muito maiores que 10.
//De modo geral, esse é um péssimo algoritmo para resolver o problema das N rainhas, e foi feito
//Por motivos acadêmicos, não para ser usado na prática.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
    // Initial capacity for queue
    int capacity = 10000;
    
    State *queue = (State *)malloc(sizeof(State) * capacity);
    int front = 0, rear = 0;

    //Aloca tabuleiro vazio
    State initialState;
    initialState.positions = (int *)malloc(sizeof(int) * n);
    initialState.row = 0;
    queue[rear++] = initialState;

    while(front < rear){
        //Aumenta tamanho da fila se necessário
        if(rear >= capacity){
            capacity *= 2;
            queue = (State *)realloc(queue, sizeof(State) * capacity);
            if(!queue){
                printf("Falha em alocar memória\n");
                exit(EXIT_FAILURE);
            }
        }

        State currentState = queue[front++];

        //Se todas rainhas forem colocadas, imprime solução
        //Para o código na primeira solução encontrada
        if(currentState.row == n){
            printSolution(currentState.positions, n);
            free(currentState.positions);
            break;
        }

        //Tentar colocar rainha na linha atual da coluna atual
        for(int col = 0; col < n; col++){
            if(isSafe(currentState.positions, currentState.row, col)){
                State newState;
                newState.positions = (int *)malloc(sizeof(int) * n);
                for (int i = 0; i < currentState.row; i++){
                    newState.positions[i] = currentState.positions[i];
                }
                newState.positions[currentState.row] = col;
                newState.row = currentState.row + 1;

                queue[rear++] = newState;
            }
        }
        free(currentState.positions);
        for(int i = front; i < rear; i++){
            free(queue[i].positions);
            }
    }
    free(queue);
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    if(n <= 0){
        printf("Tamanho inválido.\n");
        return 1;
    }

    clock_t start = clock();

    solveNQueens(n);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo para resolver: %.6f seconds\n", time_taken);

    return 0;
}