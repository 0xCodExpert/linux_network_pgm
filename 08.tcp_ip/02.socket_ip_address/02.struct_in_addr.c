#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	in_addr_t host_addr;
	struct in_addr sip_addr;
	char str[INET_ADDRSTRLEN];
	
	sip_addr.s_addr=inet_addr(argv[1]);
	printf("NETWROK-BYTE-ORDER = %#x\n", sip_addr.s_addr);
	
	inet_aton(argv[1], &sip_addr);
	printf("NETWROK-BYTE-ORDER = %#x\n", sip_addr.s_addr);
	
	inet_pton(AF_INET, argv[1], &sip_addr);
	printf("NETWROK-BYTE-ORDER = %#x \n", sip_addr.s_addr);
	
	inet_ntop(AF_INET, &sip_addr, str, INET_ADDRSTRLEN);
	printf("IP_ADDR = %s\n", str);
	return 0;
}