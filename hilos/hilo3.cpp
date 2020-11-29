#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define  NUM_THREADS 7

void *llamar(void *idThread){
    long tid;
    tid = (long) idThread;
    if (tid==0)
        sleep(1);
    if (tid==1)
        sleep(4);
    if (tid==2)
        sleep(3);
    if (tid==3)
        sleep(5);
    if (tid==4)
        sleep(2);
    if (tid==5)
        sleep(3);
    if (tid==6)
        sleep(1);
    printf("Id Thread =  % ld \t i = % ld \n", pthread_self(), tid);
    printf("Id Thread =  % ld exiting ..............\n", tid);
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