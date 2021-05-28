#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr, client_addr;
	
	struct sockaddr_in getipa(const char*, int);

	
	int sd, sc;
	int size, val;
	//int size;
	int num[2], res;
	if ((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		printf ("SERVER: Error en el socket");
	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(int));
	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(4200);
	bind(sd, &server_addr, sizeof(server_addr));
	listen(sd, 5);
	size = sizeof(client_addr);
	
	while (1){
		printf("esperando conexion\n");
		sc = accept(sd, (struct sockaddr *)&client_addr,&size);
		read ( sc, (char *) num, 2 *sizeof(int));
		// recibe la petición
		res = num[0] + num[1]; // procesa la petición
		write(sc, &res, sizeof(int)); // envía el resultado
		close(sc); // cierra la conexión (sc)
	}
	close (sd);
	return 0;
} /*fin main */
