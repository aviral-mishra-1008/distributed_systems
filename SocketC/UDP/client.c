#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8002
#define IPADDR "127.0.0.1"

int main(){
    int cliSock;
    if((cliSock = socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("Cannot make socket");
        exit(1);
    }

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr(IPADDR);

    while(1){
        char buffer[1024];
        char rcvbuff[1024];

        int len = sizeof(client);

        printf("Enter: ");
        fgets(buffer, 1024, stdin);
        sendto(cliSock, (char *)buffer, strlen(buffer), 0, (struct sockaddr*)&client, len);
        int n = recvfrom(cliSock, (char *)rcvbuff, 1024, MSG_WAITALL, (struct sockaddr*)&client, &len);
        rcvbuff[n] = '\0';
        printf("Server Response: %s\n",rcvbuff);
    }
    close(cliSock);
    return 0;
}