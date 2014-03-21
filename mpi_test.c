#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <gmp.h>

void not_prime(mpz_t i) {
	
	mpz_out_str(stdout, 10, i);
	printf(" is not prime.\n");

	int is_init;
	MPI_Initialized(&is_init);
	if (is_init) MPI_Finalize();
	exit(0);
}

int main(int argc, char **argv) {

	// initialize MPI
	MPI_Init(&argc, &argv);

	// rank = rank of each process
	// size = number of processes
	int rank, size, number, i;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("Rank: %d Size: %d\n", rank, size);
	
	// sender process
	if (rank != 0) {
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	// receiving process
	else {
		for (i = 1; i < size; i++) {
			MPI_Recv(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process %d has called\n", number);
		} 
	}

	// last MPI function to be called
	MPI_Finalize();
	return 0;
}
