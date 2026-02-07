#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "post.h"

extern char* strdup(const char*);

struct post {
    char *publicacion; 
    char *autor; 
    abb_t *likes; 
    size_t post_id;    
    size_t autor_id; 
};


// Una version de strdup pero que guarda la cadena con una letra menos
// para no generar problemas al imprimir
char *strdup_autor(const char *cadena) {
	size_t len = strlen(cadena);
    char* copia = strdup(cadena);
    if (!copia) return NULL;

    copia[len-1] =  '\0';
    return copia;
}


post_t *post_crear(char *publicacion, char *autor, size_t post_id, size_t autor_id) {
    post_t *post = malloc(sizeof(post_t)); 
    if (!post) return NULL;

    post->publicacion = strdup(publicacion); 
    if(!post->publicacion) {
        free(post);
        return NULL;
    }

    post->autor = strdup_autor(autor);   
    if(!post->autor) {
        free(post->publicacion);
        free(post);
        return NULL;
    }

    post->likes = abb_crear(strcmp, free); 
    if (!post->likes) {
        free(post->publicacion);
        free(post->autor);
        free(post);
        return NULL;
    }

    post->post_id = post_id;
    post->autor_id = autor_id;

    return post;
}


void post_destruir(void* post){
    post_t* post_ = (post_t*)post;
    abb_destruir(post_->likes);
    free(post_->publicacion);
    free(post_->autor);
    free(post_);
}

bool post_likear(post_t *post, char *usuario) {
    char *likeador = strdup_autor(usuario);
    if (!likeador) return false;

    if (!abb_guardar(post->likes, usuario, likeador)){
        free(likeador);
        return false;
    }
    return true;
}


size_t post_cantidad_likes(post_t *post) {
    return abb_cantidad(post->likes);
}


void post_imprimir(post_t *post) {  
    printf("Post ID %ld\n", post->post_id);
    printf("%s dijo: %s", post->autor, post->publicacion); 
    printf("Likes: %ld\n", abb_cantidad(post->likes));
}


bool visitar(const char *dato, void *extra, void *extra2) {
    char *likeador = (char*)dato;
    printf("	%s", likeador);
    return true;
}


void imprimir_likes(post_t *post) { 
    printf("El post tiene %ld likes:\n", abb_cantidad(post->likes));
    abb_in_order(post->likes, visitar, NULL);
}
