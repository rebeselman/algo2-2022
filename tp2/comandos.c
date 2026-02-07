#include "comandos.h"

bool error_usuario_logueado(algogram_t* programa, char* comando){
    if (esta_logueado(programa)) { 
        printf("Error: Ya habia un usuario loggeado\n");
        free(comando);
        return true;
    }
    return false;
}

bool error_usuario_no_logueado(algogram_t* programa, char* comando){
    if (!esta_logueado(programa)){
        printf("Error: no habia usuario loggeado\n");
        free(comando);
        return true;
    }
    return false;
}

void login(algogram_t* programa, char* comando, char* subcomando){
    if (loguear(programa, subcomando)) { 
        printf("Hola %s", subcomando);               
    }
    else {
        printf("Error: usuario no existente\n");
    }
    free(subcomando);
    free(comando); 
}

// Si el subcomando falló en crearse se libera la memoria del comando y se corta el programa.
char* leer_subcomando(char* comando){
	char* subcomando = leer_comando(stdin);
	if (!subcomando) {
        free(comando);
        return NULL;
    }

    return subcomando;
}

void publicar(algogram_t* programa, char* comando, char* subcomando, size_t* post_id){
    agregar_post_a_feeds(programa, subcomando, *post_id);
    (*post_id)++;
    printf("Post publicado\n");
    free(subcomando);
    free(comando);
}

void logout(algogram_t* programa, char* comando){
    desloguear(programa);
    printf("Adios\n");
    free(comando);  
}


void ver_siguiente_feed(algogram_t* programa, char* comando){
    if (!esta_logueado(programa) || !ver_feed_siguiente(programa)) { 
        printf("Usuario no loggeado o no hay mas posts para ver\n");
    }
    free(comando);
}

void likear_post(algogram_t* programa, char* comando, char* subcomando, size_t* post_id){
    int post_num = atoi(subcomando);
    if (!esta_logueado(programa) ||  post_num >= *post_id) {
        printf("Error: Usuario no loggeado o Post inexistente\n");
        free(comando);
        free(subcomando);
        return;
        }

    dar_like(programa, post_num);
    printf("Post likeado\n"); 

    free(subcomando);
    free(comando);
}


void mostrar_likes_aux(algogram_t* programa, char* comando, char* subcomando, size_t* post_id){
    int post_num = atoi(subcomando);
    if (post_num >= *post_id || !mostrar_likes(programa, post_num)) { 
        printf("Error: Post inexistente o sin likes\n");
        free(subcomando);
        free(comando);
        return;
    }
    free(subcomando);
    free(comando);
}

bool comandar(algogram_t *programa, size_t *post_id) {
    char* comando = leer_comando(stdin); 
	if (!comando) return false;
		
    if (strcmp(comando, "login\n") == 0) {
        if (error_usuario_logueado(programa, comando)) return true;
        
        char *subcomando = leer_subcomando(comando);
        if (!subcomando) return false;

        login(programa, comando, subcomando);

        return true;
    }

    if (strcmp(comando, "logout\n")==0) {
        if (error_usuario_no_logueado(programa, comando)) return true;

        logout(programa, comando);
        return true;
    }

    if (strcmp(comando, "publicar\n")==0) {
        if (error_usuario_no_logueado(programa, comando)) return true;

        char *subcomando = leer_subcomando(comando);
        if (!subcomando) return false;

        publicar(programa, comando, subcomando, post_id);
        return true;
    }

    if (strcmp(comando, "ver_siguiente_feed\n") == 0) {
        ver_siguiente_feed(programa, comando);
        return true;
    }

    if (strcmp(comando, "likear_post\n") == 0) {
        char *subcomando = leer_subcomando(comando);
        if (!subcomando) return false;

        likear_post(programa, comando, subcomando, post_id);
        return true;
    }

    if (strcmp(comando, "mostrar_likes\n") == 0) {
        char *subcomando = leer_subcomando(comando);
        if (!subcomando) return false;

        mostrar_likes_aux(programa, comando, subcomando, post_id);
        return true;
    }

    free(comando);
    return true;
}


void ejecutar_programa(algogram_t *programa) {
    bool resultado = true;
    size_t post_id = 0;

    while(resultado) {
        resultado = comandar(programa, &post_id);
    }
}