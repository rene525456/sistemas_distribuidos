#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 8 // cada hilo tendrá un segmento del vector
#define VECTOR_SIZE 100000000

// Vector de identificadores de hilos
pthread_t tid[MAX_THREADS]; // vector de tipo hilo, almacenar los identificadores de todos los hilos q vamos creando

// definición de un candado para arbitrar el acceso a una variable compartida
pthread_mutex_t mutex;

// variables globales
int *array; // un apuntador a un vecto de enteros
int length = VECTOR_SIZE; // máxima longitud del vector
int count = 0;
int double_count = 0;

// máximo de números de hilos que se pueden lanzar
int max_threads = MAX_THREADS;

// Función usada por la función 'pthread_create'.'pthread_create' crea un nuevo hilo quien se dedicará a ejecutar esta función
void *count3s_thread(void *arg){
	int i;
	int length_per_thread = length / max_threads; // cada hilo procese una parte del vector,
	long id = (long)arg;

	int start = id * length_per_thread;
		
	
	for(i = start; i < start + length_per_thread; i++){
        
		if (array[i] == 3){
            pthread_mutex_lock(&mutex); // se llama esta sección crítica
			count++;
            pthread_mutex_unlock(&mutex);
		}
	}
	
	return NULL;
	//pthread_exit(NULL);
}

//inicializador del vector
// Función que inicializa los elementos del vector y cuanta cuants vesces se genero el numero '3'
void initialize_vector(){
	int i = 0;
	array = (int*) malloc(sizeof(int) * VECTOR_SIZE); // La asignación dinámica de memoria en el Lenguaje de programación C, se crea espacio en el arreglo
	if(array == NULL){
		printf("Allocation memory failed\n");
		exit(-1);
	}
	for(;i < VECTOR_SIZE; i++){
		array[i] = rand() % 20;
		if (array[i] == 3)
			double_count++;
	}
}

int main(int argc, char* argv[]){
	long i = 0;
	int err;
	clock_t t1, t2;
	// se puede pasar por argumentos el número de hilos que se quiere invocar para procesar el vector

	if (argc == 2){
		max_threads = atoi(argv[1]);
		if (max_threads > MAX_THREADS){
			max_threads = MAX_THREADS;
		}else{}
	}else{
		max_threads = MAX_THREADS;
	}
	printf("Running 3s-00 Using %d threads\n", max_threads);
	
	srand(time(NULL));
	printf("*** 3s-01 ***\n");
	printf("Initializing vector.... ");
	fflush(stdout);
	initialize_vector();
	printf("Vector initialized! \n");
	fflush(stdout);
	t1 = clock();
	
	//El candado que evita la concurrencia
	pthread_mutex_init(&mutex, NULL);
	
	// comienza el procesamiento
	while(i < max_threads){
		err = pthread_create(&tid[i], NULL, &count3s_thread, (void*)i);
		if (err != 0)
			printf("[3s-01] Can't create a thread [%ld]\n",i);
		else
			printf("[3s-01] Thread created [%ld]\n",i);
		i++;
	}
	i = 0;
	for(; i < max_threads; i++){
		void *status;
		int rc;
		rc = pthread_join(tid[i],&status);
		if(rc){
			printf("ERROR; return code from pthread() is %d \n", rc);
			exit(-1);
		}else{
			printf("Thread [%ld] exited with status [%ld] \n", i, (long)status);
		}
	}
	t2 = clock();
	printf("[3s-01] Count by threads %d\n",count);
	printf("[3s-01] Double check %d!\n",double_count);
	pthread_mutex_destroy(&mutex);
	printf("[3s-01] Elapsed time %f\n",(((float)t2 - (float)t1) /1000000.0F) * 1000);
	printf("Finishing 3s-00");
	return 0;
}
