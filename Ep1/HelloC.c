#include <stdio.h>
#include <pthread.h>
#include "error.h"


void* hello(void* arg) {
    int thread_id = *((int*)arg); // Convertendo o argumento para inteiro
    printf("Hello world from thread %d!\n", thread_id);
    return NULL;
  
}

int main() {
   
   int numThreads = 10; // Defina o número de threads que deseja criar
   pthread_t threads[numThreads];

   for (int i = 0; i < numThreads; i++) {
        
        if (pthread_create(&threads[i], NULL, hello, &i) != 0) {
           perror("pthread_create");
           return 1;
       }
   }

   for (int i = 0; i < numThreads; i++) {
       if (pthread_join(threads[i], NULL) != 0) {
           perror("pthread_join");
           return 1;
       }
   }

   return 0;
}