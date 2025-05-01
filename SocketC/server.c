#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main(){
    int socket_fd;
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0))==-1){
        perror("Socket creation failed");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(socket_fd, (struct sockaddr*)&server, sizeof(server))==-1){
        perror("Bind failed");
        exit(1);
    }

    if((listen(socket_fd,10))==-1){
        perror("Listen failed");
        exit(1);
    }

    struct sockaddr_in client;
    int client_socket;
    int client_socklen = sizeof(client);
    if((client_socket = accept(socket_fd, (struct sockaddr*)&client, &client_socklen))==-1){
        perror("Accept failed");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int sent_bytes = send(client_socket, "Hello From Server!", sizeof("Hello From Server!"), 0);
    int received_bytes = recv(client_socket, buffer, sizeof(buffer)-1, 0);
    buffer[received_bytes] = '\0';
    printf("Echo: %s\n",buffer);

    close(socket_fd);
    close(client_socket);
    return 0;
}