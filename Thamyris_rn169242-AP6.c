// THAMYRIS NUNES SUGAHARA

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{     //Estrutura para os nós da lista
    char data;
    int count;           //Contador
    struct Node* next;   //Ponteiro para o próximo
    struct Node* prev;   //Ponteiro para o anterior
}Node;

Node* initializeLista() {
    return NULL;
}

Node* insertEnd(Node* head, char data, int count){     //Insere um nó no final da lista
    Node* newNode = (Node*)malloc(sizeof(Node));       //Alocação de memória
    newNode->data=data;
    newNode->count = count;
    newNode->next=NULL;

   //Se a lista estiver vazia, o ponteiro "head" é nulo, e portanto o novo nó será o primeiro da lista e o anterior será nulo
   if(head==NULL){          
    newNode->prev = NULL;
    return newNode;
   }

    Node* current = head;      
    while (current->next != NULL) {      //Percorre a lista até o ultimo nó
        current = current->next;
    }

    current->next = newNode;             //Novo último nó é o próximo do nó atual
    newNode->prev = current;             //Ligação bidirecional, configura anterior do novo nó para apontar de volta para current
    return head;                         //Retorna início da lista atualizada
}

Node* removeNoise(Node* head){
    Node* current = head;           // Inicializa current apontando para o início

    while(current!= NULL){
        if (current->count ==1){    // Verifica se o nó atual tem count igual a 1
            Node* left = current->prev;    //Cria ponteiro "left"(esquerda) apontando o anterior
            Node* right = current->next;   //Cria o ponteiro "right"(direita) apontando para o próximo
          // Se o nó atual tem um nó anterior e um seguinte, e ambos têm count maior ou igual a 2 (não são ruídos)
            if(left != NULL && right != NULL && left->count >=2 && right->count>=2){
                if(left->count > right->count){            //Se o count(frequência) à esquerda for maior que o à direita
                    left->count += 1;                      //Incrementa o count da esquerda
                    left->next = right;                    //Atualiza o next do nó da esquerda para apontar para o nó à direita
                    right->prev = left;                    //Atualiza o prev do nó da direita para apontar para o nó à esquerda
                    free(current);
                    current = left;                        //Move o ponteiro current para o nó à esquerda
                } else if (left->count < right->count) {   //Se o count à esquerda for menor
                    right->count += 1;                     //Incrementa o count à direita
                    right->prev = left;                    //Atualiza o prev do nó da direita para apontar para o nó à esquerda
                    left->next = right;                    //Atualiza o next do nó da esquerda para apontar para o nó à direita
                    free(current);
                    current = right;                       //Move o ponteiro current para o nó à direita
                } else {                                   //Count iguais
                    left->count += 1;
                    left->next = right;
                    right->prev = left;
                    free(current);
                    current = left;
                }
            }else if(left == NULL && right != NULL && right->count >= 2) {     //Se o nó atual não tem nó anterior mas tem nó seguinte e ele tem count maior ou igual a 2
                right->count += 1;                         //Incrementa o count à direita
                head = right;                              //Atualiza o início da lista para apontar para o nó a direita
                right->prev = NULL;                        //Define o ponteiro prev do nó á direita como NULL
                free(current);
                current = head;
            }else if (left != NULL && right == NULL && left->count >= 2) {    //Se o nó atual não tem nó posterior, as tem o anterior (ultimo nó)
                left->count += 1;                                             //Incrementa o count ao nó da esquerda
                left->next = NULL;                                            //Define o ponteiro next do nó à esquerda como NULL
                free(current);
                current = left;                                               //Move o ponteiro current para o nó à esquerda
            }else{
                current = current->next;
            }
        } else {
            current = current->next;
        }
    }

    return head;
}

Node* createSubstring(char* input){
    Node* head = initializeLista();     //Inicializa a lista
    int i = 0;

    while (input[i] != '\0') {         //Percorre a string até o caractere nulo
        char currentChar = input[i];   //Obtém o caractere atual
        int count = 0;

        while (input[i] != '\0' && input[i] == currentChar) {
            count++;                  //Incrementa o contador
            i++;                      //Move para o próximo caractere
        }

        head = insertEnd(head, currentChar, count);   //Insere um novo nó no final da lista com o caractere atual e sua contagem
    }
    return head;
}

void printSubstring(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d%c", current->count, current->data);
        current = current->next;
    }
}

int substringLength(Node* head) {
    int length = 0;
    Node* current = head;

    while (current != NULL) {
        int count = current->count;
        int numCountDigits = 0;

        //Conta o número de dígitos em 'count'
        while (count > 0) {
            count /= 10;
            numCountDigits++;
        }

        //Adiciona o número de caracteres representados por 'count'
        length += numCountDigits;

        // Adicionar o número de caracteres na substring atual (ignorando o valor 'count')
        length += 1;

        current = current->next;
    }

    return length;
}


int main() {
    char input[1024];
    scanf("%s", input);

    Node* substrings = createSubstring(input);

    int originalLength = substringLength(substrings);
    
    printf("%d\n", originalLength);

    printSubstring(substrings);
    printf("\n");

    substrings = removeNoise(substrings);

    int length2 = substringLength(substrings);
    printf("%d\n", length2);

    printSubstring(substrings);

    Node* current = substrings;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
