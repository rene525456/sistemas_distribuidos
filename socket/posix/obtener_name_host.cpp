#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main () {
	char maquina[256];
	int err;
	err = gethostname(maquina, 256);
	printf("Ejecuto en la maquina %s\n", maquina);
	
	return 0;
}
