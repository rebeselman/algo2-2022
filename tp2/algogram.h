// gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c
// gdb ./pruebas
// valgrind --s --leak-check=full ./pruebas usuarios.txt
// ./pruebas.sh PATH-A-EJECUTABLE-TP2

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct algogram algogram_t;

// Crea la base de datos de la red social. Recibe el archivo de usuarios.
// Post: Se inició la base de datos de algogram.
algogram_t* algogram_crear(FILE *archivo);

// Elimina la base de datos de la red social Algogram. Recibe al programa creado anteriormente.
// Pre: el programa fue creado.
// Post: el programa se destruyó. 
void algogram_destruir(algogram_t *programa);

// Recibe el nombre del usuario que desea loguearse, si es un usuario en la base de datos, lo loguea y
// devuelve true, en caso contrario devuelve false.
// Pre: el programa fue creado.
// Post: se logueó al usuario.
bool loguear(algogram_t *programa, char *usuario);

// Desloguea al usuario actual.
// Pre: el programa fue creado.
// Post: se deslogueó al usuario.
void desloguear(algogram_t *programa);

// Devuelve true si hay algún usuario logueado, false en caso contrario.
// Pre: el programa fue creado.
bool esta_logueado(algogram_t *programa);


// Se encarga de crear y agregar el post hecho por el usuario logueado a los feeds del resto de los usuarios.
// Pre: el programa fue creado.
// Post: Se agregó al feed de todos los usuarios (menos al logueado) el nuevo post.
void agregar_post_a_feeds(algogram_t *programa, char *publicacion, size_t id_post);

// Muestra por salida estándar el post con más prioridad a ser visto en el feed del usuario logueado.
// Pre: el programa fue creado.
// Post: se imprimió el post.
bool ver_feed_siguiente(algogram_t *programa);

// Recibe el id de un post, y si válido le da like a post, y el usuario logueado se guarda entre los usuarios que
// dieron like a ese post.
// Pre: el programa fue creado
// Post: Se agregó al usuario logueado entre los usuarios que le dieron like a ese post.
void dar_like(algogram_t *programa, size_t id_post);

// Recibe el id de un post, y si es válido se muestran los nombres de los usuarios que le dieron like a ese post.
// Pre: el programa fue creado.
// Post: se mostró por salida estándar los nombres de los usuarios que le dieron like a ese post.
bool mostrar_likes(algogram_t *programa, size_t id_post);

// Lee los comandos ingresados por consola.
char *leer_comando(FILE *archivo);
