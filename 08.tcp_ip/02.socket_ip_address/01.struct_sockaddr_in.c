#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	in_addr_t host_addr;
	struct sockaddr_in sock_addr; 
	struct in_addr sip_addr;
	unsigned char *addr;
	
	host_addr=inet_network(argv[1]); 	// host_addr=inet_network("192.168.60.100");
	printf("HOST-BYTE-ORDER = %#x\n", host_addr);
	
	sock_addr.sin_addr.s_addr=htonl(host_addr);
	printf("NETWROK-BYTE-ORDER = %#x\n", sock_addr.sin_addr.s_addr);
	
	sock_addr.sin_addr.s_addr=inet_addr(argv[1]);
	printf("NETWROK-BYTE-ORDER = %#x\n", sock_addr.sin_addr.s_addr);
	
	inet_aton(argv[1], &sip_addr);
	printf("NETWROK-BYTE-ORDER = %#x\n", sip_addr.s_addr);
	
	inet_pton(AF_INET, argv[1], &(sock_addr.sin_addr));
	printf("NETWROK-BYTE-ORDER = %#x \n", sock_addr.sin_addr.s_addr);
	
	addr=inet_ntoa(sock_addr.sin_addr);
	printf("IP_ADDR = %s\n", addr);
	return 0;
}