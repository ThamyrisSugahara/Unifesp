// THAMYRIS NUNES SUGAHARA

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um cliente
typedef struct Cliente {
    int ID;
    int time;
    struct Cliente* next;
} Client;

// Estrutura para representar uma fila simplesmente encadeada
typedef struct Fila {
    Client* first;
    Client* end;
} Fila;

// Função para inicializar uma fila
void initializeFila(Fila* fila) {
    fila->first = NULL;
    fila->end = NULL;
}

// Função para enfileirar um cliente em uma fila
void enfileirar(Fila* fila, int ID, int time) {
    Client* new_client = (Client*)malloc(sizeof(Client));
    new_client->ID = ID;
    new_client->time = time;
    new_client->next = NULL;

    if (fila->first == NULL) {
        fila->first = new_client;
        fila->end= new_client;
    } else {
        fila->end->next = new_client;
        fila->end = new_client;
    }
}

// Função para desenfileirar um cliente de uma fila
Client* desenfileirar(Fila* fila) {
    if (fila->first == NULL) {
        return NULL;
    } else {
        Client* finished_client = fila->first;
        fila->first = fila->first->next;
        if (fila->first == NULL) {
            fila->end = NULL;
        }
        return finished_client;
    }
}

int main() {
    int n_clients, n_attendants;
    scanf("%d %d", &n_clients, &n_attendants);

    Fila* filas = (Fila*)malloc(n_attendants * sizeof(Fila));
    for (int i = 0; i < n_attendants; i++) {
        initializeFila(&filas[i]);
    }

    int* time_attendants = (int*)malloc(n_attendants * sizeof(int));
    for (int i = 0; i < n_attendants; i++) {
        time_attendants[i] = 0;
    }

    for (int i = 0; i < n_clients; i++) {
        int time;
        scanf("%d", &time);

        int attendant_min = 0;
        for (int j = 1; j < n_attendants; j++) {
            if (time_attendants[j] < time_attendants[attendant_min]) {
                attendant_min = j;
            }
        }

        enfileirar(&filas[attendant_min], i + 1, time);
        time_attendants[attendant_min] += time;
    }

    for (int i = 0; i < n_attendants; i++) {
        printf("%d: ", i + 1);
        Client* finished_client = desenfileirar(&filas[i]);
        while (finished_client != NULL) {
            printf("%d ", finished_client->ID);
            free(finished_client);
            finished_client = desenfileirar(&filas[i]);
        }
        printf("\n");
    }

    free(filas);
    free(time_attendants);

    return 0;
}
