#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<time.h>
#include"tmeas.h"

int main() 
{
srand(time(NULL));

int n_ec;
printf("Insert number of ecuations and variables: ");
scanf("%d", &n_ec);

int i;
int j;
double ecuations[n_ec][n_ec];
int aux=0;


ecuations[0][0]=12;
ecuations[0][1]=6;
ecuations[1][0]=5;
ecuations[1][1]=3;
ecuations[1][2]=1;
ecuations[2][0]=12;
ecuations[2][1]=1;
ecuations[2][2]=2;
ecuations[2][3]=2;




/*for(i=0;i<n_ec;i++){
printf("Ecuation number %d\n\n", i);
	for(j=0;j<i+2;j++){
		aux = rand() % 11;
		while(aux==0){
		 aux = rand() % 11;
		}
		if(rand()%2==0){
		 aux=-aux;
		}
		ecuations[i][j]=aux;
		printf("X%d = %lf\n", j, ecuations[i][j]);
	}
}*/

clock_t tstart, tfinish;
tstart = clock();
double time;

//fragment for paralelization
double res[n_ec];
res[0]= ecuations[0][0]/ecuations[0][1];
printf("%lf", res[0]);



for(i=1;i<n_ec;i++){
res[i]=ecuations[i][0];
	
	#pragma omp parallel for
	for(j=1;j<i+1;j++){
	#pragma omp atomic
	res[i]-=(ecuations[i][j]*res[j-1]);
	}
	
	//#pragma omp parallel for reduction(-:res)
	/*for(j=i;j<n_ec;j++){ //suma por cada fila
	res[j]-=(ecuations[j][i]*res[i-1]);
	}*/

res[i]=res[i]/ecuations[i][i+1];
}

tfinish = clock();

time = (double) (tfinish - tstart) / CLOCKS_PER_SEC;

printf("Time: %lf\n", time); 



for(i=0;i<n_ec;i++){
	printf("Result of variable%d: %lf\n", i, res[i]);
}


}
