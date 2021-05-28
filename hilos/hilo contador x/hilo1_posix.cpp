#include <pthread.h>
#include <stdio.h>
#define MAX 100


void *inc_x(void *x_void_ptr); // función que va a hacer invocada una vez que se crea el hilo, no está definida

int main(){
	int x = 0;
	int y = 0;
	printf("x: %d, y: %d\n", x, y); // imprimir los valores de x y y
	pthread_t inc_x_thread; //es una variable de tipo pthread_t es el identificador del hilo q se va a crear
	if (pthread_create(&inc_x_thread, NULL, inc_x, &x)){
		fprintf(stderr, "Error al crear al hilo|thread\n");
		return 2;
	}
	while (++y <MAX);
	printf("y terminó el incremento\n");
	printf("X: %d, Y: %d\n", x, y);
	return 0;
}

void *inc_x(void *x_void_ptr){
	printf("Estoy en el método implementado\n");
	int *x_ptr = (int *)x_void_ptr; // conviertiendo a un entero
	while (++(*x_ptr) < MAX);
	printf("x terminó el incremento\n");
	return NULL;
}
