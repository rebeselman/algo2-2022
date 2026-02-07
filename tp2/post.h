#include <stdbool.h>

typedef struct post post_t; 

// Crea el post.
// Post: se creó el post.
post_t *post_crear(char *publicacion, char *autor, size_t id_post, size_t autor_id);

// Destruye el post.
// Pre: se creó el post.
// Post: se destruyó el post.
void post_destruir(void *post);

// Se encarga de agregar el like del usuario.
// Pre: se creó el post.
// Post: se agregó el like del usuario al post.
bool post_likear(post_t *post, char *usuario);


// Recibe el post e imprime por salida estándar
// la información del post.
// Pre: se creó el post.
// Post: se imprimió por salida estándar la información del post.
void post_imprimir(post_t *post);

// Recibe un post e imprime los nombres de los usuarios que le dieron like al post.
// Pre: se creó el ṕost.
// Post: se imprimió los nombres de los usuarios que le dieron like al post.
// Complejidad: O(u) u siendo cantidad de usuarios que le dieron like al post.
void imprimir_likes(post_t *post);


// Devuelve la cantidad de likes que tiene el post.
// Pre: se creó el post.
// Post: devolvió la cantidad de likes que tiene el post.
size_t post_cantidad_likes(post_t *post);
