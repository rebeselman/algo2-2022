#include "pila.h"
#include <stdlib.h>

const int capacidad_inicial = 20;
const int num_para_redimensionar_0 = 2;
const int num_para_redimensionar_1 = 4;
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void){
	pila_t* pila_nueva = malloc(sizeof(pila_t));
	if (pila_nueva ==  NULL) return NULL; 
	void** arreglo_datos = malloc(capacidad_inicial*sizeof(void*));
	if (arreglo_datos == NULL){
		free(arreglo_datos);
		return NULL;
	}
	pila_nueva -> datos = arreglo_datos;
	pila_nueva -> cantidad = 0;
	pila_nueva -> capacidad = capacidad_inicial;
	return pila_nueva;
}


bool pila_redimensionar(pila_t* pila, size_t capacidad_nueva){

	void** nuevo_arreglo = realloc(pila->datos, capacidad_nueva*sizeof(void*));
	if (nuevo_arreglo == NULL){
		free(pila->datos);
		return false;
	}
	pila->datos = nuevo_arreglo;
	pila->capacidad = capacidad_nueva;
	return true;
}

void pila_destruir(pila_t* pila){
	free(pila->datos);
	free(pila);
}


bool pila_esta_vacia(const pila_t* pila){
	return (pila->cantidad == 0);
}


bool pila_apilar(pila_t* pila, void* valor){
	if (pila->capacidad == pila->cantidad){
		bool res = pila_redimensionar(pila, (pila->capacidad)*num_para_redimensionar_0);
		if (res == false) return false; 
	}
	pila->datos[pila->cantidad] = valor; 
	pila ->cantidad = (pila ->cantidad)+1;
	return true;
}


void* pila_ver_tope(const pila_t* pila){
	if (pila_esta_vacia(pila)) return NULL;
	size_t indice_tope = pila->cantidad;
	return pila->datos[indice_tope-1];
}


void* pila_desapilar(pila_t* pila){
	if (pila_esta_vacia(pila)) return NULL;
	if ((pila->cantidad*num_para_redimensionar_1 <= pila->capacidad) && (pila->capacidad != capacidad_inicial)){	
		bool res = pila_redimensionar(pila, (pila->capacidad)/num_para_redimensionar_0);
		if (res == false) return NULL;
	}
	void* elemento_tope = pila->datos[pila->cantidad-1];
	pila->cantidad = pila->cantidad-1;
	return elemento_tope;
}











