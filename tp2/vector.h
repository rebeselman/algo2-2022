#include <stdbool.h> 
#include <stddef.h>

typedef struct vector vector_t;

typedef void (*vector_destruir_dato_t)(void *);


vector_t* vector_crear(vector_destruir_dato_t destruir);

void vector_destruir(vector_t* vector);

size_t vector_largo(vector_t* vector);

bool vector_redimensionar(vector_t* vector, size_t capacidad_nueva);

bool vector_agregar(vector_t* vector, void* valor);

void* vector_obtener(vector_t* vector, size_t posicion);