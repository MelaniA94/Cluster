#include <stdio.h>
#include <cmath>
#include <mpi.h>

void work(int rank);

int main() {
	int myrank, numprocs;
	/*variables used for gathering timing statistics*/
	double mytime, maxtime, mintime, avgtime;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Barrier(MPI_COMM_WORLD); /*synchronize all processes*/
	mytime = MPI_Wtime(); /*get time just before work section */
	work(myrank);
	mytime = MPI_Wtime() - mytime; /*get time just after work section*/
	/*compute max, min, and average timing statistics*/
	MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myrank == 0) {
		avgtime /= numprocs;
		printf("Min: %lf Max: %lf Avg: %lf\n\n", mintime, maxtime, avgtime);
	}
	MPI_Finalize();
	return(0);
}

void work(int rank) {
	int start;
	int end = (1000 * rank + 999);
	bool Is_prime;

	if (rank == 0) start = 2;
	else start = 1000 * rank;
	printf("Prime numbers between %d and %d : ", (1000 * rank) , end);
	for (start; start <= end; start++)
	{
		Is_prime = true;
		for (int i = 2; i <= sqrt(start); i++)
		{
			if (start % i == 0) {
				Is_prime = false;
				break;
			}
		}
		if (Is_prime) printf("%d, ", start);
	}
	printf("\b\b  \n\n");
}