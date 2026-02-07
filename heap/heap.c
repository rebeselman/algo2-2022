#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
const size_t CAPACIDAD_INICIAL = 20;
const int NUM_PARA_REDIMENSIONAR_0 = 2;
const int NUM_PARA_REDIMENSIONAR_1 = 4;
/* ******************************************
 * 	Definición de del struct del heap		* 
 ********************************************/


/* Tipo utilizado para el heap. */
struct heap {
	void** datos;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;
};

/* ********************************************
 * Definición de funciones auxiliares del heap* 
 **********************************************/
size_t posicion_hijo_izq(size_t pos_padre){
	return 2*pos_padre + 1;
} 

size_t posicion_hijo_der(size_t pos_padre){
	return 2*pos_padre + 2;
}

size_t posicion_padre(size_t pos_hijo){
	return (pos_hijo -1)/2;
}   
 


void intercambiar_en_arreglo(void** arreglo, size_t pos_1, size_t pos_2){
	void* aux = arreglo[pos_1];
	arreglo[pos_1] = arreglo[pos_2];
	arreglo[pos_2] = aux;
}


// LLeva un elemento de abajo hacia arriba a la posición que corresponga
void uppheap(void** arreglo, size_t pos_hijo, cmp_func_t comparar){
	if (pos_hijo == 0)return;
	size_t pos_padre = posicion_padre(pos_hijo);
	if (comparar(arreglo[pos_padre], arreglo[pos_hijo]) < 0){
		intercambiar_en_arreglo(arreglo, pos_padre, pos_hijo);
		uppheap(arreglo, pos_padre, comparar);
	}
}

// LLeva un elemento de arriba hacia abajo a la posición 
void downheap(void** arreglo, size_t pos_padre, cmp_func_t comparar, size_t cantidad){
	if (pos_padre == cantidad -1)return;
	size_t pos_hijo_izq = posicion_hijo_izq(pos_padre);
	size_t pos_hijo_der = posicion_hijo_der(pos_padre);
	if ((pos_hijo_izq < cantidad && comparar(arreglo[pos_padre], arreglo[pos_hijo_izq]) < 0) || (pos_hijo_der < cantidad && comparar(arreglo[pos_padre], arreglo[pos_hijo_der]) < 0)){
		if (pos_hijo_izq < cantidad && pos_hijo_der < cantidad){
			if (comparar(arreglo[pos_hijo_izq], arreglo[pos_hijo_der]) > 0){
				intercambiar_en_arreglo(arreglo, pos_padre, pos_hijo_izq);
				downheap(arreglo, pos_hijo_izq, comparar, cantidad);
			}
			else{
				intercambiar_en_arreglo(arreglo, pos_padre, pos_hijo_der);
				downheap(arreglo, pos_hijo_der, comparar, cantidad);
			}
		}
		else if (pos_hijo_izq < cantidad){
			intercambiar_en_arreglo(arreglo, pos_hijo_izq, pos_padre);
			downheap(arreglo, pos_hijo_izq, comparar, cantidad);
		}
		else{
			intercambiar_en_arreglo(arreglo, pos_hijo_der, pos_padre);
			downheap(arreglo, pos_hijo_der, comparar, cantidad);
		}
	}
	
}
bool redimensionar(heap_t* heap, size_t capacidad_nueva){
	void** nuevo_arreglo = realloc(heap->datos, capacidad_nueva*sizeof(void*));
	if (nuevo_arreglo == NULL){
		free(heap->datos);
		return false;
	}
	heap->datos = nuevo_arreglo;
	heap->capacidad = capacidad_nueva;
	return true;
}


// Le da a un arreglo forma de heap
void heapify(void** arreglo, cmp_func_t cmp, size_t cantidad){
	for (int i = (int)cantidad -1; i > -1; i--){
		downheap(arreglo, (size_t)i, cmp, cantidad);
	}
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cmp, cant);
	size_t pos_final = cant-1;
	for (size_t i = 0; i < cant; i++){
		intercambiar_en_arreglo(elementos, 0, pos_final);
		downheap(elementos, 0, cmp, pos_final);
		pos_final--;
	}
}

/* ******************************************
 *  Definición de las primitivas del heap	* 
 ********************************************/

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap_nuevo = malloc(sizeof(heap_t));
	if (!heap_nuevo)return NULL;
	void** arreglo = malloc(CAPACIDAD_INICIAL*sizeof(void*));
	if (!arreglo){
		free(heap_nuevo);
		return NULL;
	}
	heap_nuevo->datos = arreglo;
	heap_nuevo->cantidad = 0;
	heap_nuevo->capacidad = CAPACIDAD_INICIAL;
	heap_nuevo->cmp = cmp;
	return heap_nuevo;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar 
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	if (!heap) return NULL;
	for (size_t i = 0; i < n; i++){
		heap->datos[i] = arreglo[i];
	}
	heapify(heap->datos, cmp, n);
	heap->cantidad = n;
	return heap;
	
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap   
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
	for (size_t i = 0; i < heap->cantidad; i++){
		if (destruir_elemento) destruir_elemento(heap->datos[i]);
	}
	free(heap->datos);
	free(heap);
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	if (heap->cantidad == 0)return true;
	else return false;
}

/* Agrega un elemento al heap.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.				
 */
bool heap_encolar(heap_t *heap, void *elem){
	if (heap->capacidad == heap->cantidad){
		if (!redimensionar(heap, NUM_PARA_REDIMENSIONAR_0*heap->capacidad)) return false;
	}
	heap->datos[heap->cantidad] = elem;
	heap->cantidad++;
	uppheap(heap->datos, heap->cantidad-1, heap->cmp);
	return true;											
}
/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.  
 */
void *heap_desencolar(heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	if ((heap->cantidad*NUM_PARA_REDIMENSIONAR_1 <= heap->capacidad) && (heap->capacidad != CAPACIDAD_INICIAL)){	
		if (!redimensionar(heap, (heap->capacidad)/NUM_PARA_REDIMENSIONAR_1)) return false;
	}
	void* dato = heap->datos[0];
	intercambiar_en_arreglo(heap->datos, 0, heap->cantidad -1);
	heap->cantidad--;
	downheap(heap->datos, 0, heap->cmp, heap->cantidad);
	return dato;
}
