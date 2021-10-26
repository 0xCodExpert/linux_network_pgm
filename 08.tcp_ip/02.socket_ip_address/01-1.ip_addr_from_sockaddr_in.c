#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>

int main(int argc, char * argv[]){
	in_addr_t host_addr;
	struct sockaddr_in sock_addr; 
	unsigned char *addr;
	unsigned long s_addr;
	unsigned long * ptr_s_addr;
	
	char str[INET_ADDRSTRLEN];
	
	sock_addr.sin_addr.s_addr=inet_addr(argv[1]);
	printf("NETWROK-BYTE-ORDER = %#x\n", sock_addr.sin_addr.s_addr);
	
	addr=inet_ntoa(sock_addr.sin_addr);
	printf("IP_ADDR = %s\n", addr);
	
	s_addr=sock_addr.sin_addr.s_addr;
	printf("NETWROK-ADDR-BIN = %lu\n",s_addr);
	ptr_s_addr = &s_addr;
	printf("PTR_S_ADDR = %#lx\n",*ptr_s_addr);
	
	inet_ntop(AF_INET, &s_addr, str, INET_ADDRSTRLEN);
	printf("%s\n", str);
	
	return 0;
}