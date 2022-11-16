#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VECTOR_SIZE 1000000000

// variables globales
int *array;	
int count = 0;	
int double_count = 0;	

void initialize_vector(){
	int i = 0;
	array = (int*) malloc(sizeof(int) * VECTOR_SIZE); 
	if(array == NULL){
		printf("Memoria no disponible\n");
		exit(-1);
	}
	for(;i < VECTOR_SIZE; i++){
		array[i] = rand() % 20;
		if (array[i] == 3)
			double_count++;
	}
}

void count_3s(){
	int i = 0;
	for(;i < VECTOR_SIZE; i++){
		if (array[i] == 3)
			count++;
	}
}

int main(int argc, char* argv[]){
	int i = 0;
	int err;
	clock_t t1, t2; 
	printf("Running 3s-00");
	srand(time(NULL));
	printf("*** 3s-00 ***\n");
	printf("Initializing vector.... ");
	fflush(stdout); 
	initialize_vector();
	printf("Vector initialized! \n");
	fflush(stdout);
	t1 = clock();
	count_3s();
	t2 = clock();
	printf("Count by thread %d!\n",count);
	printf("Double check %d!\n",double_count);
	printf("[[3s-00] tiempo transcurrido %f\n",(((float)t2 - (float)t1) /1000000.0F) * 1000); 
	printf("Finishing 3s-00");
	return 0;
}

