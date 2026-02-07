#include "heap.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 100
#define TOPE 0
#define REDIMENSION 2
#define DECREMENTO 4

/* ******************************************************************
 *                          Estucturas
 * *****************************************************************/


struct heap{
    void **datos;
    size_t cantidad;
    size_t capacidad;
    cmp_func_t cmp;
};


/* ******************************************************************
 *                       Primitivas auxiliares
 * *****************************************************************/

void swap(void **x, void **y) {
    void *aux = *x;

    *x = *y;
    *y = aux;
}

void up_heap(heap_t *heap, size_t pos) {
    if (pos==TOPE) return;
    size_t padre = (pos-1)/2;
    

    if (heap->cmp(heap->datos[padre], heap->datos[pos]) >= 0) return;

    swap(&heap->datos[padre], &heap->datos[pos]);

    up_heap(heap, padre);
}

void down_heap(heap_t *heap, size_t pos) {
    size_t hijo_izq = 2*pos+1;
    size_t hijo_der = 2*pos+2;
    size_t mayor;

    if (hijo_izq >= heap->cantidad) return;

    if (hijo_der < heap->cantidad) {
        if (heap->cmp(heap->datos[hijo_der], heap->datos[hijo_izq]) > 0) {
            mayor = hijo_der;
        }
        else {
            mayor = hijo_izq;
        }
    }
    else {
        mayor = hijo_izq;
    }

    if (heap->cmp(heap->datos[mayor], heap->datos[pos]) <= 0)  return;

    swap(&heap->datos[pos], &heap->datos[mayor]);

    down_heap(heap, mayor);
}

void down_sort(void **datos, size_t cantidad, size_t pos , cmp_func_t cmp) {
    size_t hijo_izq = 2*pos+1;
    size_t hijo_der = 2*pos+2;
    size_t mayor;

    if (hijo_izq >= cantidad) return;

    if (hijo_der < cantidad) {
        if (cmp(datos[hijo_der], datos[hijo_izq]) > 0) {
            mayor = hijo_der;
        }
        else {
            mayor = hijo_izq;
        }
    }
    else {
        mayor = hijo_izq;
    }

    if (cmp(datos[mayor], datos[pos]) <= 0)  return;

    swap(&datos[pos], &datos[mayor]);

    down_sort(datos, cantidad, mayor, cmp);
}

void heapify(heap_t *heap) {
    for (int i=(int)(heap->cantidad-1); i>=0; i--) {
        down_heap(heap, i);
    }
}

void sortify(void **datos, size_t cantidad, cmp_func_t cmp) {
    for (int i=(int)(cantidad-1); i>=0; i--) {
        down_sort(datos, cantidad, i, cmp);
    }
}

bool redimensionar_datos(heap_t *heap, size_t capacidad) {
    void **aux = realloc(heap->datos, sizeof(void*)*capacidad);
    if (!aux) return false;

    heap->capacidad = capacidad;
    heap->datos = aux;

    return true;
}

/* ******************************************************************
 *                       Primitivas del heap
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
    if (!cmp) return NULL;

    heap_t *nuevo_heap = malloc(sizeof(heap_t));
    if (!nuevo_heap) return NULL;

    nuevo_heap->datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
    if (!nuevo_heap->datos) {
        free(nuevo_heap);
        return NULL;
    }

    nuevo_heap->cmp = cmp;
    nuevo_heap->cantidad = 0;
    nuevo_heap->capacidad = CAPACIDAD_INICIAL;

    return nuevo_heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    if (!cmp) return NULL;

    heap_t *nuevo_heap = malloc(sizeof(heap_t));
    if (!nuevo_heap) return NULL;

    size_t largo = CAPACIDAD_INICIAL;
    if (n>=CAPACIDAD_INICIAL) {
        largo = n*2;
    }

    nuevo_heap->datos = malloc(sizeof(void*)*largo);
    if (!nuevo_heap->datos) {
        free(nuevo_heap);
        return NULL;
    }

    nuevo_heap->cmp = cmp;
    nuevo_heap->cantidad = n;
    nuevo_heap->capacidad = largo;
    memcpy(nuevo_heap->datos, arreglo, sizeof(void*)*n);

    heapify(nuevo_heap);

    return nuevo_heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    if (cant<=1) return;

    sortify(elementos, cant, cmp);

    for (size_t i=(cant-1); i>0; i--) { 
        swap(&elementos[TOPE], &elementos[i]);
        down_sort(elementos, i, TOPE, cmp);
    }
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    if (destruir_elemento) {
        for (size_t i=0; i<heap->cantidad; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cantidad==0;
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cantidad==heap->capacidad) {
        size_t nueva_capacidad = heap->capacidad*REDIMENSION;
        if (!redimensionar_datos(heap, nueva_capacidad)) return false;
    }
    
    heap->datos[heap->cantidad] = elem;

    up_heap(heap, heap->cantidad);
    heap->cantidad++;

    return true;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    
    return heap->datos[TOPE];
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;

    if (heap->cantidad<(heap->capacidad/DECREMENTO) && heap->capacidad>CAPACIDAD_INICIAL) {
        size_t nueva_capacidad = heap->capacidad/REDIMENSION;
        if (!redimensionar_datos(heap, nueva_capacidad)) return false;
    }

    swap(&heap->datos[TOPE], &heap->datos[--heap->cantidad]);
    down_heap(heap, TOPE);

    return heap->datos[heap->cantidad];
}
