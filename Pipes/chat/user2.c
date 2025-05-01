#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


#define MAX_SIZE 1024

int main(){
    char *path = "/tmp/myfifo";

    char str[MAX_SIZE-1];
    char sent[MAX_SIZE];

    while(1){
        int fd = open(path,O_RDWR);
        int bytesRead = read(fd,str,MAX_SIZE-1);
        str[bytesRead] = '\0';
        printf("Received: %s\n",str);

        if((strcmp(str,"end"))==0){
            close(fd);
            break;
        }

        printf("Send: ");
        fgets(sent,MAX_SIZE,stdin);
        write(fd,sent,MAX_SIZE);

        close(fd);
    }

    return 0;
}