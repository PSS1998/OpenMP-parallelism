// Example Chapter 3 OpenMP Program
#include <stdio.h>
#include <math.h>
#include <sys/time.h> 
#include <sys/resource.h>  
#include <omp.h>

double timeGetTime() 
{     
	struct timeval time;     
	struct timezone zone;     
	gettimeofday(&time, &zone);     
	return time.tv_sec + time.tv_usec*1e-6; 
}  


const long int VERYBIG = 100000;
// ***********************************************************************
int main( void )
{
  int i;
  long int j, k, sum;
  double sumx, sumy, total, z;
  double starttime, elapsedtime;
  double starttime1, elapsedtime1;
  double starttime2, elapsedtime2;
  double starttime3, elapsedtime3;
  double starttime4, elapsedtime4;
  int flag1, flag2, flag3, flag4;
  int count;
  // ---------------------------------------------------------------------
  // Output a start message
  printf( "OpenMP Parallel Timings for %ld iterations \n\n", VERYBIG );

  // repeat experiment several times
  for( i=0; i<6; i++ )
  {
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 0;
    count = 0;
    // get starting time
    starttime = timeGetTime();
    // reset check sum and total
    sum = 0;
    total = 0.0;
    
    // Work loop, do some work by looping VERYBIG times
    #pragma omp parallel for     \
      num_threads (4)		 \
      private( sumx, sumy, k, count )   \
      reduction( +: sum, total ) \
      schedule( dynamic, 1000 )
      for( int j=0; j<VERYBIG; j++ )
      {
	if(omp_get_thread_num() == 0 && flag1 == 0){
		flag1 = 1;
		starttime1 = timeGetTime();
	}
	if(omp_get_thread_num() == 1 && flag2 == 0){
		flag2 = 1;
		starttime2 = timeGetTime();
	}
	if(omp_get_thread_num() == 2 && flag3 == 0){
		flag3 = 1;
		starttime3 = timeGetTime();
	}
	if(omp_get_thread_num() == 3 && flag4 == 0){
		flag4 = 1;
		starttime4 = timeGetTime();
	}

	count++;

        // increment check sum
        sum += 1;
       
        // Calculate first arithmetic series
        sumx = 0.0;
        for( k=0; k<j; k++ )
         sumx = sumx + (double)k;

        // Calculate second arithmetic series
        sumy = 0.0;
        for( k=j; k>0; k-- )
         sumy = sumy + (double)k;

        if( sumx > 0.0 )total = total + 1.0 / sqrt( sumx );
        if( sumy > 0.0 )total = total + 1.0 / sqrt( sumy );

	if(omp_get_thread_num() == 0 && count%1000==999){
		elapsedtime1 = timeGetTime() - starttime1;
	}
	if(omp_get_thread_num() == 1 && count%1000==999){
		elapsedtime2 = timeGetTime() - starttime2;
	}
	if(omp_get_thread_num() == 2 && count%1000==999){
		elapsedtime3 = timeGetTime() - starttime3;
	}
	if(omp_get_thread_num() == 3 && count%1000==999){
		elapsedtime4 = timeGetTime() - starttime4;
	}
	
    }
    
    // get ending time and use it to determine elapsed time
    elapsedtime = timeGetTime() - starttime;
  
    // report elapsed time
    printf("Time Elapsed %10d mSecs Total=%lf Check Sum = %ld\n",
                   (int)(elapsedtime * 1000), total, sum );
    printf("Time Elapsed %10d mSecs for Thread %d\n", (int)(elapsedtime1 * 1000), 0);
    printf("Time Elapsed %10d mSecs for Thread %d\n", (int)(elapsedtime2 * 1000), 1);
    printf("Time Elapsed %10d mSecs for Thread %d\n", (int)(elapsedtime3 * 1000), 2);
    printf("Time Elapsed %10d mSecs for Thread %d\n", (int)(elapsedtime4 * 1000), 3);
  }

  // return integer as required by function header
  return 0;
}
// **********************************************************************
