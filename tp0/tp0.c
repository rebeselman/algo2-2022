#include "tp0.h"
#include <stdio.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y){
	int aux = *x;
	*x = *y;
	*y = aux;
}


int maximo(int vector[], int n){
	if (n == 0)
		return -1;
	int aux = vector[0];
	int index = 0;
	
	for (int i = 1; i < n; i++){
		if (vector[i] > aux){
			aux = vector[i];
			index = i;
		}
	}
	return index;	
}


int comparar(int vector1[], int n1, int vector2[], int n2){
	int largo;
	if (n1 < n2)
		largo = n1;
	else
		largo = n2;
	for (int i= 0; i < largo; i++){
		if (vector1[i] > vector2[i])
			return 1;
		else if (vector1[i] < vector2[i])
			return -1;
	}
	if (n1 < n2)
		return -1;
	else if (n2 < n1)
		return 1;
	return 0;
}


void seleccion(int vector[], int n){
	int largo = n;
	while (largo > 0){
		int indiceMax = maximo(vector, largo);
		swap(&vector[largo-1], &vector[indiceMax]);
		largo -= 1;
	}
}
