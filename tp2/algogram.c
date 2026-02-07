#define _POSIX_C_SOURCE 200809L //  por el getline

#include "algogram.h"
#include "usuario.h"
#include "hash.h"
#include "post.h"
#include "vector.h"
#define LARGO_COMANDO 20
#define POST_CAP_ORIGINAL 100
#define REDIMENSIONADOR 2
#define ERROR_LEER_ARCHIVO -1
#define ERROR_DE_CONVERSION -2
#define SUMA_EXTRA_CARACTERES 10

struct algogram{
    hash_t *usuarios; 
    vector_t* posts;
    usuario_t *actual;
};

// Funciones auxiliares //

// Función auxiliar para pasar de size_t a char* el id_post, para guardar en el hash de posts.
/*
char* numero_a_cadena(size_t numero){
    char* clave = malloc(sizeof(int));
    if (!clave) return NULL; 

    int cant_caracteres = sprintf(clave, "%d", (int)numero);
    if (cant_caracteres == ERROR_DE_CONVERSION){
        free(clave);
        return NULL;
    }

    return clave;  
}
*/
//                      //

bool generar_usuarios(FILE *archivo, hash_t *hash){
    size_t pos = 0; 
	while (true) {
        char *linea = NULL;
	    size_t capacidad = 0;
        size_t leidos = getline(&linea, &capacidad, archivo);
        if (leidos == ERROR_LEER_ARCHIVO){
            free(linea);
            break;
        }
        usuario_t *usuario = usuario_crear(linea, pos);
        if (!usuario) {
            free(linea);
            return false;
        }
        hash_guardar(hash, linea, usuario);
        pos++;
    }
    return true;
}

algogram_t* algogram_crear(FILE *archivo) {
    algogram_t *arranque = malloc(sizeof(algogram_t)); 
    if (!arranque) return NULL;

    arranque->usuarios = hash_crear(usuario_destruir); 
    if(!arranque->usuarios) {
        free(arranque);
        return NULL;
    }
    arranque->posts = vector_crear(post_destruir);
    if(!arranque->posts) {
        hash_destruir(arranque->usuarios);
        free(arranque);
        return NULL;
    }
    if (!generar_usuarios(archivo, arranque->usuarios)) {
        hash_destruir(arranque->usuarios);
        vector_destruir(arranque->posts);
        free(arranque);
        return NULL;
    }
    arranque->actual = NULL; 
    return arranque; 
}

void algogram_destruir(algogram_t *programa) {
    hash_destruir(programa->usuarios);
    vector_destruir(programa->posts);
    free(programa);
}

bool loguear(algogram_t *programa, char *usuario) {
    if (!hash_pertenece(programa->usuarios, usuario)) return false;
    programa->actual = (usuario_t*) hash_obtener(programa->usuarios, usuario);
    return true;
}

void desloguear(algogram_t *programa) {
    programa->actual = NULL;
}

bool esta_logueado(algogram_t *programa) {
    return programa->actual != NULL;
}




void agregar_post(usuario_t *usuario, post_t *post, size_t autor_id, size_t post_id) { 
    size_t afinidad = (size_t)abs((int)(usuario_id(usuario) - autor_id));
    recargar_feed(usuario, post, post_id, afinidad);
}

void agregar_post_a_feeds(algogram_t *programa, char *publicacion, size_t id_post) {

    size_t autor_id = usuario_id(programa->actual);
    post_t* post_nuevo = post_crear(publicacion, usuario_nombre(programa->actual), id_post, autor_id);
    // agrego a contenedor de posts
    if (!vector_agregar(programa->posts, post_nuevo)){
        post_destruir(post_nuevo);
        return;
    }


    hash_iter_t *iter = hash_iter_crear(programa->usuarios); 

    while (!hash_iter_al_final(iter)){
        usuario_t *usuario = (usuario_t*) hash_obtener(programa->usuarios, hash_iter_ver_actual(iter));
        if (usuario_id(usuario) != usuario_id(programa->actual)) {
			agregar_post(usuario, post_nuevo, autor_id, id_post); 
        }
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    
}

bool ver_feed_siguiente(algogram_t *programa) {
    return ver_feed(programa->actual);
}

void dar_like(algogram_t *programa, size_t id_post) {
    post_likear((post_t*)vector_obtener(programa->posts, id_post), usuario_nombre(programa->actual)); 
}

bool mostrar_likes(algogram_t *programa, size_t id_post) {
    post_t *post = (post_t*)vector_obtener(programa->posts, id_post);
    if (!post_cantidad_likes(post)) return false;
    imprimir_likes(post);
    return true;
}

char* leer_comando(FILE *archivo){
	size_t tamanio = 0;
	char *comando = NULL;
	size_t leido = getline(&comando, &tamanio, archivo);
	if (leido == ERROR_LEER_ARCHIVO){
		free(comando);
		return NULL;
	}
	return comando;
}


