#include "pila.h"

#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 100
#define CAPACIDAD_INCREMENTO 2
#define CAPACIDAD_DECREMENTO 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){
    pila_t *nueva_pila = malloc(sizeof(pila_t));
    if (nueva_pila==NULL) return NULL;

    nueva_pila->datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
    if (nueva_pila->datos==NULL) {
        free(nueva_pila);
        return NULL;
    }

    nueva_pila->cantidad = 0;
    nueva_pila->capacidad = CAPACIDAD_INICIAL;

    return nueva_pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad==0;
}

bool redimensionar(pila_t *pila, size_t nueva_capacidad){
    void **datos_aux = realloc(pila->datos,sizeof(void*)*nueva_capacidad);

    if (datos_aux==NULL) {
        return false;
    }

    pila->datos = datos_aux;
    pila->capacidad = nueva_capacidad;

    return true;
}

bool pila_apilar(pila_t *pila, void *valor) {
    size_t capacidad_aux = pila->capacidad*CAPACIDAD_INCREMENTO;
    
    if (pila->cantidad==pila->capacidad && !redimensionar(pila, capacidad_aux)) {
        return false;
    }

    pila->datos[pila->cantidad] = valor;

    pila->cantidad++;

    return true;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) return NULL;

    return pila->datos[pila->cantidad-1];
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;

    size_t capacidad_aux = pila->capacidad - pila->capacidad/CAPACIDAD_DECREMENTO;

    if (pila->cantidad==pila->capacidad/CAPACIDAD_INCREMENTO && pila->capacidad>CAPACIDAD_INICIAL) {
        redimensionar(pila, capacidad_aux);
    }

    void *tope;
    tope = pila_ver_tope(pila);

    pila->cantidad--;

    return tope;
}

// ...



