#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char *path = "myfile.txt";
    struct stat s;

    if(stat(path,&s)==0){
        printf("Size is: %d\n",(int)s.st_size);
    }
    return 0;
}