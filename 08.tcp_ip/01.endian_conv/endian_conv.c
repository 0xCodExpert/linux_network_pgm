#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	unsigned char *addr;
	unsigned int host_addr;
	unsigned int net_addr;
	
	struct sockaddr_in sock_addr;

	host_addr=inet_network("192.168.60.100");
	printf("LITTLE ENDIAN = %#x\n", host_addr);
	addr = (unsigned char *)&host_addr;
	
	printf("little : %#x %#x %#x %#x\n", *addr, *addr++, *addr++, *addr++);
	
	sock_addr.sin_addr.s_addr=htonl(host_addr);
	printf("IP_ADDR = %s\n", inet_ntoa(sock_addr.sin_addr));
	
	net_addr=htonl(host_addr);
	printf("BIG ENDIAN = %#x\n", net_addr);
	sock_addr.sin_addr.s_addr=htonl(net_addr);	
	// sock_addr.sin_addr.s_addr=net_addr;
	host_addr=ntohl(*(&sock_addr.sin_addr.s_addr));
	printf("IP_ADDR = %s\n", inet_ntoa(sock_addr.sin_addr));
	return 0;
}

