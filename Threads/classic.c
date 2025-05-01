#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int num1;
    int num2;
    int res;
}nums;

void *sum_nums(void *arg){
    nums *num = (nums*)arg;
    num->res = num->num1+num->num2;
    return NULL;
}

void *prod_num(void *arg){
    nums *num = (nums *)arg;
    num->res = num->num1*num->num2;
    return NULL;
}

int main(){
    int a,b;
    printf("Enter number1: ");
    scanf("%d",&a);
    printf("Enter number2: ");
    scanf("%d",&b);

    nums arg1 = {a,b};
    nums arg2 = {a,b};

    pthread_t sumThread, prodThread;

    pthread_create(&sumThread, NULL,sum_nums,&arg1);
    pthread_create(&prodThread, NULL,prod_num,&arg2);

    pthread_join(sumThread,NULL);
    pthread_join(prodThread,NULL);

    printf("Sum: %d Prod: %d\n",arg1.res, arg2.res);

    return 0;
}