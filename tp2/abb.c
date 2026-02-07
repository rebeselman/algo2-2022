#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "abb.h"
#include "pila.h"

extern char* strdup(const char*); // para que el compilador no marque error al usar strden
/* ******************************************
 * Definicion de los structs abb y abb_iter * 
 ********************************************/

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb {
    nodo_abb_t* raiz;
    size_t cant;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t comparar;
};


/* ******************************************
 * Definicion de los structs auxiliares* 
 ********************************************/

//si encontrado es false, nodo es un nodo al que le podrías insertar un hijo
typedef struct nodo_buscado {
	bool encontrado;
	nodo_abb_t* nodo;
	nodo_abb_t* padre;
	
} nodo_buscado_t;



/* *******************************
 * Funciones auxiliares del nodo * 
 *********************************/

nodo_abb_t* nodo_crear(char* clave, void* dato){
    nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
    if (nodo == NULL) return NULL;
    nodo->dato = dato; 
    nodo->clave = clave; //copia de la clave
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

nodo_buscado_t* buscar_nodo(nodo_abb_t* raiz, const char* clave, abb_comparar_clave_t comparar, nodo_abb_t* padre){
	if (!raiz) {
		nodo_buscado_t* nodo = malloc(sizeof(nodo_buscado_t));
		if (!nodo) return NULL;
		nodo->encontrado = false;
		nodo->nodo = padre;
		nodo->padre = padre;
		return nodo;		
	}
	if (comparar(clave, raiz->clave) ==  0){
		nodo_buscado_t* nodo = malloc(sizeof(nodo_buscado_t));
		if (!nodo) return NULL;
		nodo->encontrado = true;
		nodo->nodo = raiz;
		nodo->padre = padre;
		return nodo;
	}
	if (comparar(clave, raiz->clave) < 0) return buscar_nodo(raiz->izq, clave, comparar, raiz);
	else return buscar_nodo(raiz->der, clave, comparar, raiz); 
}

void nodo_destruir(nodo_abb_t *nodo, abb_destruir_dato_t destruir_dato){
    if (destruir_dato != NULL) destruir_dato(nodo->dato);
    free(nodo->clave);
    free(nodo);
}

//Destruir abb
void _abb_destruir(nodo_abb_t *nodo, abb_destruir_dato_t destruir_dato) {
    if (!nodo) return;
    _abb_destruir(nodo->izq, destruir_dato);
    _abb_destruir(nodo->der, destruir_dato);
    nodo_destruir(nodo, destruir_dato);
}


char* buscar_reemplazante(nodo_abb_t* nodo){
	if (!nodo->izq) {
		char* clave_reemplazante = strdup(nodo->clave);
		if (!clave_reemplazante) return NULL;
		return clave_reemplazante;
	}
	return buscar_reemplazante(nodo->izq);
}




/* ****************
 * Primitivas ABB * 
 ******************/
 
abb_t *abb_crear(abb_comparar_clave_t comparar, abb_destruir_dato_t destruir_dato){
	abb_t *abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb->raiz = NULL;
	abb->cant = 0;
	abb->comparar = comparar;
	abb->destruir = destruir_dato;
	return abb;
}


// Devuelve true si pudo guardar clave y dato, false en caso de error.
// Pre: El arbol fue creado.
// Pos: Clave y dato fueron guardadas.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_buscado_t* nodo_buscado = buscar_nodo(arbol->raiz, clave, arbol->comparar, NULL); 
	if (!nodo_buscado) return false;
	if(!nodo_buscado->encontrado){ 
		char* clave_copia = strdup(clave);
		if (!clave_copia) {
			free(nodo_buscado);
			return false;
		}
		nodo_abb_t* nodo_nuevo = nodo_crear(clave_copia, dato);
		if (!nodo_nuevo){
			free(clave_copia);
			free(nodo_buscado);
			return false;
		}
		if (!nodo_buscado->nodo) arbol->raiz =  nodo_nuevo;
		else{
			abb_comparar_clave_t comparar_dato = arbol->comparar;
			if (comparar_dato(clave_copia, nodo_buscado->nodo->clave) < 0) nodo_buscado->nodo->izq = nodo_nuevo;
			else nodo_buscado->nodo->der = nodo_nuevo;
		}
		arbol->cant++;
	}
	else{
		abb_destruir_dato_t destruir = arbol->destruir;
		if (destruir) destruir(nodo_buscado->nodo->dato);
		nodo_buscado->nodo->dato = dato;
	}
	
	free(nodo_buscado);
	return true;
}

// Borra la clave junto al dato asociado del arbol, devuelve el dato. Devuelve NULL en caso de error.
// Pre: El arbol fue creado.
// Pos: Devuelve el dato asociado a la clave borrada.
void * abb_borrar(abb_t *arbol, const char *clave){
	nodo_buscado_t* nodo_buscado = buscar_nodo(arbol->raiz, clave, arbol->comparar, NULL);
	if (!nodo_buscado || !nodo_buscado->encontrado){
		free(nodo_buscado);
		return NULL;
	}
	void* dato = nodo_buscado->nodo->dato;
	abb_comparar_clave_t comparar = arbol->comparar;
	

	if (!nodo_buscado->nodo->der || !nodo_buscado->nodo->izq){
		if (!nodo_buscado->nodo->der && !nodo_buscado->nodo->izq){
			if (nodo_buscado->nodo == arbol->raiz) arbol->raiz = NULL;
			else{
				if (comparar(nodo_buscado->nodo->clave, nodo_buscado->padre->clave) < 0) nodo_buscado->padre->izq = NULL;
				else nodo_buscado->padre->der = NULL;
			}
		}		
		else{
			if (nodo_buscado->nodo ==  arbol->raiz){
				if (nodo_buscado->nodo->der) arbol->raiz = nodo_buscado->nodo->der;
				else  arbol->raiz = nodo_buscado->nodo->izq;			
			}
			else if (comparar(nodo_buscado->nodo->clave, nodo_buscado->padre->clave) < 0){
				if (nodo_buscado->nodo->der) nodo_buscado->padre->izq = nodo_buscado->nodo->der;
				else  nodo_buscado->padre->izq = nodo_buscado->nodo->izq;
			}
			else{
				if (nodo_buscado->nodo->der) nodo_buscado->padre->der = nodo_buscado->nodo->der;
				else nodo_buscado->padre->der = nodo_buscado->nodo->izq;
			}
		}
		free(nodo_buscado->nodo->clave);
		free(nodo_buscado->nodo);
	}
	else{
	
		char* clave_reemplazante = buscar_reemplazante(nodo_buscado->nodo->der);
		void* dato_reemplazante = abb_borrar(arbol, clave_reemplazante);
		free(nodo_buscado->nodo->clave);
		nodo_buscado->nodo->clave = clave_reemplazante;
		nodo_buscado->nodo->dato = dato_reemplazante;
		free(nodo_buscado);
		return dato;
	}
	arbol->cant--;
	free(nodo_buscado);
	return dato;
	
}



void* abb_obtener(const abb_t *arbol, const char *clave){
	nodo_buscado_t* nodo_buscado = buscar_nodo(arbol->raiz, clave, arbol->comparar, NULL); //falta chequeo del malloc
	if (nodo_buscado->encontrado){
		void* dato = nodo_buscado->nodo->dato;
		free(nodo_buscado);
		return dato;
	}
	else {
		free(nodo_buscado);
		return NULL;
	}
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_buscado_t* nodo_buscado = buscar_nodo(arbol->raiz, clave, arbol->comparar, NULL); //falta chequeo del malloc
	bool encontrado = nodo_buscado->encontrado;
	free(nodo_buscado);
	if (encontrado)return true;
	else return false;
}


size_t abb_cantidad(const abb_t *arbol){
	return arbol->cant;
}

void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol->raiz, arbol->destruir);
    free(arbol);
}

/* ********************************
 * Primitiva del iterador interno * 
 **********************************/




bool _abb_in_order(nodo_abb_t*nodo, bool visitar(const char *, void *, void *), void *extra){
    if (nodo == NULL) return true;
    if (_abb_in_order(nodo->izq, visitar, extra)) {
        if (!visitar(nodo->clave, nodo->dato, extra)) return false;
        return _abb_in_order(nodo->der, visitar, extra);
    }
    return false;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	if (arbol->raiz == NULL) return;
	_abb_in_order(arbol->raiz, visitar, extra);
}



/* *********************************
 * Primitivas del iterador externo * 
 ***********************************/
struct abb_iter{
    pila_t *pila;
}; 

void apilar_hijos_izquierdos(nodo_abb_t* nodo_actual, pila_t* pila){
	if (!nodo_actual) return;
	pila_apilar(pila, nodo_actual);
	apilar_hijos_izquierdos(nodo_actual->izq, pila);
}






// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    pila_t* pila = pila_crear();
    if (!pila){
		free(iter);
		return NULL;
	}
	apilar_hijos_izquierdos(arbol->raiz, pila);
	iter->pila = pila;
    return iter;
}

//Devuelve true en caso de poder avanzar, false en caso contrario.
bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter))return false;
	nodo_abb_t* nodo = pila_desapilar(iter->pila);
	apilar_hijos_izquierdos(nodo->der, iter->pila);
	return true;
}
// Devuelve la clave actual.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return NULL;
	nodo_abb_t* nodo = pila_ver_tope(iter->pila);
	return nodo->clave;
}

// Devuelve true si está al final, false en caso contrario.
bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

// Destruye el iterador
void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}
