#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define ARRAY 5
#define NUM_PER_ARRAY 5

int minPerArray[ARRAY];
int result; 

void map(int array[NUM_PER_ARRAY], int pos){
    int minEle = INT_MAX;
    for(int i=0; i<NUM_PER_ARRAY; i++){
        minEle = MIN(minEle,array[i]);
    }
    minPerArray[pos] = minEle; 
}

void reduce(){
    int minEle = INT_MAX;
    for(int i=0; i<ARRAY; i++){
        minEle = MIN(minEle, minPerArray[i]);
    }
    result = minEle;
}

int main(){
    int nums[ARRAY][NUM_PER_ARRAY] = {
        {5,2,1,3,2},
        {9,-1,2,3,8},
        {7,7,7,7,7},
        {-1,-4,0,12,1},
        {9,3,1,7,8}
    };

    for(int i=0; i<ARRAY; i++){
        int temp[NUM_PER_ARRAY];
        for(int j=0; j<NUM_PER_ARRAY; j++){
            temp[j] = nums[i][j];
        }
        map(temp,i);
    }

    reduce();

    printf("The minimum element found is: %d\n",result);
    return 0;
}