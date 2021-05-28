#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <memory.h>

int main(int argc, char **argv) {
	struct hostent *hp;
	struct in_addr in;
	//hp = gethostbyname("www.uc3m.es");
	hp = gethostbyname("www.unl.edu.ec");
	if (hp == NULL) {
		printf("Error en gethostbyname\n");
		return 0;
	}
	memcpy(&in.s_addr,*(hp->h_addr_list),sizeof(in.s_addr));
	printf("%s es %s\n", hp->h_name, inet_ntoa(in));
}
