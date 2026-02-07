#include "feed.h"
#include "heap.h"
#include "post.h"
#include <stdlib.h>

#define MENOR 1 
#define MAYOR -1
// Al comparar por minimos, hay que priorizar los valores menores

struct feed {
    heap_t *heap;  
};

typedef struct feed_nodo {
    post_t *post;
    size_t id;
    size_t afinidad;
} feed_nodo_t;

// Función de comparación para el heap que contiene los feed_nodo_t que a su vez contiene
// los posts. El post con más prioridad a ser visto es el que tiene el valor más chico de afinidad
// en valor absoluto, entonces si afinidad1 < afinidad2 (en valor absoluto) afinidad1 tiene más prioridad
// entonces se dice que es MAYOR.
int igualdad(size_t id1, size_t id2) {
    if (id1 < id2) return MENOR;
    else return MAYOR;
}

int comparar(const void *dato1, const void *dato2) { 
    feed_nodo_t *nodo1 = (feed_nodo_t*) dato1;
    feed_nodo_t *nodo2 = (feed_nodo_t*) dato2;
    
    if (nodo1->afinidad > nodo2->afinidad) return MAYOR;
    else if (nodo1->afinidad < nodo2->afinidad) return MENOR;
    else {
        return igualdad(nodo1->id, nodo2->id);
    }
}

feed_t* feed_crear() {
    feed_t *feed = malloc(sizeof(feed_t));
    if (!feed) return NULL;

    feed->heap = heap_crear(comparar);
    if(!feed->heap) {
        free(feed);
        return NULL;
    }
    return feed;
}

feed_nodo_t* feed_nodo_crear(post_t *post, size_t id, size_t afinidad) { 
    feed_nodo_t *nodo = malloc(sizeof(feed_nodo_t));
    if (!nodo) return NULL;

    nodo->id = id;
    nodo->post = post;
    nodo->afinidad = afinidad;

    return nodo;
}

void feed_nodo_destruir(void* nodo) { 
    free(nodo);
}


void feed_destruir(feed_t *feed) {
    heap_destruir(feed->heap, feed_nodo_destruir);
    free(feed);
}


bool feed_agregar(feed_t *feed, void *post, size_t id, size_t afinidad) {   
    feed_nodo_t *nodo = feed_nodo_crear((post_t*) post, id, afinidad);
    if (!nodo) return false;

    if (!heap_encolar(feed->heap, nodo)){
        free(nodo);
        return false;
    }
    return true;
}


bool feed_ver(feed_t *feed){ 
    if (heap_esta_vacio(feed->heap)) return false;

    feed_nodo_t *nodo = (feed_nodo_t*) heap_desencolar(feed->heap); 
    post_imprimir(nodo->post); 
    feed_nodo_destruir(nodo);

    return true;
}
