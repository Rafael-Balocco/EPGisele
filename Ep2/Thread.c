#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include "error.h" 

#define N 2 // Define o número desejado de iterações

int vez = 0; // Variável para sincronização entre as threads, definir de quem é a vez

int count = 0; // Variável global para contar operações na seção crítica

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Inicialização do mutex, mecanismo que garante que apenas uma thread por vez possa acessar uma seção crítica do código, evitando condições de corrida.

// Função executada pela thread P0
void* P0(void* arg) {
    int meu_id = 0;
    int outro = 1;
    int i;
    for (i = 0; i < N; ++i) {
        pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar a seção crítica

        while (vez != meu_id) { // Enquanto não é a vez desta thread
            pthread_mutex_unlock(&mutex); // Libera o mutex enquanto espera
            pthread_mutex_lock(&mutex); // Requisita o mutex antes de verificar novamente
        }

        // Seção crítica
      
        count++; // Incrementa a variável count dentro da seção crítica
      
        printf("Thread %d P0 - Seção crítica, count = %d\n", i, count); 
      
        pthread_mutex_unlock(&mutex); // Libera o mutex após a seção crítica

        vez = outro; // Mudança de vez após a seção crítica
      
        // Seção não crítica
       
        printf("Thread %d P0 - Seção Não Crítica\n", i);
    }

    return NULL;
}

// Função executada pela thread P1
void* P1(void* arg) {
    int meu_id = 1;
    int outro = 0;
    int i;
    for (i = 0; i < N; ++i) {
        pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar a seção crítica

        while (vez != meu_id) { // Enquanto não é a vez desta thread
            pthread_mutex_unlock(&mutex); // Libera o mutex enquanto espera
            pthread_mutex_lock(&mutex); // Requisita o mutex antes de verificar novamente
        }

        // Seção crítica
        
        count++; // Incrementa a variável count dentro da seção crítica
      
        printf("Thread %d P1 - Seção crítica, count = %d\n", i, count);
        
        pthread_mutex_unlock(&mutex); // Libera o mutex após a seção crítica
        
        vez = outro; // Mudança de vez após a seção crítica
        
        // Seção não crítica
        printf("Thread %d P1 - Seção Não Crítica\n", i);
    }
    
    return NULL;
}

// Função principal
int main() {
    pthread_t threads[N]; // Cria um array de threads

    // Criando threads para P0 e P1
    if (pthread_create(&threads[0], NULL, P0, NULL) != 0) {
        perror("Falha ao criar a Thread P0"); // Exibe mensagem de erro caso a criação da thread falhe
        return EXIT_FAILURE;
    }

    if (pthread_create(&threads[1], NULL, P1, NULL) != 0) {
        perror("Falha ao criar a Thread P1"); // Exibe mensagem de erro caso a criação da thread falhe
        return EXIT_FAILURE;
    }

    // Esperando as threads terminarem
    for (int i = 0; i < N; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Falha ao aguardar a conclusão da Thread"); // Exibe mensagem de erro caso a espera pela thread falhe
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
