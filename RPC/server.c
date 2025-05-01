#include "transfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>

int * send_file_1_svc(file_data *data, struct svc_req *req){
    int result;
    FILE *fp = NULL;

    if(fp==NULL){
        fp = fopen("received_text.txt","w");
        if(fp==NULL){
            printf("cannot open file\n");
            result = -1;
        }
    }

    if(data->len>0){
        int bytesWritten = fwrite(data->data, 1, data->len, fp);
        if(bytesWritten!=data->len){
            printf("Some error writing the file");
            result = -1;
        }
        else{
            result = 0;
        }
    }

    if(fp!=NULL){
        fclose(fp);
    }
    
    return &result;
}