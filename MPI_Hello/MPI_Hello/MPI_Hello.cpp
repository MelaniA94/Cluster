#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 

int main(int argc, char** argv)
{   
	
	int msg[6];
	int return_msg[6];
	int my_rank;
	int number_of_processes;
	MPI_Status status;
	int i, a;
	time_t t;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		srand((unsigned)time(&t));
		for (i = 1; i < number_of_processes; i++) {
			// To Generate 6 random numbers
			for (a = 0; a < 6; a++) {
				msg[a] = rand() % 100;
			}
			// Send - random numbers
            MPI_Send(msg, 7, MPI_INT, i, 99, MPI_COMM_WORLD);

			// Receive the multiplied numbers
            MPI_Recv(return_msg, 7, MPI_INT, i, 99, MPI_COMM_WORLD, &status);

			// Printing the received numbers(multiplied)
			printf("Reply from process %d to process 0:", i);
			for (a = 0; a < 6; a++) {
				printf("% d ", return_msg[a]);
			}
			printf("\n");
		}
	}
	else {
		// Receive the random numbers
		MPI_Recv(msg, 7, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
		// Print the received numbers
		printf("Process %d received from process 0:", my_rank);
		for (a = 0; a < 6; a++) {
			printf("% d ", msg[a]);
			return_msg[a] = msg[a] * 3;
		}
		// Send the multiplied numbers 
		MPI_Send(return_msg, 7, MPI_INT, 0, 99, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}