#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

const size_t NUM_ALGUNOS_ELEMENTOS = 6;
const size_t NUM_MUCHOS_ELEMENTOS = 1000;
// Función de comparación

int comparar_enteros(const void *a, const void *b){
	if (*(int*) a > *(int*)b) return 1;
	else if (*(int*)a < *(int*)b) return -1;
	else return 0;
	
}

static void prueba_heap_vacio(){
	printf("PRUEBA HEAP VACIO\n");
	heap_t* heap = heap_crear(comparar_enteros);
	print_test("cantidad de elementos en el heap es 0", heap_cantidad(heap) == 0);
	print_test("el heap está vacío", heap_esta_vacio(heap));
	print_test("ver máximo devuelve NULL", !heap_ver_max(heap));
	print_test("desencolar devuelve NULL", !heap_desencolar(heap));
	heap_destruir(heap, NULL);
	print_test("el heap se destruyó", true);
}

static void prueba_heap_algunos_elementos(){
	printf("PRUEBA HEAP ALGUNOS ELEMENTOS\n");
	heap_t* heap = heap_crear(comparar_enteros);
	
	// Creo un arreglo de enteros
	int** arreglo = malloc(NUM_ALGUNOS_ELEMENTOS*sizeof(int*));
	
	int* elem_5 = malloc(sizeof(int));
	*elem_5 = 5;
	arreglo[2] = elem_5;
	int* elem_2 = malloc(sizeof(int));
	*elem_2 = 2;
	arreglo[4] = elem_2;
	int* elem_6 = malloc(sizeof(int));
	*elem_6 = 6;
	arreglo[1] = elem_6;
	int* elem_10 = malloc(sizeof(int));
	*elem_10 = 10;
	arreglo[0] = elem_10;
	int* elem_1 = malloc(sizeof(int));
	*elem_1 = 1;
	arreglo[5] = elem_1;
	int* elem_4 = malloc(sizeof(int));
	*elem_4 = 4;
	arreglo[3] = elem_4;
	
	// Encolo los elementos de forma arbitraria
	
	print_test("se encoló el número 5",heap_encolar(heap, arreglo[2]));
	print_test("la cantidad de elem es 1", heap_cantidad(heap) ==  1);
	print_test("heap ver máximo ve devuelve 5", heap_ver_max(heap) == arreglo[2]);

	print_test("se encoló el número 2",heap_encolar(heap, arreglo[4]));

	print_test("se encoló el número 6", heap_encolar(heap, arreglo[1]));
	print_test("se encoló el número 10", heap_encolar(heap, arreglo[0]));
	print_test("se encoló el número 1", heap_encolar(heap, arreglo[5]));
	
	print_test("se encoló el número 4", heap_encolar(heap, arreglo[3]));
	
	// Desencolo y verifico el orden-> deberían salir los elementos de mayor prioridad primero
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		void * elem_desencolado = heap_desencolar(heap);
		if (elem_desencolado != arreglo[i]){
			print_test("no se respeta la prioridad", false);
			printf("%i\n", *(int*) elem_desencolado);
		}
		free(elem_desencolado);
	}
	print_test("se desencolaron los elementos y se respetó la invariante de heap", true);
	print_test("la cantidad de elementos en el heap es 0", heap_cantidad(heap) ==  0);
	print_test("el heap está vaío", heap_esta_vacio(heap));
	free(arreglo);
	heap_destruir(heap, free);
	print_test("el heap se destruyó", true);		
}
	

static void prueba_heap_volumen(){
	printf("PRUEBA HEAP VOLUMEN\n");
	heap_t* heap = heap_crear(comparar_enteros);
	
	void** arreglo = malloc(NUM_MUCHOS_ELEMENTOS*sizeof(void*));
	for (int i = 0; i < NUM_MUCHOS_ELEMENTOS; i++){
		int* elemento = malloc(sizeof(int));
		*elemento = i;
		arreglo[i] = elemento;
		heap_encolar(heap, elemento);
		
	}

	print_test("se encolaron los elementos", true);
	for (int i = 0; i < NUM_MUCHOS_ELEMENTOS; i++){
		void* elemento = heap_desencolar(heap);
		if (comparar_enteros(elemento, arreglo[NUM_MUCHOS_ELEMENTOS-1-i]) != 0) print_test("no se respeta la invariante de heap", false);
		free(elemento);
	}

	
	
	free(arreglo);
	heap_destruir(heap, free);
	print_test("el heap se destruyó", true);
}

static void prueba_heap_crear_heap_a_traves_de_arreglo(){
	printf("PRUEBA HEAP A TRAVES DE ARREGLO\n");
	// Creo arreglo
	void** arreglo = malloc(NUM_ALGUNOS_ELEMENTOS*sizeof(void*));
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		int* elemento = malloc(sizeof(int));
		*elemento = i;
		arreglo[i] = elemento;	
	}
	
	heap_t* heap = heap_crear_arr(arreglo, NUM_ALGUNOS_ELEMENTOS, comparar_enteros);
	
	// Imprimo heap apara ver si cumple propiedad de heap
	for (size_t i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		void* elemento = heap_desencolar(heap);
		if (*(int*) elemento != *(int*)arreglo[NUM_ALGUNOS_ELEMENTOS-i-1]) print_test("no se respeta la invariante de heap", true);
		free(elemento);
	}
	heap_destruir(heap, free);
	free(arreglo);
}


static void prueba_heap_heap_sort(){
	printf("PRUEBA_HEAP_SORT\n");
	void** arreglo = malloc(NUM_ALGUNOS_ELEMENTOS*sizeof(void*));
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		int* elemento = malloc(sizeof(int));
		*elemento = (int)NUM_ALGUNOS_ELEMENTOS-i;
		arreglo[i] = elemento;
	}
	heap_sort(arreglo, NUM_ALGUNOS_ELEMENTOS, comparar_enteros);
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		if (*(int*) arreglo[i] != i+1)print_test("no está ordenado", false);
	}
	heap_t* heap = heap_crear_arr(arreglo, NUM_ALGUNOS_ELEMENTOS, comparar_enteros);
	heap_destruir(heap, free);
	free(arreglo);
}




void pruebas_heap_estudiante(){
	prueba_heap_vacio();
	prueba_heap_algunos_elementos();
	prueba_heap_volumen();
	prueba_heap_crear_heap_a_traves_de_arreglo();
	prueba_heap_heap_sort();
}
