#include "vector.h"
#include "stdlib.h"
#define CAPACIDAD_INICIAL 50
#define REDIMENSIONADOR 2
struct vector {
    void** arreglo;
    size_t capacidad;
    size_t cantidad;
    vector_destruir_dato_t destruir;

};

vector_t* vector_crear(vector_destruir_dato_t destruir){
    vector_t* vector = malloc(sizeof(vector_t));
    if (!vector)return NULL;
    void** arreglo = malloc(CAPACIDAD_INICIAL*sizeof(void*));
    if (!arreglo){
        free(vector);
        return NULL;
    }
    vector->arreglo = arreglo;
    vector->capacidad = CAPACIDAD_INICIAL;
    vector->cantidad = 0;
    vector->destruir = destruir;
    return vector;
}

void vector_destruir(vector_t* vector){
    vector_destruir_dato_t destruir = vector->destruir;
    for (int i = 0; i < vector->cantidad; i++){
        if (destruir) destruir(vector->arreglo[i]);
    }
    free(vector->arreglo);
    free(vector);
}

size_t vector_largo(vector_t* vector){
    return vector->cantidad;
}

bool vector_redimensionar(vector_t* vector, size_t capacidad_nueva){
	void** nuevo_arreglo = realloc(vector->arreglo, capacidad_nueva*sizeof(void*));
	if (nuevo_arreglo == NULL){
		free(vector->arreglo);
		return false;
	}
	vector->arreglo = nuevo_arreglo;
	vector->capacidad = capacidad_nueva;
	return true;
}

bool vector_agregar(vector_t* vector, void* valor){
	if (vector->capacidad == vector->cantidad){
		bool res = vector_redimensionar(vector, (vector->capacidad)*REDIMENSIONADOR);
		if (res == false) return false; 
	}
	vector->arreglo[vector->cantidad] = valor; 
	vector->cantidad = (vector->cantidad)+1;
	return true;
}

void* vector_obtener(vector_t* vector, size_t posicion){
    if (posicion >= vector->cantidad) return NULL;
    return vector->arreglo[posicion]; 
}