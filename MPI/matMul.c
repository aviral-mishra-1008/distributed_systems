#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4



void initalize_mat(int A[N][N], int B[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            A[i][j] = i+j;
            B[i][j] = i-j;
        }
    }
}

void print_mat(int A[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d,", A[i][j]);
        } printf("\n");
    }printf("\n");
}

int main(int argc, char *argv[]){
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        initalize_mat(A,B);
        print_mat(A);
        print_mat(B);
    }

    int local_rows = N/size;
    int localA[local_rows][N], localC[local_rows][N];

    MPI_Bcast(B,N*N,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(A,local_rows*N,MPI_INT,localA, local_rows*N, MPI_INT,0,MPI_COMM_WORLD);

    for(int i=0; i<local_rows; i++){
        for(int j=0; j<N; j++){
            localC[i][j] = 0;
            for(int k=0; k<N; k++){
                localC[i][j] += localA[i][k]*B[k][j];
            }
        }
    }

    MPI_Gather(localC, local_rows*N, MPI_INT, C, local_rows*N, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==0){
        printf("Result ready: \n\n");
        print_mat(C);
    }

    MPI_Finalize();
    return 0;
}