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

	mpz_t big_int, big_size, sqrt_limit, chunk_size, chunk_rem;
	mpz_t count, start_limit, end_limit;
	mpz_init_set_str(big_int, "1111111111111111111", 10);

	//Calculate Square Root Limit
	mpz_init(sqrt_limit);
	mpz_sqrt(sqrt_limit, big_int);
	gmp_printf("sqrt: %Zd\n", sqrt_limit);

	//Calculate Chunk Size
	mpz_init(chunk_size);
	mpz_init(chunk_rem);
	mpz_init_set_ui(big_size, size);
	mpz_cdiv_qr(chunk_size, chunk_rem, sqrt_limit, big_size);
	gmp_printf("chunk size: %Zd\n", chunk_size);

	//Calculate Limits
	mpz_init(start_limit);
	mpz_init(end_limit);
	if(rank==0){
		mpz_init_set_ui(start_limit, 2);
	}
	else{
		mpz_mul_ui(start_limit, chunk_size, rank);
	}
	mpz_add(end_limit, start_limit, chunk_size);

	//Primality Test
	mpz_init(count);
	mpz_init_set(count, start_limit); //count = start
	while(mpz_cmp(count, end_limit) < 0){
		//check if divisible
		if(mpz_divisible_p(big_int, count)!=0){
			//composite!
			printf("COMPOSITE\n");
			break;
		}
		mpz_add_ui(count, count, 1); //count++
	}

	gmp_printf("number is prime from %Zd to %Zd\n", start_limit, end_limit);

	// last MPI function to be called
	MPI_Finalize();
	return 0;
}
