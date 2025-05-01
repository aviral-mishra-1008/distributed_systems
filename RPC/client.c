#include "transfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>

#define MAX_LEN 255

typedef struct{
    char username[MAX_LEN];
    char password[MAX_LEN];
}user;

int users = 2;
int i;

user userList[2] = {
    {"aviral","1234"},
    {"ayushman","2345"}
};

int authenticate(char *username, char *password){
    int res = 0;
    for(i=0; i<users; i++){
        if(userList[i].username==username && userList[i].password==password){
            res = 1;
            break;
        }
    }
    return res;
}

int main(int argc, char *argv[]){

    if(argc!=3){
        printf("Usage -> filename server filename\n");
        exit(1);
    }

    int *result;
    CLIENT *client;
    file_data data;
    FILE *fp = NULL;
    char user[MAX_LEN];
    char pass[MAX_LEN];

    printf("Welcome to RPCGEN\n\n");
    printf("Enter your username: ");
    fgets(user, MAX_LEN, stdin);
    printf("Enter your password: ");
    fgets(pass, MAX_LEN, stdin);

    if(authenticate(user,pass)){
        printf("You are successfully authenticated! Welcome Mr. %s\n\n",user);
    }

    client = clnt_create(argv[1], FILE_TRANSFER_PROG, FILE_TRANSFER_VERS, "tcp");
    if(fp==NULL){
        fp = fopen(argv[2],"r");
        if(fp==NULL){
            printf("Cannot open file");
            exit(1);
        }
    }

    int bytes = fread(data.data, 1, MAX_DATA, fp);
    data.len = bytes;

    result = send_file_1(&data,client); 
    //this goes to the server, the file_data pointer is sent and then the svc_req is the client and this is received at send_data_1_svc

    if(result==0){
        printf("File sent over network\n");
    } else{
        printf("Error sening file check server for more errors\n");
    }

    fclose(fp);
    clnt_destroy(client);
    return 0;
}

