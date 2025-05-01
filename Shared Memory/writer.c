#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX 1024

int main(){
    int key  = ftok("shmfile",65);
    int shmid = shmget(key,MAX,IPC_CREAT | 0666);
    if(shmid==-1){
        perror("Error ho gawa");
        exit(1);
    }

    char *shm_mem = shmat(shmid,NULL,0);
    while(1){
        printf("Enter your message: ");
        fgets(shm_mem, MAX, stdin);

        if(strncmp(shm_mem,"exit",4)==0){
            break;
        }

        printf("Data written!!\n");
        sleep(1);
    }

    shmdt(shm_mem);
    return 0;
}