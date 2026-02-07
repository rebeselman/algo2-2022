#include <string.h>
#include <stdbool.h>
#include "feed.h"
#include "usuario.h"

struct usuario {
    char *nombre;
    feed_t *feed; 
    size_t id_usuario; 
};


usuario_t *usuario_crear(char *nombre, size_t id_usuario) {
    usuario_t *usuario = malloc(sizeof(usuario_t));
    if (!usuario) return NULL;


    usuario->nombre = nombre;
    usuario->id_usuario = id_usuario;
    usuario->feed = feed_crear();
    if (!usuario->feed) {
        free(usuario->nombre);
        free(usuario);
        return NULL;
    }

    return usuario;
}

void _usuario_destruir(usuario_t *usuario) {
    feed_destruir(usuario->feed);
    free(usuario->nombre);
    free(usuario);
}

void usuario_destruir(void *usuario) {
    usuario_t *destruible = (usuario_t*) usuario;
    _usuario_destruir(destruible);
}

size_t usuario_id(usuario_t *usuario) {
    return usuario->id_usuario;
}

char *usuario_nombre(usuario_t *usuario) {
    return usuario->nombre;
}

bool usuario_distinto(usuario_t *usuario, usuario_t *usuario2) {
    return (strcmp(usuario->nombre, usuario2->nombre) != 0);
}

void recargar_feed(usuario_t *usuario, void *post, size_t id, size_t afinidad) {
    feed_agregar(usuario->feed, post, id, afinidad); 
}

bool ver_feed(usuario_t *usuario) {
    return feed_ver(usuario->feed); 
}
