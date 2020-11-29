#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define  NUM_THREADS 7

void *llamar(void *idThread){
    long tid;
    tid = (long) idThread;
    printf("Id Thread =  % ld \t i = % ld \n", pthread_self(), tid);
    pthread_exit(NULL);
    return NULL;

}

int main(){

    pthread_t arrayThread[NUM_THREADS];// array de hilos
    for(long i=0; i<NUM_THREADS; i++){
        pthread_create(&arrayThread[i],NULL, llamar, (void *)i);
    }
    for(long i=0; i<NUM_THREADS; i++){
        pthread_join(arrayThread[i],NULL);
    }
    
    return 0;
}