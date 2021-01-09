#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 

int main(int argc, char** argv)
{
	int my_rank;
	int msg[6];
	int return_msg[6];
	int number_of_processes;
	MPI_Status status;
	int i, j;
	time_t t;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		srand((unsigned)time(&t));
		for (i = 1; i < number_of_processes; i++) {
			// To Generate 6 random numbers
			for (j = 0; j < 6; j++) {
				msg[j] = rand() % 100;
			}
			// Send - random numbers
			//MPI_Send(message,strlen(message)+1,MPI_CHAR,1,99,MPI_COMM_WORLD);
			MPI_Send(msg, 7, MPI_INT, i, 99, MPI_COMM_WORLD);

			// Receive the multiplied numbers
			//MPI_Recv(message,strlen(message)+1,MPI_CHAR,0,99,MPI_COMM_WORLD,&status);
			MPI_Recv(return_msg, 7, MPI_INT, i, 99, MPI_COMM_WORLD, &status);

			// Printing the received numbers(multiplied)
			printf("Return from process %d to process 0:", i);
			for (j = 0; j < 6; j++) {
				printf("% d ", return_msg[j]);
			}
			printf("\n");
		}
	}
	else {
		// Receive the random numbers
		MPI_Recv(msg, 7, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
		// Print the received numbers
		printf("Process %d received from process 0:", my_rank);
		for (j = 0; j < 6; j++) {
			printf("% d ", msg[j]);
			return_msg[j] = msg[j] * 3;
		}


		// Send the multiplied numbers 
		MPI_Send(return_msg, 7, MPI_INT, 0, 99, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}