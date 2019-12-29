/**
	Exercise 2.

	Author: María Dolón.

	Date: January 2018
*/

#include <stdio.h>
#include <math.h>

// A sample function whose definite integral's 
// approximate value is computed using Trapezoidal 
// rule 
float y(float x){ 
    // Declaring the function f(x) = 1/(1+x*x) 
    return 1/(1+x*x); 
} 

int main (int argc, char *argv[]){{
	int numero_intervalo_inicial =  atoi(argv[1]); //a
    int numero_intervalos = atoi(argv[2]);//i
	int h = atoi(argv[3]);

    // Computing sum of first and last terms 
    // in above formula 
    float area_parcial = (y(a)+y(b))+ 2*y(numero_intervalo_inicial+numero_intervalos*h); 
	
	return area_parcial;
}