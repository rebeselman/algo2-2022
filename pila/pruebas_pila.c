#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int numero_algunos_elementos = 10;
const int numero_muchos_elementos = 10000;

static void desapilar_verificando_orden(pila_t* pila ,void** arreglo_auxiliar, size_t tam){
	/* Función auxiliar */
	for (int i = 0; i < tam; i++){
		if (pila_ver_tope(pila) != &arreglo_auxiliar[tam-1-i]) print_test("elemento del tope no cumple orden correcto", false);
		void* elemento_desapilado = pila_desapilar(pila);
		if (elemento_desapilado != &arreglo_auxiliar[tam-1-i]) print_test("elemento desapilado no cumple orden correcto", false);
	}
	print_test("los elementos desapilados cumplieron el orden correcto", true);	
}


static void prueba_pila_vacia(void) {
	printf("INICIO DE PRUEBAS CON PILA VACÍA\n");
    pila_t* pila = pila_crear();
    
    print_test("pila crear me devuelve una pila vacía", pila_esta_vacia(pila) == true);
    print_test("si intento ver el tope me devulve NULL", pila_ver_tope(pila) == NULL);
    print_test("si desapilo me devuelve NULL", pila_desapilar(pila) == NULL);
    
    /* Destruyo la pila */
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    
}

static void prueba_pila_algunos_elementos(void){
	/*El objetivo es probar que se mantiene la invariante de pila al desapilar los elementos*/
	printf("INICIO DE PRUEBAS CON PILA CON ALGUNOS ELEMENTOS\n");
	
	/*Creo la pila*/
	pila_t* pila = pila_crear();
	
	/*Para probar la invariante de pila, creo un arreglo y voy a apilar sus posiciones de memoria para luego verificar si son las mismas al desapilarlas*/
	void** arreglo_auxiliar = malloc(numero_algunos_elementos*sizeof(void*));
	
	/*Apilo las posiciones de memoria del arreglo*/
	for (int i = 0; i < numero_algunos_elementos; i++){
		pila_apilar(pila, &arreglo_auxiliar[i]);
	}
	
	/*Desapilo las posiciones de memoria del arreglo y verifico que estén en el orden correcto*/
	desapilar_verificando_orden(pila, arreglo_auxiliar, numero_algunos_elementos);
	

	/*Pruebo que la pila está vacía*/
	print_test("la pila está vacía", pila_esta_vacia(pila) == true);

    /* Destruyo la pila */
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    
    free(arreglo_auxiliar);
}

/*Pruebas de la pila para un volumen grande de elementos apilados*/
static void prueba_pila_volumen(void){
	printf("INICIO PRUEBA PILA VOLUMEN\n");
	
	/*Creo la pila*/
	pila_t* pila = pila_crear();
	
	/*Para probar la invariante de pila con un volumen grande de elementos apilados, creo un arreglo y voy a apilar sus posiciones de memoria para luego verificar si son las mismas al desapilarlas*/
	void** arreglo_auxiliar = malloc(numero_muchos_elementos*sizeof(void*));
	
	/*Apilo las posiciones de memoria del arreglo*/
	for (int i = 0; i < numero_muchos_elementos; i++){
		pila_apilar(pila, &arreglo_auxiliar[i]);
	}
	
	/*Desapilo las posiciones de memoria del arreglo y verifico que estén en el orden correcto*/
	desapilar_verificando_orden(pila, arreglo_auxiliar, numero_muchos_elementos);
	
	/*Pruebo que al desapilar hasta que esté vacía hace que la pila se comporte como recién creada.*/
	print_test("la pila está vacía", pila_esta_vacia(pila) == true);
	print_test("desapilar la pila vacía me devuelve null", pila_desapilar(pila) ==  NULL);
	print_test("si la pila está vacía e intento ver el tope me devuelve null", pila_ver_tope(pila) == NULL);
	
	
	
    /* Destruyo la pila */
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    
    free(arreglo_auxiliar);	
}


static void prueba_pila_elemento_null(){
	printf("INICIO PRUEBA PILA ELEMENTO NULL\n");
	
	/*Creo la pila*/
	pila_t* pila = pila_crear();
	
	print_test("puedo apilar el elemento NULL", pila_apilar(pila, NULL) == true);
	
	print_test("elemento NULL está apilado", pila_esta_vacia(pila) == false);
	
	print_test("el tope es el elemento NULL", pila_ver_tope(pila) ==  NULL);
	
	void* elemento_null = pila_desapilar(pila);
	
	print_test("elemento desapilado es NULL", elemento_null == NULL);
	
	
	/*Pruebo que al desapilar hasta que esté vacía hace que la pila se comporte como recién creada.*/
	print_test("la pila está vacía", pila_esta_vacia(pila) == true);
	print_test("desapilar la pila vacía me devuelve null", pila_desapilar(pila) ==  NULL);
	print_test("si la pila está vacía e intento ver el tope me devuelve null", pila_ver_tope(pila) == NULL);
	

    /* Destruyo la pila */
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
}

	
void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_algunos_elementos();
    prueba_pila_volumen();
    prueba_pila_elemento_null();
   
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
