#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8002

int main(){
    int serSock;
    if((serSock = socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("Cannot make socket");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(serSock, (struct sockaddr*)&server, sizeof(server))==-1){
        perror("Cannot bind");
        exit(1);
    }

    while(1){
        char buffer[1024];
        struct sockaddr_in client;
        int len = sizeof(client);

        int n = recvfrom(serSock, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&client, &len);
        buffer[n] = '\0';
        for(int i=0; i<n; i++){
            if(buffer[i]==' ' || (buffer[i]>='A' && buffer[i]<='Z')) continue;
            buffer[i] = buffer[i]-'a'+'A';
        }
        sendto(serSock, (char *)buffer, n, 0, (struct sockaddr*)&client, len);
    }
    close(serSock);
    return 0;
}