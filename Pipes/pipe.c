#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1024

int main(){
    int pipefd1[2];
    int pipefd2[2];
    int pid;

    pipe(pipefd1);
    pipe(pipefd2);

    if((pid=fork())==-1){
        perror("Cannot fork");
        exit(1);
    }

    if(pid==0){
        char ans[MAX_SIZE]; 
        char *str = "hello I am aviral";
        write(pipefd1[1],str,strlen(str));
        printf("Sent string: %s\n",str);
        read(pipefd2[0],&ans,MAX_SIZE);
        printf("Received string: %s \n",ans);
    }

    else{
        char str[MAX_SIZE]; 
        int rcvb = read(pipefd1[0],&str,MAX_SIZE-1);
        str[rcvb] = '\0';
        for(int i=0; i<rcvb; i++){        
            if(str[i]==' ' || (str[i]>='A' && str[i]<='Z')) continue;
            str[i] = str[i]-'a'+'A';
        }
        write(pipefd2[1],&str,MAX_SIZE);
    }

    return 0;
}