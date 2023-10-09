// THAMYRIS NUNES SUGAHARA

#include <stdio.h>
#include <stdlib.h>

struct Node { // estrutura para um nó da lista encadeada
    int data;
    struct Node* next; //ponteiro para o proximo nó
};

// Inicializar pilha
void initialize(struct Node** top) {
    *top = NULL;
}

// Verificar se a pilha está vazia
int isEmpty(struct Node* top) {
    return top == NULL;
}

// Empilhar
void push(struct Node** top, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Desempilhar
int pop(struct Node** top) {
    if (isEmpty(*top)) {
        return -1; // Pilha vazia, retorna -1
    }
    struct Node* temp = *top;
    *top = (*top)->next;
    int poppedData = temp->data;
    free(temp);
    return poppedData;
}

// Função principal para avaliar a expressão RPN
int calcRPN(char* expression) {
    struct Node* top = NULL; // Inicializa a pilha como vazia
    int i = 0, operand1, operand2, result = 0; // Inicializa result com 0
    int operators = 0, operands = 0;

    while (expression[i] != '\0') {
        if (expression[i] >= '0' && expression[i] <= '9') {
            push(&top, expression[i] - '0');
            operands++;
        } else {
            operand2 = pop(&top);
            operand1 = pop(&top);
            if (operand1 == -1 || operand2 == -1) {
                printf("Invalid Expression\n");
               return -1; // Expressão inválida, retorna -1
            }
            switch (expression[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Invalid Expression\n");
                        return -1; // Expressão inválida, retorna -1
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid Expression\n");
                    return -1; // Expressão inválida, retorna -1
            }
            push(&top, result);
            operators++;
        }
        i++;
        
    }
    if (operators != operands - 1) {
        printf("Invalid Expression\n");
        return -1; // Expressão inválida, retorna -1
    }
    return result;
}

int main() {
    char expression[1024];
    scanf("%s", expression); // Lê a expressão da entrada

    int result = calcRPN(expression); // Avalia a expressão
     if (result != -1) {
        printf("%d\n", result); // Exibe o resultado se a expressão for válida
    }

    return 0;
    
}
