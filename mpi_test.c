#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {

	// initialize MPI
	MPI_Init(&argc, &argv);

	// rank = rank of each process
	// size = number of processes
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("Rank: %d Size: %d\n", rank, size);

	// last MPI function to be called
	MPI_Finalize();
	return 0;
}
