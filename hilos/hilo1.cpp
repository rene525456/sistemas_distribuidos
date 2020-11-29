#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* llamar(void* ptr){
    printf("Procesando el hilo");
    printf("Estoy en la funcion \nId Thead = %ld \n", pthread_self());
    pthread_exit(NULL);
    return NULL;

}

int main(){
    pthread_t thread; // declarar el hebra
    pthread_create(&thread,NULL, llamar, NULL);
    printf("Estoy en en main \nId Thead = %ld \n", thread);
    pthread_join(thread, NULL);
    return 0;
}