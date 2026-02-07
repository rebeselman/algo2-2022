#include <stdlib.h>

typedef struct usuario usuario_t;

// Crea un usario.
// Post: se creó un usuario.
usuario_t *usuario_crear(char *nombre, size_t id_usuario); 

// Se destruye el usuario.
// Pre: se creó el usuario.
// Post: se destruyó el usuario.
void usuario_destruir(void *usuario); 

// Devuelve el id del usuario.
// Pre: se creó el usuario.
size_t usuario_id(usuario_t *usuario);

// Devuelve el nombre del usuario.
// Pre: se creó el usuario.
// Post: devolvió el nombre del usuario.
char *usuario_nombre(usuario_t *usuario);


// Recarga el feed del usuario con un nuevo post.
// Pre: se creó el usuario y el post.
// Post: Se agregó al feed del usuario el post.
void recargar_feed(usuario_t *usuario, void *post, size_t id_post, size_t afinidad);


// Se muestra (si hay) el post más prioritario para ser visto en el feed por el usuario.
// Pre: se creó el usuario.
// Post: Se imprimió por salida estándar el post.
bool ver_feed(usuario_t *usuario);
