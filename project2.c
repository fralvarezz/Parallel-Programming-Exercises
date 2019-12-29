/**
	Exercise 2.

	Author: María Dolón.

	Date: January 2018
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main (int argc, char *argv[]){
    int numero_intervalos; //int n
    pid_t pid;
    int resultado_area_hijo = 0;
    int resultado_area_total =0;
    int hijos_vivos = 0;
    int estado;
    int intervalo_hijo ;
    int intervalo_inicial=0;//float x0 = 0; 
    int intervalo_total =1;//float xn = 1; 
	float h; //parameter
	double t;//time     
	// Comprobar parámetros - evaluation of parameters
	if(argc != 2){
		printf("Number of parameters incorrect. You have to put the number of threads.\n");
		exit(1);
	}
// Recoger parámetros - get value of parameters
	numero_intervalos = atoi(argv[1]);
	intervalo_hijo = intervalo_total/numero_intervalos;
	
	// Grid spacing 
	h = (intervalo_total-intervalo_inicial)/numero_intervalos; 

	//Measure time
	tstart();
	//Create threads and each one does an interval
	while (numero_intervalos > 0){
		fprintf (stdout,"Create thread number: %d \n", hijos_vivos);
		pid = fork();
		switch(pid) {
			case -1:
				perror("Error in fork");
				exit(EX_SOFTWARE);
			case 0:
				//Start the thread
				fprintf (stdout,"[Thread %d]: Start to calculate the interval\n",hijos_vivos);
				execl("/home/victor/Escritorio/trapezoidal","trapezoidal", intervalo_inicial,intervalo_hijo, h, NULL);
				perror("Error in running execl");
				fprintf (stderr,"Error in the thread");
				exit(EX_OSERR);
			default:
				intervalo_inicial = intervalo_hijo;
				intervalo_hijo = intervalo_hijo + intervalo_total/numero_intervalos;
				numero_intervalos--;
				hijos_vivos++;
		}
    }

    do {
	// Bucle para relanzar wait por llegada de una señal y no por la muerte de hijo u otra causa
		do {
			resultado_area_hijo=wait(&estado);
			// Adding middle terms in above formula
			resultado_area_total = resultado_area_hijo + resultado_area_total;
			hijos_vivos--;
		} while((resultado_area_hijo==-1) && (errno==EINTR));
		// Comprobate the thread / child
		if ( (resultado_area_hijo==-1) && (errno==ECHILD)) {
			perror ("Error: go out of the wait (porque no existian hijos que reconocer)");
			exit (EX_SOFTWARE);
		}
	}while(hijos_vivos > 0);
	t=tstop();
	
	//Final result
	printf("Value of integral is %f\n",resultado_area_total*(h/2)); 
    printf("time=%lf\n",t);

	return EXIT_SUCCESS;
}
