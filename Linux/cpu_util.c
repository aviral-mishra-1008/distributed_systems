#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 1024

int main() {
    FILE *fp;
    float cpu;
    char temp[MAX];
    fp = popen("top -bn1 | grep \"Cpu(s)\" | awk '{print $2}'","r");
    if(fp==NULL){
        perror("Cannot open");
        exit(1);
    }

    fgets(temp,MAX,fp);
    cpu = atof(temp);
    printf("Cpu utilization: %f",cpu);
    return 0;
}