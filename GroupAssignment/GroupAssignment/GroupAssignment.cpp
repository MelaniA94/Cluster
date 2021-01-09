#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv) {

	int ierr, rank, size, root;
	float A[16];
	float B[16];

	float Apart[4];
	float Bpart[4];
	float C;
	float Cpart[4];
	float D;
	float Dpart[16];


	root = 0;
	/* Initiate MPI. */
	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Initialize B and C. */
	if (rank == root) {
		// float A[16] = {1,2,4,5,7,3,2,8,1,9,3,4,1,6,1,1};
		A[0] = 2;
		A[1] = 1;
		A[2] = 1;
		A[3] = 3;
		A[4] = 2;
		A[5] = 5;
		A[6] = 1;
		A[7] = 1;
		A[8] = 3;
		A[9] = 8;
		A[10] = 9;
		A[11] = 2;
		A[12] = 5;
		A[13] = 6;
		A[14] = 1;
		A[15] = 2;



		B[0] = 1;
		B[1] = 1;
		B[2] = 3;
		B[3] = 1;
		B[4] = 5;
		B[5] = 7;
		B[6] = 2;
		B[7] = 1;
		B[8] = 9;
		B[9] = 4;
		B[10] = 1;
		B[11] = 1;
		B[12] = 1;
		B[13] = 1;
		B[14] = 5;
		B[15] = 1;

		// float B[16] = {3,2,1,6,2,3,2,9,2,4,7,4,1,1,2,3};
	}

	ierr = MPI_Barrier(MPI_COMM_WORLD);


	ierr = MPI_Scatter(A, 4, MPI_FLOAT, Apart, 4, MPI_FLOAT, root, MPI_COMM_WORLD);


	ierr = MPI_Scatter(B, 4, MPI_FLOAT, Bpart, 4, MPI_FLOAT, root, MPI_COMM_WORLD);

	for (int j = 0;j < 4;j++) {
		Cpart[j] = Apart[j] * Bpart[j];
	}


	ierr = MPI_Reduce(&Cpart, &C, 4, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == 0) {

		printf("Scaler product with divide and conquer approach=%g\n", C);

		for (int i = 0; i < 16; i++) {
			Dpart[i] = A[i] * B[i];
		}
		for (int k = 0; k < 16; k++) {
			D += Dpart[k];
		}
		printf("Scaler product without using divide and conquer approach=%g\n", D);


	}



	MPI_Finalize();

}
