#include "stdio.h"
#include "omp.h"

#define  N  100

int main(int argc, char * argv[])
{
	int shared_data = 0;
	int i;

	#pragma omp parallel num_threads(2) shared(shared_data) private(i)
	{
		#pragma omp for
			for (i = 0; i < N; i++)
				shared_data ++;
	}
	printf ("The result is %d\n", shared_data);

	return 0;
}
