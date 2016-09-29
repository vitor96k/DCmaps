#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

double **criarMatriz(unsigned long int n){

	unsigned long int i,j;

	double **mat = (double **)malloc(n*sizeof(double *)); 		//ALOCA N PONTEIROS DOUBLE
	for(i=0;i<n;i++){
		mat[i] = (double *)malloc(n*sizeof(double));			//Cada ponteiro alocado aponta para um vetor de doubles;
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			mat[i][j] = -1;
		}
	}
	return mat;
}

void setMatriz(double **m, unsigned long int i, unsigned long int j,double valor){
	m[i][j] = valor;
}

double getMatriz(double **m,unsigned long int i, unsigned long int j){
	return m[i][j];
}

unsigned long int ColOfLessLine (double **m, unsigned long int size, unsigned long int l){

	unsigned long int i;
	unsigned long int co;

	double menor;

	for(i=0;i<=size-1;i++){
		if(m[l][i]>0){
			menor = m[l][i];
			co = i;
			//printf("\npeguei %.2f",menor);
		}		
	}

	for(i=0;i<=size-1;i++){

		if(m[l][i] > 0 && menor > m[l][i]){
			menor = m[l][i];
			co = i;
		}
	}
	//printf("\nMenor : %.2f",menor);
	//printf("\nColuna: %lu",co);
	return co;
}

void printLine(double **m, unsigned long int size, unsigned long int l){

	unsigned long int  u = 0;
	printf("\n");
	while(u<size){
		printf("%.2f  ",m[l][u]);
		u++;
	}
}

void catchZero(double **mat, unsigned long int size){

	unsigned long int i,j;

	for(i=0;i<=size;i++){

		for(j=0;j<=size;j++){

			if(mat[i][j]==0){
				printf("\nVertice: %lu",j);

			}
		}
	}
}