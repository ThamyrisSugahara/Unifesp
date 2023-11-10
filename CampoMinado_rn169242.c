/*  THAMYRIS NUNES SUGAHARA 
    RA: 169242
*/ 

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct tempNo {        // Nó temporário
    int valor;
    int coluna;
    struct tempNo* prox;
}NO;

typedef NO* PONT;

typedef struct matriz{         // Estrutura da Matriz
    PONT* A;
    int linhas;
    int colunas;
}MATRIZ;

// Inicializar

void inicializarMatriz(MATRIZ* m, int lin, int col){
    int i;
    m->linhas = lin;
    m->colunas = col;
    m->A = (PONT*)malloc(lin*sizeof(PONT));     
    for(i=0; i<lin;i++){
        m->A[i] = NULL;    //Inicializando os nós da Matriz
    }
}

// Atribuindo valor

bool AtribuiMatriz (MATRIZ* m, int lin, int col, int val){
    if (lin < 0 || lin >= m-> linhas || col < 0 || col >= m->colunas){
        return false;
    }
    PONT ant = NULL;
    PONT atual = m->A[lin];
    while (atual != NULL && atual -> coluna < col){
        ant = atual;
        atual = atual->prox;
    }
    if (atual != NULL && atual->coluna == col){     //Verificando se o nó existe
        if (val == 0){
            if(ant == NULL) m->A[lin] = atual->prox;
            else ant->prox = atual->prox;
            free(atual);
        }
        else atual->valor = val;
    }else if (val != 0){
        PONT novo = (PONT)malloc(sizeof(NO));
        novo->coluna = col;
        novo->valor = val;
        novo->prox = atual;
        if(ant == NULL) m->A[lin] = novo;
        else ant->prox = novo;
    }
    return true;
}

// Acessar Valor

int ValorMatriz(MATRIZ* m, int lin, int col){
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas)
        return 0;
    PONT atual = m->A[lin];
    while (atual != NULL && atual->coluna < col)
        atual = atual->prox;
    if (atual != NULL && atual->coluna == col)
        return atual->valor;
    return 0;
}

// Verificar o número de bombas ao redor
int contarBombas(MATRIZ* m, int lin, int col){
    int bombas = 0;
    int i,j;
    for (i = -1; i <= 1; i++){
        for (j = -1; j <= 1; j++){
            int linhaVizinha = lin + i;
            int colunaVizinha = col + j;
            if (linhaVizinha >=0 && linhaVizinha < m->linhas && colunaVizinha >=0 && colunaVizinha < m->colunas){
                if (ValorMatriz(m, linhaVizinha,colunaVizinha)==-1){
                    bombas++;
                }
            }
        }
    }
    return bombas;
}

int main(){
int quantL, quantC, j, i, l, c, b;
    scanf("%d %d", &quantL, &quantC);      // Numero de linhas e colunas do campo minado

    if (quantL < 0 || quantC < 0 || quantL > 100 || quantC > 100){
        printf("Dimensoes invalidas.");
        return 1;
    }

    MATRIZ matriz;
    inicializarMatriz(&matriz,quantL,quantC);

    scanf("%d", &b); // Numero de Bombas
    if (b < 0 || b > 60){
        printf("Numero de bombas invalido.");
    }

    //Coordenadas das bombas
    for (i = 0; i < b; i++){
        scanf("%d %d", &l,&c);   //Numero da linha e da coluna onde ficará a bomba
        if(l >= 0 && l < quantL && c >= 0 && c < quantC){
            int bExiste = ValorMatriz(&matriz, l, c);
            if(!bExiste){
                AtribuiMatriz(&matriz, l, c, -1);
            }
        }
    }
    //Imprimir a Matriz (Campo Minado)
    for (i = 0; i < quantL; i++){
        for(j = 0; j < quantC; j++){
            if( ValorMatriz(&matriz, i, j) == -1){
                printf("X ");
            }else{
                int bombasEmVolta = contarBombas(&matriz, i, j);
                printf("%d ", bombasEmVolta);
            }
        }
        printf("\n");
    }
    //Liberar memória
    for (i = 0; i < quantL; i++){
        PONT atual = matriz.A[i];
        while(atual != NULL){
                PONT temp = atual;
                atual = atual -> prox;
                free(temp);
        }
    }
    free(matriz.A);
    return 0;
}