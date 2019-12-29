#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <pthread.h>
#include <math.h>
#include "tmeas.h"

/* define the number of threads to create */
#define NUM_THREADS	2

struct Indexes{
	int first;
	int last;
};

void* my_pthread_function( void *ptr );

float result=0;
int n=1;


/* initialize mutex */
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	printf("Input n: ");
	scanf("%d", &n);
	pthread_t thread_array[NUM_THREADS];
     	int i, thr;
	int missing = n % NUM_THREADS;
	int last=0;
	struct Indexes aux[NUM_THREADS];
	aux[0].first = 1;
	aux[0].last = aux[0].first + n / NUM_THREADS;
	if(missing>0){
		aux[0].last++;
		missing--;
	}	
	double t;
	tstart();
	for( i = 0; i < NUM_THREADS; i++ )
	{
		thr = pthread_create( &thread_array[i], NULL, my_pthread_function, &aux[i]);
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
		if(i>0){
			aux[i].first=aux[i-1].last;
			aux[i].last = aux[i].first + n/NUM_THREADS;
			if(missing>0){
				aux[i].last++;
				missing--;
			}
		}
	}


	for( i = 0; i < NUM_THREADS; i++ )	
		pthread_join( thread_array[i], NULL);
	printf("%f",result);
	result -= log(n);
	t = tstop();
	printf("The result is: %f\n",result);
	printf("It took %lf secs\n",t);
	return EXIT_SUCCESS;    
}

void* my_pthread_function( void *thr_data )
{
	struct Indexes *aux = (struct Indexes*)thr_data;
	int j;
	for(j = aux->first; j < aux->last; j++){
		pthread_mutex_lock( &my_mutex );
		result+=(1.0/(float)j);
		printf("Result is %f and j is %d\n",result,j);
		pthread_mutex_unlock( &my_mutex );
	}
}
