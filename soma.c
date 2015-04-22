/* Código original disponível em: http://sbel.wisc.edu/Courses/ME964/2012/Lectures/lecture0419.pdf */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int myRank, nprocs,i, n;
    int *result, *data_l;
    const int dimArray = 2;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    data_l = (int *) malloc(dimArray*sizeof(int));
    for (i = 0; i < dimArray; ++i) data_l[i] = (i+1)*myRank;
    for (n = 0; n < nprocs; ++n)
    {
        if( myRank == n )
        {
            for(i=0; i<dimArray; ++i) printf("Process %d. Entry: %d. Value: %d\n", myRank, i, data_l[i]);
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    result = (int *) malloc(dimArray*sizeof(int));
    MPI_Scan(data_l, result, dimArray, MPI_INT, MPI_PROD, MPI_COMM_WORLD);//Alteração para realizar o Produto dos valores
    for (n = 0; n < nprocs; ++n)
    {
        if (myRank == n)
        {
            printf("\n Post Scan - Content on Process: %d\n", myRank);
            for (i = 0; i < dimArray; ++i) printf("Entry: %d. Scan Val: %d\n", i, result[i]);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
