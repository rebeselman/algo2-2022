#ifndef _LISTA_H
#define _LISTA_H

#include <stdbool.h>
#include <stddef.h>

// 	Definicion del tipo de dato lista //

/* 	La lista está planteada como una lista de punteros genéricos. */
struct lista;
typedef struct lista lista_t;

/* ******************
 * PRIMITIVAS LISTA *
 * ******************/

// Crea una lista. En caso de error devuelve NULL.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento en la primera posición, devuelve false en caso de error.
// Pre: la lista fue creada.
// Post: se insertó un nuevo elemento en la primera posición.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento en la última posición, devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se insertó un nuevo elemento en la ultima posición. 
bool lista_insertar_ultimo(lista_t *lista, void* dato);

// Borra el primer elemento de la lista. Devuelve el dato eliminado. Si la lista está vacía devuelve NULL. 
// Pre: la lista fue creada.
// Post: se borró el primer elemento de la lista.
void* lista_borrar_primero(lista_t *lista);

// Obtiene el primer dato de la lista, se devuelve este dato. Si la lista está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer dato de la lista.                        
void* lista_ver_primero(const lista_t *lista);


// Obtiene el último dato de la lista, se devuelve este dato. Si la lista está vacía devuelve NULL.    
// Pre: la lista fue creada.
// Post: se devolvió el último dato de la lista.
void* lista_ver_ultimo(const lista_t* lista);    

// Devuelve el largo de la lista o cantidad de elementos en ella.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. desruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


/* ****************************
 * PRIMITIVA ITERADOR INTERNO *
 * ****************************/

// Itera la lista aplicando a cada elemento de esta la función visitar.
// Pre: la lista fue creada. visitar es una función capaz de modificar dato. ****
// Post: la lista fue iterada según nuestras intenciones.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Definicion del tipo de dato lista_iter //

struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* *****************************
 * PRIMITIVAS ITERADOR EXTERNO *
 * *****************************/


// Crea una iterador de lista. En caso de error devuelve NULL.
// Post: devuelve un iterador de lista, apuntando a la primera posición de la misma.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posicion en la lista
// Pre: el iterador fue creado
// Post: Si se pudo avanzar al proximo lugar devuelve true
// o false si se encuentra al final de la lista
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el contenido de la posicion actual del iterador
// Pre: el iterador fue creado
// Post: devuelve el dato 
void* lista_iter_ver_actual(const lista_iter_t *iter);

// Verifica si el iterador en encuentra al final de la lista
// Pre: el iterador fue creado
// Post: devuelve true si se encuentra al final, false en caso contrario
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: el iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un nuevo elemento en la posicion donde se encuentra el iterador
// Pre: el iterador fue creado, el dato va a ser el elemento a insertar
// Post: se intera un nuevo elemento a la lista
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra el elementos actual que se este iterando
//Pre: el iterador fue creado
//Post: el elemento ya no se encuentra en la lista
void* lista_iter_borrar(lista_iter_t *iter);

//pruebas de la lista//
void pruebas_lista_estudiante(void);

#endif  // _LISTA_H
