#include "lista.h"
#include <stdlib.h>

/* Tipo de dato Nodo */

typedef struct nodo nodo_t;

struct nodo {
	void* dato;
	nodo_t* prox;
};

/* Definicion de primitivas de nodo */

nodo_t* nodo_crear(void* dato){
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if (!nodo_nuevo){
		return NULL;
	}
	nodo_nuevo->dato = dato;
	nodo_nuevo->prox = NULL; 
	return nodo_nuevo;
}

void* nodo_destruir(nodo_t* nodo){
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

/* Tipo de dato lista */

struct lista {
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct lista_iter{
	lista_t* lista;
	nodo_t* actual;
	nodo_t* anterior;
};

/* Definicion de primitivas de la lista */

lista_t *lista_crear(void){
	lista_t* lista_nueva = malloc(sizeof(lista_t));
	if (!lista_nueva) return NULL;
	lista_nueva->prim = NULL;
	lista_nueva->ult = NULL;
	lista_nueva->largo = 0;
	return lista_nueva;
}

bool lista_esta_vacia(const lista_t* lista){
	if (lista->largo == 0) return true;
	return false;
}

bool lista_insertar_primero(lista_t* lista, void* dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if (!nodo_nuevo) return false;
	if (lista_esta_vacia(lista)) lista->ult = nodo_nuevo;
	else nodo_nuevo->prox = lista->prim;
	lista->prim = nodo_nuevo;
	lista->largo++;
	return true;
}	
   
bool lista_insertar_ultimo(lista_t* lista, void *dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if (!nodo_nuevo)return false;
	if (lista_esta_vacia(lista)) lista->prim = nodo_nuevo;  
	else lista->ult->prox = nodo_nuevo;
	lista->ult = nodo_nuevo;
	lista->largo++;
	return true;
}

void* lista_borrar_primero(lista_t* lista){ 
	if (lista_esta_vacia(lista)) return NULL;
	nodo_t* nuevo_prim = lista->prim->prox;
	void* dato = nodo_destruir(lista->prim);
	lista->largo--;
	lista->prim = nuevo_prim;
	if(lista_esta_vacia(lista))lista->ult = NULL;
	return dato;
}
                     
void* lista_ver_primero(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;	
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	while (lista->prim){
		void* dato = lista_borrar_primero(lista);
		if (destruir_dato) destruir_dato(dato);
	}
	free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void* extra), void* extra){
	nodo_t* nodo_actual = lista->prim;
	while (nodo_actual){
		bool res = visitar(nodo_actual->dato, extra);
		if(!res) break;
		nodo_actual = nodo_actual->prox;
	}	
}

// Primitivas del iterador externo

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter) return NULL;
	iter->lista = lista;
	iter->actual = lista->prim;
	iter->anterior = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (iter->actual == NULL) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void* dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if (!nodo_nuevo) return false;
	if (!iter->anterior){ 	
		if(!lista_esta_vacia(iter->lista))nodo_nuevo->prox = iter->actual;
		else iter->lista->ult = nodo_nuevo;
		iter->lista->prim = nodo_nuevo;
		
	}
	else{ 
		iter->anterior->prox = nodo_nuevo;
		if (!iter->actual) iter->lista->ult = nodo_nuevo;
		else nodo_nuevo->prox = iter->actual;			
	}
	iter->actual = nodo_nuevo;
	iter->lista->largo++;
	return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return NULL;
	void* dato;
	if (!iter->anterior){
		iter->lista->prim = iter->actual->prox;
		dato = nodo_destruir(iter->actual);
		iter->actual = iter->lista->prim;
	}
	else{
		iter->anterior->prox = iter->actual->prox;
		dato = nodo_destruir(iter->actual);
		iter->actual = iter->anterior->prox;
		if (lista_iter_al_final(iter)) iter->lista->ult = iter->anterior;
	}
	iter->lista->largo--;
	return dato;
}
