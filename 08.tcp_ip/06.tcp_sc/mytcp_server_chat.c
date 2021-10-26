

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int listen_socket, client_socket;
	
	if(argc < 2){
		fprintf(stderr, "Usage : %s <port-number>\n", argv[0]);
		exit(1);
	}
	
    printf("Creating socket...\n");
    
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == -1) {
        perror("socket failed");
        return 1;
    }

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(atoi(argv[1]));

    printf("Binding socket to local address...\n");
    if (bind(listen_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        return 1;
    }
    
    printf("Listening...\n");
    if (listen(listen_socket, 10) < 0) {
        perror("listen failed");
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(listen_socket, &master);
    int max_socket = listen_socket;

    printf("Waiting for connections...\n");


    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            perror("select failed");
            return 1;
        }

        for(int i=1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {
                if (i == listen_socket) {
					int sin_size = sizeof(struct sockaddr_in);
                    client_socket = accept(listen_socket, 
									(struct sockaddr*)&client_addr, &sin_size);
                    if (client_socket == -1) {
                        perror("accept failed");
                        return 1;
                    }
					
                    FD_SET(client_socket, &master);
                    if (client_socket > max_socket)
                        max_socket = client_socket;

					printf("New connection from %s and port #%d\n", 
									inet_ntoa(client_addr.sin_addr), 
									ntohs(client_addr.sin_port));

                } else {
                    char buf[1024];
                    int bytes_received = recv(i, buf, 1024, 0);
                    if (bytes_received < 1) {
                        FD_CLR(i, &master);
                        close(i);
                        continue;
                    }

                    int j;
                    for (j = 1; j <= max_socket; ++j) {
                        if (FD_ISSET(j, &master)) {
                            if (j == listen_socket || j == i)
                                continue;
                            else
                                send(j, buf, bytes_received, 0);
                        }
                    }
                }
            } //if FD_ISSET
        } //for i to max_socket
    } //while(1)



    printf("Closing listening socket...\n");
    close(listen_socket);

    printf("Finished.\n");

    return 0;
}
