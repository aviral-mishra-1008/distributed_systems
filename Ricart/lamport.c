#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1
#define N 4

typedef struct{
    int timestamp;
    int replies;
    bool in_cs;
    bool requesting;
    int waitQ[N];
}process;

int clock = 0;
process processes[N];

void update_clock(int request_ts){
    if(clock<=request_ts){
        clock = request_ts+1;
    } else{
        clock++;
    }
}

bool can_enter_cs(int pid){
    sleep(2);
    if(processes[pid].requesting && processes[pid].replies==N-1){
        processes[pid].in_cs = TRUE;
        printf("Access Granted to process %d\n",pid);
        return TRUE;
    } else{
        printf("Access Denied to process %d\n",pid);
    }
    return FALSE;
}

void send_release(int pid,int i){
    if(processes[pid].waitQ[i]==1){
        processes[i].replies++;
        processes[pid].waitQ[i] = 0;
    }
    return;
}

void request_cs(int pid){
    printf("Process %d requesting access to the critical section\n",pid);
    sleep(2);
    processes[pid].requesting = TRUE;
    processes[pid].timestamp = ++clock;
    processes[pid].replies = 0;

    for(int i=0; i<N; i++){
        if(i!=pid){
            if(!processes[i].requesting || processes[i].timestamp>processes[pid].timestamp || (processes[i].timestamp==processes[pid].timestamp && i>pid)){
                processes[pid].replies++;
                printf("Process %d grants REPLY\n",i);
                sleep(1);
            }
            else{
                printf("Process %d defers a REPLY\n",i);
                processes[pid].waitQ[i] = 1;
                sleep(1);
            }
        }
    }
}

void release_cs(int pid){
    sleep(2);
    printf("Process %d exiting the critical section\n",pid);
    processes[pid].in_cs = FALSE;
    processes[pid].requesting = FALSE;
    for(int i=0; i<N; i++){
        if(i==pid){
            continue;
        }
        send_release(pid,i);
    }
    sleep(1);
    processes[pid].replies = 0;
    printf("Release  broadcasted\n");
    printf("\n");

}

int main(){
    printf("Initializing the processes......\n");
    for(int i=0; i<N; i++){
        processes[i].requesting = FALSE;
        processes[i].timestamp = clock;
        processes[i].in_cs = FALSE;
        processes[i].replies = 0;
    }

    request_cs(0);
    can_enter_cs(0);
    release_cs(0);

    request_cs(1);
    request_cs(2);
    can_enter_cs(1);
    can_enter_cs(2);
    release_cs(1);
    can_enter_cs(2);
    release_cs(2);

    return 0;
}