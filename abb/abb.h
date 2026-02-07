#include <stdbool.h>
#include <stddef.h>

/* ******************************************
 * Definicion de los structs abb y abb_iter * 
 ********************************************/

struct abb;
struct abb_iter;

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t)(const char *, const char *);
typedef void (*abb_destruir_dato_t)(void *);

/* ********************
 * Primitivas del ABB * 
 **********************/

// Crea el abb
abb_t * abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Devuelve true si pudo guardar clave y dato, false en caso de error.
// Pre: El arbol fue creado.
// Pos: Clave y dato fueron guardadas.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Borra la clave junto al dato asociado del arbol, devuelve el dato. Devuelve NULL en caso de error.
// Pre: El arbol fue creado.
// Pos: Devuelve el dato asociado a la clave borrada.
void * abb_borrar(abb_t *arbol, const char *clave);


// Devuelve el dato asociado a la clave, NULL en caso de que no encuentre la clave.
// Pre: El arbol fue creado.
// Pos: Devuelve el dato asociado a la clave, NULL en caso de que la clave no exista.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Determina si clave pertenece o no al abb.
// Pre: El arbol fue creado.
// Pos: Devuelve true si la clave pertenece, false en caso contrario.
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos del abb.
// Pre: El arbol fue creado.
size_t abb_cantidad(const abb_t *arbol);

// Destruye el arbol.
// Pre: El arbol fue creado.
// Pos: El arbol fue destruido.
void abb_destruir(abb_t *arbol);

/* ********************************
 * Primitiva del iterador interno * 
 **********************************/

//iterador interno
//Aplica la funcion visitar() a las claves y datos del arbol.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* *********************************
 * Primitivas del iterador externo * 
 ***********************************/

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Devuelve true en caso de poder avanzar, false en caso contrario.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve la clave actual.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Devuelve true si está al final, false en caso contrario.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador
void abb_iter_in_destruir(abb_iter_t* iter);


