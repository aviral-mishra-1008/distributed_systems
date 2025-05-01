#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX 1024

int main(){
    int key = ftok("shmfile",65);
    int shmid = shmget(key, MAX, 0666);
    if (shmid == -1) {
        perror("Shared memory access failed");
        exit(1);
    }

    char *shm_mem = (char *)shmat(shmid,NULL,0);
    while(1){
        if(strlen(shm_mem)>0){
            printf("The value at memory: %s\n",shm_mem);
            shm_mem[0] = '\0';
        }

        if(strncmp(shm_mem, "exit" ,4)==0){
            break;
        }
    }

    shmdt(shm_mem);
    return 0;
}