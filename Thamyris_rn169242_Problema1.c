// THAMYRIS NUNES SUGAHARA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura competidor da corrida maluca
struct corredor {
    int numero_carro;
    char nome[21];
};

int main() {
    int n;
    int i;
    int j;
     do{
        scanf("%d", &n);
    } while (n < 3 || n > 1000);

    // Aloca espaço para armazenar os dados dos competidores dinamicamente
    struct corredor *corredor = (struct corredor *)malloc(n * sizeof(struct corredor));

    // Lê os dados dos competidores 
    for (i = 0; i < n; i++) {
          scanf("%d %s", &corredor[i].numero_carro, corredor[i].nome);
    }

    //Le as posiçoes da largada e ordena o vetor antes de comecar a corrida
    int posicao;
    for (i = 0; i < n; i++) { // posicao do vetor
        scanf("%d", &posicao);
        for (j=i; j < n; j++ ){ // numero do carro na posicao do vetor pedido na entrada
            if (posicao == corredor[j].numero_carro){
                struct corredor aux_largada = corredor[j];
                corredor[j] = corredor[i];  
                corredor[i] = aux_largada; 
                j= n+1;
            }
        }
    }
 
    // COMECA A CORRIDA!!!

    // Processa as ultrapassagens
    int ultrapassagem = 0;
    int indice_ultrapassado = -1, indice_ultrapassa = -1;
    while (ultrapassagem != -1){ // Vai ler cada ultrapassagem enquanto não for -1
      scanf("%d", &ultrapassagem);
        // Verifica se a ultrapassagem é válida
        if (ultrapassagem >= 1 && ultrapassagem <= n) {
             
            // Encontra o índice do competidor que está sendo ultrapassado e o que está ultrapassando
            for (i = 0; i < n; i++) {
                if (corredor[i].numero_carro == ultrapassagem) {
                    indice_ultrapassado = i-1;  
                    indice_ultrapassa = i;
                }
            }

            // Realiza a ultrapassagem, se possível
            if (indice_ultrapassa > 0 && indice_ultrapassa <=n) {
                struct corredor aux_ultrapassagem = corredor[indice_ultrapassa];
                corredor[indice_ultrapassa] = corredor[indice_ultrapassado]; // corredor que ultrapassa recebe os dados do ultrapassado
                corredor[indice_ultrapassado] = aux_ultrapassagem; // ultrapassado recebe dados do que o ultrapassa
            }
        }
    }


    // Imprime os três primeiros colocados
    for (i = 0; i < 3; i++) {
        printf("%d %s\n", corredor[i].numero_carro, corredor[i].nome);
    }

    // Libera a memória alocada dinamicamente
    free(corredor);

    return 0;
}