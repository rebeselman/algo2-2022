#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const size_t NUMERO_VOLUMEN = 10000;

/* ****************
 * PRUEBAS DE ABB * 
 ******************/


static void prueba_crear_abb_vacio(abb_comparar_clave_t comparar){
  printf("SE INICIAN PRUEBAS CON ABB VACIO\n");
    abb_t* abb = abb_crear(comparar,NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_borrar_por_niveles(abb_comparar_clave_t comparar, abb_destruir_dato_t destruir){
	printf("SE INICIAN PRUEBAS CON ABB POCAS CLAVES BORRANDO TODO EL ARBOL POR NIVELES\n");
	
	abb_t* abb = abb_crear(comparar, destruir);
	
	char* clave_o = "o";
	char* clave_p = "p";
	char* clave_q = "q";
	char* clave_r = "r";
	char* clave_s = "s";
	char* clave_a = "a";
	
	print_test("se guardó la clave (q)", abb_guardar(abb, clave_q, NULL));
	print_test("se guardó la clave(r)", abb_guardar(abb, clave_r, NULL)); 
	print_test("se guardó la clave(o)", abb_guardar(abb, clave_o, NULL));
	print_test("se guardó la clave(p)", abb_guardar(abb, clave_p, NULL));
	print_test("se guardó la clave(a)", abb_guardar(abb, clave_a, NULL));
	print_test("se guardó la clave(s)", abb_guardar(abb, clave_s, NULL));	
	
	print_test("se borró la clave (a)", abb_borrar(abb, clave_a) == NULL);
	print_test("se borró la clave(p)", abb_borrar(abb, clave_p) == NULL); 	
	print_test("se borró la clave (s)", abb_borrar(abb, clave_s) == NULL);	
	print_test("se borró la clave (o)", abb_borrar(abb, clave_o) == NULL);
	print_test("se borró la clave (r)", abb_borrar(abb, clave_r) == NULL);
	print_test("se borró la clave (q)", abb_borrar(abb, clave_q) == NULL);
	print_test("arbol está vacío", abb_cantidad(abb) == 0);
	abb_destruir(abb);
}

static void prueba_abb_guardar_y_borrar_intercalado_algunos_elementos(abb_comparar_clave_t comparar, abb_destruir_dato_t destruir){
	printf("SE INICIAN PRUEBAS DE GUARDADO Y BORRADO INTERCALADO PARA ALGUNOS ELMENTOS\n");
	abb_t* abb = abb_crear(comparar, destruir);

	char* clave_A = "A";
	char* clave_B = "B";
	char* clave_C = "C";
	char* clave_D = "D";
	char* clave_E =  "E";
	
	

	print_test("se guardó la clave A", abb_guardar(abb, clave_A, &clave_A));
	print_test("se guardó la clave B", abb_guardar(abb, clave_B, &clave_B));
	print_test("se guardó la clave D", abb_guardar(abb, clave_D, &clave_D));
	print_test("se guardó la clave C", abb_guardar(abb, clave_C, &clave_C));
	print_test("se guardó la clave E", abb_guardar(abb, clave_E, &clave_E));
	
	
	print_test("la cantidad es 5", abb_cantidad(abb) == 5);
	
	print_test("se borró la A", abb_borrar(abb, clave_A) == &clave_A);
	print_test("la cantidad es 4", abb_cantidad(abb) == 4);
	print_test("se borró la B", abb_borrar(abb, clave_B) == &clave_B);
	print_test("la cantidad es 3", abb_cantidad(abb) == 3);
	print_test("se borró la D", abb_borrar(abb, clave_D) == &clave_D);
	print_test("la cantidad es 2", abb_cantidad(abb) == 2);	


	abb_destruir(abb);
}


static void prueba_abb_guardar_pocos_elementos_y_obtenerlos(abb_comparar_clave_t comparar, abb_destruir_dato_t destruir){
	printf("SE INICIAN PRUEBAS DE GUARDADO Y BORRADO INTERCALADO PARA ALGUNOS ELMENTOS\n");
	abb_t* abb = abb_crear(comparar, destruir);

	char* clave_o = "o";
	char* clave_p = "p";
	char* clave_q = "q";
	char* clave_r = "r";
	char* clave_s = "s";
	char* clave_a = "a";

	
	print_test("se guardó la clave (q)", abb_guardar(abb, clave_q, &clave_q));
	print_test("se guardó la clave(r)", abb_guardar(abb, clave_r, &clave_r)); 
	print_test("se guardó la clave(o)", abb_guardar(abb, clave_o, &clave_o));
	print_test("se guardó la clave(p)", abb_guardar(abb, clave_p, &clave_p));
	print_test("se guardó la clave(a)", abb_guardar(abb, clave_a, &clave_a));
	print_test("se guardó la clave(s)", abb_guardar(abb, clave_s, &clave_s));
	
	print_test("se obtiene el dato de la clave r", abb_obtener(abb, clave_r) == &clave_r);
	print_test("se obtiene el dato de la clave o", abb_obtener(abb, clave_o) == &clave_o);
	print_test("se obtiene el dato de la clave p", abb_obtener(abb, clave_p) == &clave_p);
	print_test("se obtiene el dato de la clave a", abb_obtener(abb, clave_a) == &clave_a);
	print_test("se obtiene el dato de la clave a", abb_obtener(abb, clave_s) == &clave_s);
	
	
	
	abb_destruir(abb);
}



static void prueba_iterar_abb_vacio(){
	printf("SE INICIAN LAS PRUEBAS DE ITERADOR EXTERNO CON ABB VACIO\n");
	
	abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_iterar_abb(){
	printf("SE INICIAN LAS PRUEBAS DE ITERADOR EXTERNO CON ABB\n");
	abb_t* abb = abb_crear(strcmp, NULL);
;
    
    // Se guardan algunas claves para luego iterar

	char* arreglo[7];
	arreglo[0] = "A";
	arreglo[1] = "B";
	arreglo[2] = "C";
	arreglo[3] = "D";
	arreglo[4] = "E";
	arreglo[5] = "F";
	arreglo[6] = "G";

	// guardo las claves
	print_test("se guardó la clave D", abb_guardar(abb, arreglo[3], NULL));
	print_test("se guardó la clave B", abb_guardar(abb, arreglo[1], NULL));
	print_test("se guardó la clave A", abb_guardar(abb, arreglo[0], NULL));
	print_test("se guardó la clave C", abb_guardar(abb, arreglo[2], NULL));
	print_test("se guardó la clave F", abb_guardar(abb, arreglo[5], NULL));
	print_test("se guardó la clave E", abb_guardar(abb, arreglo[4], NULL));
	print_test("se guardó la clave G", abb_guardar(abb, arreglo[6], NULL));
	print_test("la cantidad es 7", abb_cantidad(abb) == 7);
	int i = 0;
	abb_iter_t* iter = abb_iter_in_crear(abb);	
	while (!abb_iter_in_al_final(iter)){
		if (strcmp(abb_iter_in_ver_actual(iter), arreglo[i]) != 0)print_test("esta mal el iterador", false);
		abb_iter_in_avanzar(iter);
		i++;
	}
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

static void prueba_abb_reemplazar(){
	printf("SE INICIAN LAS PRUEBAS DE REEMPLAZO DE CLAVES\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

 
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir(){
	printf("SE INICIAN LAS PRUEBAS DE REEMPLAZO PERO CON FUNCION DE DESTRUCCION NO NULL\n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    // Pide memoria para 4 valores 
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    // Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) 
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Se destruye el abb (se debe liberar lo que quedó dentro) 
    abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo){ //no se como hacer la prueba de volumen del abb. porque debería crear 500 claves de la nada y ni idea de como hacer eso.
	char** claves = malloc(largo*sizeof(char*));
	for (size_t i = 0; i < largo; i++){
		char* clave = malloc(sizeof(char));
		clave = (char*)i;
		claves[i] = clave;
		 
	
	}
	printf("%s\n", claves[0]);
	free(claves);
}

void pruebas_abb_estudiante() {
	prueba_crear_abb_vacio(strcmp);
	prueba_abb_borrar_por_niveles(strcmp, NULL);
	prueba_abb_guardar_y_borrar_intercalado_algunos_elementos(strcmp, NULL);
	prueba_abb_guardar_pocos_elementos_y_obtenerlos(strcmp, NULL);
	prueba_iterar_abb_vacio();
	prueba_iterar_abb();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_volumen(500);

}

#ifndef CORRECTOR 

int main(void) {
    pruebas_abb_estudiante(strcmp);
    return failure_count() > 0; 
}

#endif
