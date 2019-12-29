#include <stdio.h>
#include <math.h>		
#include <stdlib.h>	
#include <pthread.h>
#include "tmeas.h"


/* define the number of threads to create */

float result=0;
float h;
int numthr;

void* integral_part(void *thr_data);
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

int main()
{
	printf("How many parts do you want? ");
	scanf("%d",&numthr);
	numthr++;
	h=(1-0) / ((float)numthr-1);
	pthread_t thread_array[numthr];
     	int i, thr;

	float t;
	tstart();
	for( i = 0; i < numthr; i++ )
	{
		thr = pthread_create( &thread_array[i], NULL, integral_part, (void *)i );
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
	}
	
	
	for( i = 0; i < numthr; i++ )	
		pthread_join( thread_array[i], NULL);
	
	result = result * 4 * h;

	t=tstop();
	printf("The aproximate value of the integrate is: %f\n", result);
	printf("It took %f seconds\n",t);
	return EXIT_SUCCESS;

}

void* integral_part( void *thr_data )
{
	float a,b,aux;
	int id;
	id=(int) thr_data;

	aux=1 / (1 + pow((id * h), 2));
	if(id == 0 || id == numthr-1) aux/=2;
	printf("Im %d and my result is %f\n",id,aux);
	pthread_mutex_lock(&mut);	
	result += aux;
	pthread_mutex_unlock(&mut);
}
