// Leia o PDF ou MD antes de iniciar este exercício!


// Faça os includes necessários aqui
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem_th1;
sem_t sem_th2;

void *thread1(void *_arg) {

    sem_wait(&sem_th2);
    
    printf("A\n"); 

    sem_post(&sem_th1);    
    sem_post(&sem_th1); 
    sem_post(&sem_th1);

    sem_wait(&sem_th2);
    sem_wait(&sem_th2);
    sem_wait(&sem_th2);
    
    printf("E\n");

    return NULL;
}

void *thread2(void *_arg) {
    sem_wait(&sem_th1);
    printf("B\n");
    sem_post(&sem_th2);
    return NULL;
}

void *thread3(void *_arg) {
    sem_wait(&sem_th1);
    printf("C\n");
    sem_post(&sem_th2);
    return NULL;
}

void *thread4(void *_arg) {
    sem_wait(&sem_th1);
    printf("D\n");
    sem_post(&sem_th2);
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(&sem_th1, 0, 0);
    sem_init(&sem_th2, 0, 1);

    pthread_t tids[4];
    pthread_create(&tids[0], NULL, thread1, NULL);
    pthread_create(&tids[1], NULL, thread3, NULL);
    pthread_create(&tids[2], NULL, thread4, NULL);
    pthread_create(&tids[3], NULL, thread2, NULL);

    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&sem_th1);
    sem_destroy(&sem_th2);
    
    return 0;
}