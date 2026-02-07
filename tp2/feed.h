#include <stdbool.h>
#include <stddef.h>

typedef struct feed feed_t;

// Crea un feed para un usuario.
// Post: devuelve un feed.
feed_t *feed_crear();

// Destruye un feed.
// Pre: Se creó un feed.
// Post: se destruyó el feed con todos los posts.
void feed_destruir(feed_t *feed);

// Agrega un post al feed. Recibe el post y la afinidad del mismo.
// Pre: Se creó un feed.
// Post: se agregó un post al feed.
bool feed_agregar(feed_t *feed, void *post, size_t id, size_t afinidad); 

// Recibe un feed, muestra el post con mas prioridad para ser visto por el user y lo imprime.
// Pre: Se creó un feed.
// Post: Se imprimió el post con más prioridad.
bool feed_ver(feed_t *feed);
