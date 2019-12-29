#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "tmeas.h"

/* define the number of threads to create */
#define NUM_THREADS	4

void* my_pthread_function( void *ptr );

float result=1;
int n=1;
int x=3;
int nmax;

/* initialize mutex */
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	printf("Input the exponent: ");
	scanf("%d",&x);
	printf("Input n: ");
	scanf("%d", &nmax);
	pthread_t thread_array[NUM_THREADS];
     	int i, thr;
	double t;
	tstart();
	for( i = 0; i < NUM_THREADS; i++ )
	{
		thr = pthread_create( &thread_array[i], NULL, my_pthread_function, (void *)i );
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
	}


	for( i = 0; i < NUM_THREADS; i++ )	
		pthread_join( thread_array[i], NULL);
	t = tstop();
	printf("The result e^%d: %f\n",x,result);
	double mathres = pow(M_E,x);
	printf("The result from math library is: %lf\n",mathres);
	printf("The difference between our result and math library is %lf\n",result-mathres);
	printf("It took %lf secs\n",t);
	return EXIT_SUCCESS;    
}

void* my_pthread_function( void *thr_data )
{	while(n < nmax){
		int ncopy,id;
		long fac=1;
		id=(int)thr_data;
		//printf("Im %d",id);
		pthread_mutex_lock( &my_mutex );
		ncopy=n;
		//printf("%d ",ncopy);
		n++;
		pthread_mutex_unlock( &my_mutex );
		for(int i = 1; i<=ncopy; i++){
			fac*=i;
		}
		//printf("fac is %d\t",fac);
		pthread_mutex_lock( &my_mutex );
		result+=(pow(x,ncopy) / fac);
		//printf("%f\n",result);
		pthread_mutex_unlock( &my_mutex );
	}
}

