#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/* Estructuras */

/* Nodo */

typedef struct nodo nodo_t;

struct nodo {
	void* dato; 
	nodo_t* prox; 
};


//Crea un nodo. Si falla devuelve null, en caso contrario un nodo.
nodo_t* nodo_crear(void* dato){ //O(1)
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if (nodo_nuevo == NULL){
		return NULL;
	}
	nodo_nuevo->dato = dato;
	nodo_nuevo->prox = NULL; 
	return nodo_nuevo;
}


//Destruye el nodo y devuelve su dato.
void* nodo_destruir(nodo_t* nodo){
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

/* Cola */

struct cola {
	nodo_t* primero; 
	nodo_t* ultimo;  
};

/* Definiciones de primitivas */

cola_t* cola_crear(void){
	cola_t* cola_nueva = malloc(sizeof(cola_t));
	if (cola_nueva == NULL){
		return NULL;
	}
	cola_nueva->primero = NULL;
	cola_nueva->ultimo =  NULL;
	return cola_nueva;
}


void cola_destruir(cola_t* cola, void (*destruir_dato)(void*)){ //O(n) depende de la cantidad de N ELEMENTOS ENCOLADOS
	while (!cola_esta_vacia(cola)){
		void* dato = cola_desencolar(cola);
		if (destruir_dato) destruir_dato(dato);
	}
	free(cola);
}


bool cola_esta_vacia(const cola_t* cola){
	if (cola->primero == NULL && cola->ultimo == NULL) return true; 
	return false;
}


bool cola_encolar(cola_t* cola, void* valor){
	nodo_t* nuevo_elemento = nodo_crear(valor); //O(1)
	if (nuevo_elemento == NULL) return false;
	
	if (cola_esta_vacia(cola)) cola->primero = nuevo_elemento;
	else cola->ultimo->prox = nuevo_elemento;	
	
	cola->ultimo = nuevo_elemento;
	return true;
}


void* cola_ver_primero(const cola_t* cola){
	if (cola_esta_vacia(cola)) return NULL;
	return cola->primero->dato;
}


void* cola_desencolar(cola_t* cola){
	if (cola_esta_vacia(cola)) return NULL;
	void* proximo_primero = cola->primero->prox;
	void* dato = nodo_destruir(cola->primero);
	cola->primero = proximo_primero;
	if (cola->primero == NULL) cola->ultimo = NULL;
	return dato;
}
