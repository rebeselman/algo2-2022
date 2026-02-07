#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Devuelve verdadero si la lista no tiene elementos enlazados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al inicio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Borra el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento, 
// el posterior a ese ahora es el primero y la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el largo de la lista. Si la lista tiene
// elementos, se devuelve la cantidad, si está vacía devuelve 0.
// Pre: la lista fue creada.
// Post: se devolvió el largo de la lista, cuando no está vacía.
size_t lista_largo(const lista_t *lista);

// Itera por todos los elementos de la lista, aplicando a los elementos (dato)
// la funcion visitar y con el parametro extra que esta use.
// Pre: la lista fue creada.
// Post: se aplico visitar a todos los elementos de la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

// Crea un iterador de la lista.
// Pre: la lista fue creada.
// Post: devuelve un nuevo iterador de lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador, un elemento, en la lista. Devuelve verdadero si
// pudo avanzar, falso si alcanzo el final o lista vacia.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve true si pudo avanzar, false si no.
bool lista_iter_avanzar(lista_iter_t *iter);

// Muestra el elemento actual donde esta el iterador. Devuelve el elemento,
// o NULL si alcanzo el final o lista vacia.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve el elemento si pudo avanzar, NULL si no.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Nos dice si el iterador esta al final de la lista. Devuelve verdadero
// si esta al final o falso si no lo esta.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve true si el iterador esta al final de la lista o false si no.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta el elemento en la posicion del iterador en la lista,  
// devuelve true si pudo, false si no.
// Pre: el iterador fue creado y la lista existe.
// Post: el dato fue insertado en la lista o devuelve falso.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento en la posicion del iterador en la lista,  
// devuelve el elemento si pudo, NULL si no.
// Pre: el iterador fue creado y la lista existe.
// Post: el dato fue eliminado de la lista y lo devuelve o devuelve NULL.
void *lista_iter_borrar(lista_iter_t *iter);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_estudiante(void);

#endif  // LISTA_H
