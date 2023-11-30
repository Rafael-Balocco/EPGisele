#include <stdio.h>
#include <pthread.h>
#include "error.h" // Inclui o arquivo "error.h" para tratamento de erros

void* hello(void* arg) {
    // Converte o argumento recebido de void* para int para obter o identificador da thread
    int thread_id = *((int*)arg); 
    printf("Hello world from thread %d!\n", thread_id); // Imprime mensagem com o identificador da thread
    return NULL; // Retorna NULL para finalizar a thread
}

int main() {
    int numThreads = 10; // Número de threads a serem criadas
    pthread_t threads[numThreads]; // Array para armazenar identificadores de thread

    for (int i = 0; i < numThreads; i++) {
        if (pthread_create(&threads[i], NULL, hello, &i) != 0) { // Criação de threads
            perror("pthread_create"); // Exibe mensagem de erro se a criação falhar
            return 1; // Retorna 1 para indicar erro
        }
    }

    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(threads[i], NULL) != 0) { // Espera as threads terminarem
            perror("pthread_join"); // Exibe mensagem de erro se a espera falhar
            return 1; // Retorna 1 para indicar erro
        }
    }

    return 0; // Retorna 0 para indicar sucesso
}
