#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int socket_id;
	struct sockaddr_in server_addr;
	
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server-ip> <port #>\n", argv[0]);
        exit(1);
    }

    printf("Creating socket...\n");
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1){
        perror("socket failed");
        exit(1);
    }
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	server_addr.sin_port = htons(atoi(argv[2]));


    printf("Connecting...\n");
    if (connect(socket_id,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1){
		perror("connect failed");
		exit(1);
	}

    printf("Connected.\n");
    printf("Now ready to chat. Enter message.\n");

    while(1) {

        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_id, &reads);
        FD_SET(0, &reads);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        if (select(socket_id+1, &reads, 0, 0, &timeout) < 0) {
            perror("select failed");
            exit(1);
        }

        if (FD_ISSET(socket_id, &reads)) {
            char buf[4096];
            int bytes_received = recv(socket_id, buf, 4096, 0);
            if (bytes_received < 1) {
                printf("Connection closed by peer.\n");
                break;
            }
			printf("FROM (%d) : %.*s",
                    ntohs(server_addr.sin_port), bytes_received, buf);
        }
		
        if(FD_ISSET(0, &reads)) {
            char buf[4096];
            if (!fgets(buf, 4096, stdin)) break;
            // printf("Sending: %s", buf);
            int bytes_sent = send(socket_id, buf, strlen(buf), 0);
			printf("Sending: (%d bytes) %s", bytes_sent, buf);
        }
    } //end while(1)

    printf("Closing socket...\n");
    close(socket_id);

    printf("Good Bye.\n");
    return 0;
}

