#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	
	int rst;

	char message[]="Welcome to Linux Network Programming!";

	int yes = 1;
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	
	
#if 1
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
#endif
	
	// memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	// serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_port=htons(atoi("3333"));
	
	bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	
	listen(serv_sock, 10);
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	printf("Connected to the client port --> %d\n", htons(clnt_addr.sin_port));
	
	rst = send(clnt_sock, message, sizeof(message), 0);
	printf("rst : %d\n", rst);
	//write(clnt_sock, message, sizeof(message));

#if 1
	printf("Enter to close the socket!!!");
	getchar();
#endif

	close(clnt_sock);	
	close(serv_sock);
	return 0;
}
