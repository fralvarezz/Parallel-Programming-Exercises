/**
	Exercise 6.

	Author: María Dolón.

	Date: January 2018
*/

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define L 4

int main(int argc, char *argv){

	int limite_superior=0;
	int numero_revisando=2;
	int posicion=0;
	//srand(time(NULL));
	//omp_set_num_threads(4);

	printf("Insert limit of the array with nature numbers:\n");
	fscanf(stdin,"%d",&limite_superior);
	int array_numeros[limite_superior];

	//Create array with nature numbers, start in 2 - specific of the sieve of Erasthothenes
	for(int i=2; i<= limite_superior; i++){
		array_numeros[i]=i;
		//fprintf(stdout, "%d,", array_numeros[i]);
	}

	//double start = omp_get_wtime();
	#pragma omp parallel for private(h)
	//#pragma omp parallel for reduction (+:posicion) private(h)
	
	for(int j =2; (j*j)<=limite_superior; j++){
		if(array_numeros[j]!=0){
			posicion = j;
			for(int h=2; posicion < limite_superior; h++){
				posicion = j*h;
				array_numeros[posicion] = 0;
			}
		}
	}
	//double end = omp_get_wtime();
	
	fprintf(stdout, "Prime numbers: ");
	for(int g = 0; g < limite_superior; g++){
		if(array_numeros[g] != 0){
			fprintf(stdout, "%d,", array_numeros[g]);
		}
	}

	//fprintf(stdout, "Time: %lf\n",end-start);
}
