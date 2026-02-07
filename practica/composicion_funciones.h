#include <stdbool.h>

struct composicion;
typedef struct composicion composicion_t;



//Inicializa la composición para que en algún momento se puedan agregar funciones para emular composiciones.
composicion_t* composicion_crear();

void composicion_destruir(composicion_t* composicion);

//Se agregan funciones a la composición en el orden correcto, por ejemplo para f(g(h(x))) deberías prime
//ro agregar f, g y h y al final llamar a composicion aplicar, en ese orden.
bool composicion_agregar_funcion(composicion_t* composicion, double (*f)(double));

//devuelve el valor de la composición al pasarle un numero real.
double composicion_aplicar(composicion_t* composicion, double numero);
