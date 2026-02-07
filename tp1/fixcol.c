#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cola.h"
#include "fixcol.h"

const char NUEVA_LINEA = '\n';
const char BARRA_CERO = '\0';
const int PRIMER_PARAMETRO = 1;
const int SEGUNDO_PARAMETRO = 2;
const int TERCER_PARAMETRO = 3;
const int CANTIDAD_1_PARAMETROS_VALIDOS = 2;
const int CANTIDAD_2_PARAMETROS_VALIDOS = 3;
const int CANTIDAD_1_PARAMETROS_INVALIDOS = 1;
const char* ERROR_PARAMETROS = "Error: Cantidad erronea de parametros";
const char* ERROR_FUENTE = "Error: archivo fuente inaccesible";


void imprimir_linea_ordenada(char* linea, int num_columnas, int num_carac_leidos){
	cola_t* cola = cola_crear();
	int num_filas_parejas = (num_carac_leidos-1)/num_columnas;
	bool caracter_distinto_de_barra_n = false;
	int pos = 0;
	while(linea[pos] != BARRA_CERO){		
		cola_encolar(cola, &linea[pos]);
		pos++;
	}
	while(!cola_esta_vacia(cola)){
		if(num_filas_parejas != 0){
			for(int i = 0; i < num_columnas; i++){
				printf("%c", *(char*)cola_desencolar(cola));
			}
			printf("%c", NUEVA_LINEA);
			num_filas_parejas--;
		}
		else{
			void* caracter = cola_desencolar(cola);
			if (*(char*) caracter != NUEVA_LINEA) caracter_distinto_de_barra_n = true;
			if(caracter_distinto_de_barra_n) printf("%c", *(char*)caracter);
		}
	}			
	cola_destruir(cola, NULL);
}


bool validar_parametros(int arg, char* argv[]){
	if ((arg != CANTIDAD_1_PARAMETROS_VALIDOS && arg != CANTIDAD_2_PARAMETROS_VALIDOS)){
		fprintf(stderr, "%s", ERROR_PARAMETROS);
		return false;
	}
	int primer_parametro = atoi(argv[PRIMER_PARAMETRO]);
	if (primer_parametro <= 0){
		fprintf(stderr, "%s", ERROR_PARAMETROS);
		return false;	
	}
	return true;
}


void imprimir_archivo_columnas(int num_columnas, FILE* archivo){
	char* linea = NULL;
	size_t capacidad = 0;
	size_t leidos;
	while ((leidos = getline(&linea, &capacidad, archivo)) != EOF){
		imprimir_linea_ordenada(linea, num_columnas, (int)leidos);
	}
	free(linea);
	fclose(archivo);
}


FILE* validar_archivo(char* argv[]){
	FILE* archivo = fopen(argv[SEGUNDO_PARAMETRO], "r");
	if (!archivo){
		fprintf(stderr, "%s", ERROR_FUENTE);
		return NULL;			
	}
	return archivo;
}


int main(int arg, char* argv[]){
	if (!validar_parametros(arg, argv)) return -1;
	int numero_columnas = atoi(argv[PRIMER_PARAMETRO]);
	
	if(arg == CANTIDAD_2_PARAMETROS_VALIDOS){
		FILE* archivo = validar_archivo(argv);
		if(!archivo) return -1;
		imprimir_archivo_columnas(numero_columnas, archivo);	
	}
	else imprimir_archivo_columnas(numero_columnas, stdin);	
	return 0;
}

