#include "comandos.h"

#define PRIMER_PARAMETRO 1
#define ERROR_ABRIR 1;
#define ERROR_LEER 2;


int main (int argc, char* argv[]) {
    FILE *archivo = fopen(argv[PRIMER_PARAMETRO], "rt");
    if (!archivo) {
        fprintf(stderr, "Error: no se pudo abrir el archivo\n");
        return ERROR_ABRIR;
    }

    algogram_t *programa = algogram_crear(archivo);
    
    if(!programa){ 
        fprintf(stderr, "Error: no se pudo leer el archivo\n");
        fclose(archivo);
        return ERROR_LEER;
    }

    fclose(archivo);

    ejecutar_programa(programa);

    algogram_destruir(programa);

    return 0;
}
