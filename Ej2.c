#include <stdio.h>
#include <math.h>		
#include <stdlib.h>	
#include <pthread.h>
#include "tmeas.h"


/* define the number of threads to create */
#define NUM_THREADS	40

float result=0;
float threads=40;

void* ecuation(void *thr_data);
pthread_mutex_t my_mutex=PTHREAD_MUTEX_INITIALIZER;

int main()
{
	pthread_t thread_array[NUM_THREADS];
     	int i, thr;
	
	for( i = 0; i < NUM_THREADS; i++ )
	{
		thr = pthread_create( &thread_array[i], NULL, ecuation, (void *)i );
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
	}
	
	
	for( i = 0; i < NUM_THREADS; i++ )	
		pthread_join( thread_array[i], NULL);

	printf("The aproximate value of the integrate is: %f", 4*result);
	return EXIT_SUCCESS;

}

void* ecuation( void *thr_data )
{
	float t;
	tstart();
	float a;
	float b;
	float h;
	float ac;
	int id;
	id=(int) thr_data;
	pthread_mutex_lock(&my_mutex);
	a=(1/threads)*(id);
	b=(1/threads)*(id+1);
	h= 1/threads;
	ac=0;
	ac=(1/(1+pow((id*h),2)));
	result=result+h*(((1/1+pow(a,2))+(1/1+pow(b,2)))/2+ac);
	pthread_mutex_unlock(&my_mutex);
	t=tstop();
	printf("Im thread %d and i last %f time\n",id,t);

}


