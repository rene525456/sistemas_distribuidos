#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VECTOR_SIZE 100000000

// variables globales
int *array;	// se van almacenar los datos del vector
int count = 0;	// contador para ver cuantas veces hay del número 3
int double_count = 0;	//identificar que podemos tener problemas de precisión o conteo

//función para inicializador del vector
void initialize_vector(){
	int i = 0;
	array = (int*) malloc(sizeof(int) * VECTOR_SIZE); // La asignación dinámica de memoria en el Lenguaje de programación C, se crea espacio en el arreglo, molloc permite crear espacio en memoria para el vector
	if(array == NULL){
		printf("Memoria no disponible\n");
		exit(-1);
	}
	for(;i < VECTOR_SIZE; i++){
		array[i] = rand() % 20;// se genera un número aleatorio de 1 a 20
		if (array[i] == 3)
			double_count++;
	}
}

// contar el número de 3s en el arreglo
void count_3s(){
	int i = 0;
	for(;i < VECTOR_SIZE; i++){
		if (array[i] == 3)
			count++;
	}
}

// método principal e hilo principal
int main(int argc, char* argv[]){
	int i = 0;
	int err;
	clock_t t1, t2; // variables para tomar el tiempo del sistema
	printf("Running 3s-00");
	
	srand(time(NULL));
	printf("*** 3s-00 ***\n");
	printf("Initializing vector.... ");
	fflush(stdout); //Sirve para vaciar el buffer de escritura del archivo especificado. Por lo general cuando damos un prinft o un cout no se imprime directamnete en la pantalla. Se alamcena en un buffer que se vacia en determinadas ocaciones
	initialize_vector();
	printf("Vector initialized! \n");
	fflush(stdout);
	t1 = clock();
	count_3s();
	t2 = clock();
	printf("Count by thread %d!\n",count);
	printf("Double check %d!\n",double_count);
	printf("[[3s-00] tiempo transcurrido %f\n",(((float)t2 - (float)t1) /1000000.0F) * 1000); // elapse time diferencia entre t2 y
	printf("Finishing 3s-00");
	return 0;
}
