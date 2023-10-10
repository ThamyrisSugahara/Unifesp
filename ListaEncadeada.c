/*Escreva uma TAD de lista de inteiros ordenada simplesmente encadeada com as seguintes operações:
a) Verificar se um número pertence lista;
b) Inserir um novo elemento na lista mantendo a ordem;
c) Remover um elemento da lista;
d) Imprimir os valores da lista;
e) Copiar uma lista l1 para uma lista l2;
f) Concatenar uma lista l1 com uma lista l2;
g) Intercalar l1 e l2; 
Faça o usuário ter a escolha dessas operações*/

#include <stdio.h>
#include <stdlib.h>

// Representação do nó
typedef struct Node{
    int data;                  // Dado armazenado no nó
    struct Node* next;         // Ponteiro para o próximo nó
}Node;

// Estrutura da lista
typedef struct LinkedList {
    struct Node* head;         // Ponteiro para o primeiro nó da lista
}LinkedList;


// Inserindo novo elemento mantendo a ordem (b)
void insert(LinkedList* list, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(list->head == NULL || value < list->head->data){     // Caso a lista esteja vazia ou o novo elemento seja de menor valor do que o primeiro da lista
        newNode->next = list->head;   // next do newNode aponta para o que era anteriormente o primeiro nó
        list->head = newNode;         // atualizo o ponteiro head para apontar para o novo nó, agora ele é o primeiro da lista
        return;
    }

    Node* current = list->head;  // Encontrar o nó anterior onde o novo elemento deve ser inserido (current é a variável que percorre)
    while(current->next != NULL && current->next->data < value){
        current = current-> next; 
    }
    
    newNode->next = current->next;  // Configura o próximo do novo nó para apontar para o que era o próximo nó do "current"
    current->next = newNode;       // Atualiza o próximo do "current" para apontar para o novo nó

}

// Removendo o elemento da lista (c)

void removeNode(LinkedList* list, int value){
    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL && current->data != value){   // Procurar elemento na lista
        prev = current;
        current = current->next;
    }

    if (current == NULL){  // Se o elemento não for encontrado, sair
        return;
    }

    if(prev == NULL){   // Caso o elemento removido seja o  primeiro da lista
        list-> head = current -> next;
    }else{
        prev->next = current->next;    //Caso não seja o primeiro da lista, configura o próximo do nó anterior(prev) para apontar para o que era o próximo nó do "current"
    }
    free(current);
}

// Busca por elemento na lista (a)

int search(LinkedList* list, int value){
    Node* current = list-> head;

    while(current != NULL){
        if(current->data == value){
            return 1; // elemento encontrado
        }
        current= current-> next;
    }
    return 0; // Elemento não encontrado
}

// Imprimir os valores da lista (d)

void printList(LinkedList* list){
    Node* current = list->head;

    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
}

//Copiar uma lista 1 para uma lista 2 (e)

void copyList(LinkedList* l1, LinkedList* l2){
    Node* current = l1->head;
    Node* newList = NULL;
    Node* tail = NULL;

    while( current != NULL){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = current-> data;
        newNode->next = NULL;

        if(newList == NULL){
            newList = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        current = current->next;
    }

    l2->head = newList;
}

// Concatenar l1 e l2 (f)

void concatenateLists(LinkedList* l1, LinkedList* l2){
    if(l1->head == NULL){
        l1->head = l2->head;
    }else{
        Node* current = l1->head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = l2->head;
    }
    l2->head = NULL;
}

// Intercalar l1 e l2 (g)
void appendToResult(LinkedList* result, Node** tail, int data);

LinkedList interleaveLists(LinkedList* l1, LinkedList* l2) {
    LinkedList result;
    result.head = NULL;
    Node* tail = NULL;
    Node* current1 = l1->head;
    Node* current2 = l2->head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->data < current2->data) {
            appendToResult(&result, &tail, current1->data);
            current1 = current1->next;
        } else {
            appendToResult(&result, &tail, current2->data);
            current2 = current2->next;
        }
    }

    // Adicionar elementos restantes de l1, se houver
    while (current1 != NULL) {
        appendToResult(&result, &tail, current1->data);
        current1 = current1->next;
    }

    // Adicionar elementos restantes de l2, se houver
    while (current2 != NULL) {
        appendToResult(&result, &tail, current2->data);
        current2 = current2->next;
    }

    return result;
}

void appendToResult(LinkedList* result, Node** tail, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (result->head == NULL) {
        result->head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}


int main() {
    LinkedList list1;
    list1.head = NULL;
    LinkedList list2;
    list2.head = NULL;
    LinkedList newList;

    int choice;
    int value;

    while (1) {
        printf("\nOperações disponíveis:\n");
        printf("1. Inserir elemento na lista\n");
        printf("2. Verificar se um número pertence à lista\n");
        printf("3. Remover um elemento da lista\n");
        printf("4. Imprimir os valores da lista\n");
        printf("5. Copiar a lista l1 para l2\n");
        printf("6. Concatenar list1 com list2\n");
        printf("7. Intercalar list1 e list2\n");
        printf("8. Sair\n");
        printf("Escolha uma operação: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                insert(&list1, value);
                printf("Valor %d inserido na lista.\n", value);
                break;
            case 2:
                printf("Digite o valor a ser verificado: ");
                scanf("%d", &value);
                if (search(&list1, value)) {
                    printf("%d pertence à lista.\n", value);
                } else {
                    printf("%d não pertence à lista.\n", value);
                }
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &value);
                removeNode(&list1, value);
                printf("Valor %d removido da lista.\n", value);
                break;
            case 4:
                printf("Valores na lista: ");
                printList(&list1);
                printf("\n");
                break;
            case 5:
                copyList(&list1, &list2);
                printf("Lista l1 copiada para l2.\n");
                break;
            case 6:
                concatenateLists(&list1, &list2);
                printf("Listas concatenadas.\n");
                printList(&list1);
                break;
            case 7:
                newList = interleaveLists(&list1, &list2);
                printf("Listas intercaladas.\n");
                printList(&newList);
                break;
            case 8:
                // Liberar a memória alocada para as listas e sair
                while (list1.head != NULL) {
                    Node* temp = list1.head;
                    list1.head = list1.head->next;
                    free(temp);
                }
                while (list2.head != NULL) {
                    Node* temp = list2.head;
                    list2.head = list2.head->next;
                    free(temp);
                }
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}