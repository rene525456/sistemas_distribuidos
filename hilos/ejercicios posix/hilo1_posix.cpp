#include <pthread.h>
#include <stdio.h>
#define MAX 100

void *inc_x(void *x_void_ptr);

int main(){
	int x = 0;
	int y = 0;
	printf("x: %d, y: %d\n", x, y);
	pthread_t inc_x_thread;
	if (pthread_create(&inc_x_thread, NULL, inc_x, &x)){
		fprintf(stderr, "Error creating thread\n");
		return 2;
	}
	while (++y <MAX);
	printf("y increment finished\n");
	printf("X: %d, y: %d\n", x, y);
	return 0;
}

void *inc_x(void *x_void_ptr){
	printf("I am in method\n");
	int *x_ptr = (int *)x_void_ptr;
	while (++(*x_ptr) < MAX);
	printf("x increment finished\n");
	return NULL;
}