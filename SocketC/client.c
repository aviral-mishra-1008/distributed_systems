#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024
#define IP_ADDR "127.0.0.1"


int main(){
    int cliSock;
    if((cliSock=socket(AF_INET, SOCK_STREAM, 0))==-1){
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in client;
    client.sin_port = htons(PORT);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(IP_ADDR);

    if(connect(cliSock, (struct sockaddr*)&client, sizeof(client))==-1){
        perror("Failed to connect!");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int bytesRead = recv(cliSock, buffer, BUFFER_SIZE-1,0);
    send(cliSock, buffer, bytesRead, 0);
    buffer[bytesRead] = '\0';
    printf("Received from server: %s\n",buffer);
    close(cliSock);
    return 0;
}