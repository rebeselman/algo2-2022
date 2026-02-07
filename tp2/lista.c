#include <stdlib.h>
#include "lista.h"

typedef struct nodo nodo_t;

struct nodo {
    nodo_t *siguiente;
    void* dato;
};

struct lista{
    nodo_t *primero;
    nodo_t *ultimo;
    size_t largo;
};

lista_t *lista_crear(void) {
    lista_t *nueva_lista = malloc(sizeof(lista_t));
    if (nueva_lista==NULL) return NULL;

    nueva_lista->primero = NULL;
    nueva_lista->ultimo = NULL;
    nueva_lista->largo = 0;

    return nueva_lista;
}

nodo_t *crear_nodo(void *dato) {
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (nuevo_nodo==NULL) return NULL;

    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;

    return nuevo_nodo;
}

void destruir_nodo (nodo_t *nodo) {
    free(nodo);
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        if (destruir_dato==NULL) {
            lista_borrar_primero(lista);
        }
        else {
            destruir_dato(lista_borrar_primero(lista));
        }
    }

    free(lista);
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_iniciar(lista_t *lista, void *dato) {
    lista->primero = crear_nodo(dato);
    if (lista->primero==NULL) return false;

    lista->ultimo = lista->primero;
    lista->ultimo->siguiente = NULL;
    lista->largo++;

    return true;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    if (lista_esta_vacia(lista)) {
        return lista_iniciar(lista, dato);
    }

    nodo_t *enlistado = crear_nodo(dato);
    if (enlistado==NULL) return false;

    enlistado->siguiente = lista->primero;
    lista->primero = enlistado;
    lista->largo++;

    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    if (lista_esta_vacia(lista)) {
        return lista_iniciar(lista, dato);
    }
    
    nodo_t *enlistado = crear_nodo(dato);
    if (enlistado==NULL) return false;

    lista->ultimo->siguiente = enlistado;
    enlistado->siguiente = NULL;
    lista->ultimo = enlistado;
    lista->largo++;

    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t *aux = lista->primero;
    void *retorno = aux->dato;
    
    lista->primero = aux->siguiente;
    destruir_nodo(aux);

    lista->largo--;

    return retorno;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;

    return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;

    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    if (lista_esta_vacia(lista)) return;

    nodo_t *actual = lista->primero;

    while (actual!=NULL && visitar(actual->dato, extra)) {
        actual = actual->siguiente;
    } 
}

struct lista_iter {
    lista_t* lista;
    nodo_t* anterior;
    nodo_t* actual;
};

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) return NULL;

    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (iter->actual == NULL){
        return false;
    }

    iter->anterior = iter->actual;
    iter->actual = iter->actual->siguiente;

    return true;
}
void *lista_iter_ver_actual(const lista_iter_t *iter){
    if (lista_iter_al_final(iter)) return NULL;
    
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if (iter->anterior == NULL ){
        if (!lista_insertar_primero(iter->lista, dato)) return false; 

        iter->actual = iter->lista->primero;
        return true;
    }
    else if (iter->actual == NULL ){
        nodo_t* nodo_aux = iter->lista->ultimo;

        if (!lista_insertar_ultimo(iter->lista, dato)) return false;

        iter->anterior = nodo_aux;
        iter->actual = nodo_aux->siguiente;
        return true;
    }

    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL) return false;
    
    nodo->siguiente = iter->actual;
    iter->anterior->siguiente = nodo;
    iter->actual = nodo;
    iter->lista->largo++;

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if (iter->actual==NULL) return NULL;
    
    void* dato_aux;
    nodo_t* resultado;

    if (iter->anterior == NULL) {
        resultado = iter->actual->siguiente;
        dato_aux = lista_borrar_primero(iter->lista);
        iter->actual = resultado;

        return dato_aux;
    }

    dato_aux = iter->actual->dato;
    iter->anterior->siguiente = iter->actual->siguiente;
    free(iter->actual);

    if(iter->anterior->siguiente == NULL){
        iter->actual = NULL;
        iter->lista->ultimo = iter->anterior;
    }
    else{
        iter->actual = iter->anterior->siguiente;
    }

    iter->lista->largo--;

    return dato_aux;
}   
