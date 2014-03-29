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
	setbuf(stdout, NULL);
	int number_of_digits;
	char *user_input;
	int *composite_arr;

	printf("Enter number of digits : ");
	scanf("%d",&number_of_digits);
	user_input = (char*) malloc(number_of_digits*sizeof(char));

	printf("Enter your number : ");
	scanf("%s",user_input);

	// initialize MPI
	MPI_Init(&argc, &argv);

	// rank = rank of each process
	// size = number of processes
	int rank, size, number, i, even = 0, flag;
	int composite = 0;
	MPI_Request req;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("Rank: %d Size: %d\n", rank, size);

	mpz_t big_int, big_size, sqrt_limit, chunk_size, chunk_rem;
	mpz_t count, start_limit, end_limit;
	mpz_init_set_str(big_int, user_input, 10);

	if (rank == 0){
		if (mpz_divisible_ui_p(big_int, 2) != 0) {
			even = 1;
			printf("The input is composite (even).\n");
		}
	}

	MPI_Bcast(&even, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if( even == 0 ){

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

		// If start_limit is even, add 1 to make it odd
		if (mpz_divisible_ui_p(start_limit, 2) != 0) {
			mpz_add_ui(start_limit, start_limit, 1);
		}
		mpz_add(end_limit, start_limit, chunk_size);

		//Primality Test
		mpz_init(count);
		mpz_init_set(count, start_limit); //count = start
		while(mpz_cmp(count, end_limit) <= 0){
			// gmp_printf("count: %Zd\n", count);
			//check if divisible
			if(mpz_divisible_p(big_int, count)!=0){
				//composite!
				composite = 1;
				break;
			}
			mpz_add_ui(count, count, 2); //count+2, skip even numbers
		}

		// gmp_printf("number is prime from %Zd to %Zd\n", start_limit, end_limit);

		//PROCESS JOIN
		MPI_Barrier(MPI_COMM_WORLD);

		if(rank==0) composite_arr = (int*) malloc(size*sizeof(int));
		MPI_Gather(&composite, 1, MPI_INT, composite_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

		//Only rank 0 will print
		if(rank==0){
			int i;
			for(i=0; i<=size; i++){
				if(i == size){
					printf("The input is prime.\n");
					break;
				}
				if(composite_arr[i] == 1){
					printf("The input is composite.\n");
					break;
				}
			}
		}
	}

	// last MPI function to be called
	MPI_Finalize();
	return 0;
}
