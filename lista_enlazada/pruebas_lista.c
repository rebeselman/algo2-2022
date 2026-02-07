#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
const int NUM_ALGUNOS_ELEMENTOS = 10;

//funcion para prueba de iterador interno
bool multiplicar_por_2(void* dato, void* extra){
	*(int*)dato *= *(int*) dato;
	return true;
}


static void prueba_lista_vacia(){  
	printf("\n");
	printf("INICIO PRUEBA LISTA VACIA\n");
	
	lista_t* lista = lista_crear();
    if(!lista) return;
    
 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	// Se prueba que se comporta como vacía
	print_test("si intento borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
	print_test("si intento ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
	print_test("si intento ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
	print_test("el largo es 0", lista_largo(lista) == 0);

	lista_destruir(lista, NULL);
	print_test("se destruyó lista vacía, función de destrucción NULL", true);
	printf("\n");
}

static void prueba_lista_unico_elemento(void){
	printf("INICIO PRUEBA LISTA UNICO ELEMENTO\n");
	lista_t *lista = lista_crear();
    if(!lista) return;

 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	// Se prueba que se comporta como vacía
	print_test("si intento borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
	print_test("si intento ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
	print_test("si intento ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
	print_test("el largo es 0", lista_largo(lista) == 0);
	
	// Se crea un elemento arbitrario para agregar a la lista en la primera posición	
	int valor = 1;	
	print_test("inserto el valor en la primera posicion", lista_insertar_primero(lista, &valor));
	print_test("la lista no está vacía", !lista_esta_vacia(lista));
	print_test("si veo el primero es el dato que agregué", lista_ver_primero(lista) == &valor);
	print_test("si veo el ultimo es el dato que agregué", lista_ver_ultimo(lista) == &valor);
	print_test("el largo es 1", lista_largo(lista) ==  1); 
	
	print_test("borro el primer elemento y me devuelve el que agregué", lista_borrar_primero(lista) == &valor);
	print_test("lista está vacía", lista_esta_vacia(lista));
	
	// Se prueba que si ahora inserto en la ultima posición, se cumple todo las pruebas anteriores también
	print_test("inserto el valor en la ultima posicion", lista_insertar_ultimo(lista, &valor));
	print_test("la lista no está vacía", !lista_esta_vacia(lista));
	print_test("si veo el primero es el dato que agregué", lista_ver_primero(lista) == &valor);
	print_test("si veo el ultimo es el dato que agregué", lista_ver_ultimo(lista) == &valor);
	print_test("el largo es 1", lista_largo(lista) ==  1);	
	
	print_test("borro el ultimo elemento y me devuelve el que agregué", lista_borrar_primero(lista) == &valor);
	print_test("lista está vacía", lista_esta_vacia(lista));	
	
	lista_destruir(lista, free);
	print_test("la lista vacía se destruyó, función de destrucción no NULL", true); 
	printf("\n");
}

static void prueba_lista__no_vacia_destruccion_de_datos(){
	printf("INICIO PRUEBA LISTA NO VACIA DESTRUCCION DE DATOS\n");
	lista_t *lista = lista_crear();
    if(!lista) return;

 	print_test("se creó la lista", true);
 	
 	// Voy a agregar punteros a la lista
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++){
		int* puntero = malloc(sizeof(int));
		if (puntero == NULL){
			print_test("malloc me devolvió null", false);
			break;
		}
		lista_insertar_ultimo(lista, puntero);
	}
	print_test("se agregaron punteros dinámicos a la lista", true); 
 	print_test("la lista no esta vacia", !lista_esta_vacia(lista));
	lista_destruir(lista, free);
	print_test("la lista vacía se destruyó, función de destrucción no NULL", true); 
	printf("\n"); 		
}

static void prueba_lista_elemento_null(){
	printf("INICIO PRUEBA LISTA CON ELEMENTO NULL\n");
	lista_t *lista = lista_crear();
		if(!lista) return;
	void* nulo = NULL;
	
	print_test("Se prueba que la lista esta vacia", lista_esta_vacia(lista) == true);
	print_test("Se prueba agregar el elemento NULL", lista_insertar_primero(lista, nulo) == true);
	print_test("Se prueba que la lista no esta vacia despues de agregar elemento NULL", lista_esta_vacia(lista) == false);
	print_test("Se prueba que el primer elemento es NULL", lista_ver_primero(lista) == nulo);
	print_test("Se prueba que el ultimo elemento es NULL", lista_ver_ultimo(lista) == nulo);
	print_test("Se elimina el elemento NULL", lista_borrar_primero(lista) == nulo);
	print_test("Se prueba agregar el elemento NULL al final", lista_insertar_ultimo(lista, nulo) == true);
	print_test("Se prueba que la lista no esta vacia despues de agregar elemento NULL al final", lista_esta_vacia(lista) == false);
	print_test("El primer elemento de la lista es NULL", lista_ver_primero(lista) == nulo);
	print_test("El ultimo elemento de la lista es NULL", lista_ver_ultimo(lista) == nulo);
	print_test("Se prueba borrar el elemento NULL", lista_borrar_primero(lista) == nulo);
	print_test("La lista se encuentra vacia", lista_esta_vacia(lista) == true);
	
	lista_destruir(lista, NULL);
	printf("\n"); 
}

static void prueba_iterador_primera_posicion(void){
	printf("INICIO PRUEBA LISTA ITERADOR EXTERNO PRIMERA POSICION\n");
	lista_t* lista = lista_crear();
    if(!lista) return;

 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	//Se agregan algunos elementos a la lista, creando una lista y agregando las posiciones
	void* arreglo[NUM_ALGUNOS_ELEMENTOS];
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++) lista_insertar_ultimo(lista, &arreglo[i]);
	print_test("se agregaron 10 elementos", true);
	print_test("largo es 10", lista_largo(lista) == 10);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	// Se prueba que el iterador efectivamente esté en el primer elemento de la lista.
	print_test("el iterador está en la primera posición", lista_iter_ver_actual(iter) == &arreglo[0]);
	print_test("el iterador no está al final", !lista_iter_al_final(iter));
	
	//Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.
	int valor = 1;
	print_test("inserto un elemento en la primera posición", lista_iter_insertar(iter, &valor));	
	print_test("el primer elemento de la lista es el insertado", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
	print_test("largo es 11", lista_largo(lista) == 11);	
	
	//Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.
	print_test("remuevo el primer elemento y es el que inserté", lista_iter_borrar(iter) == &valor);
	print_test("largo es 10", lista_largo(lista) == 10);
	print_test("cambia el primer elemento de la lista", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
			

	print_test("se destruyó el iterador", true);
	lista_iter_destruir(iter);
	
	
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true);
	printf("\n");	
}

static void prueba_lista_destruir_free(void) {
    printf("INICIO PRUEBAS DE DESTRUIR CON FREE\n");
    lista_t* lista = lista_crear();
    int* vec1 = malloc(sizeof(int));
    int* vec2 = malloc(sizeof(int));
    
    print_test("Se prueba que el primer vector fue insertado correctamente", lista_insertar_ultimo(lista, vec1));
    print_test("Se prueba que el segundo vector fue insertado correctamente", lista_insertar_ultimo(lista, vec2));
    lista_destruir(lista, free);
    print_test("Se prueba que se destruyó la lista", true);
    
    printf("\n");
}

void destruir_pila(void* pila) {
	pila_destruir((pila_t *) pila);
}

static void prueba_lista_destruir_pila(void) {
    printf("INICIO PRUEBAS DE DESTRUIR CON PILAS\n");
    lista_t* lista = lista_crear();
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();

    print_test("Se prueba que la pila1 fue insertada", lista_insertar_ultimo(lista, pila1));
    print_test("Se prueba que la pila2 fue insertada", lista_insertar_ultimo(lista, pila2));
    lista_destruir(lista, destruir_pila);
    print_test("Se prueba que la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_volumen(void){
	printf("INICIO PRUEBAS DE LISTA CON VOLUMEN DE ELEMENTOS\n");
    lista_t* lista = lista_crear();
    print_test("Se insertan 500 elementos", true);
    int* valor = malloc(500 * sizeof(int)); 
    for(int i = 0; i < 500; i++){        
        if(!lista_insertar_ultimo(lista, &valor[i])) 
            print_test("Error al intentar insertar en la lista", false);
    }
    print_test("Se insertaron 500 elementos en la lista", true);
    print_test("Se prueba que la lista no esta vacia", !lista_esta_vacia(lista));
    int k = 0;
    while(!lista_esta_vacia(lista))
    {
        if(lista_borrar_primero(lista) != &valor[k]){
            print_test("Error al comparar punteros", false);
            break;
        }
        k++;
    }
    print_test("Se prueba que la lista esta vacía y es destruida", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    free(valor);
    printf("\n");
}

static void prueba_iterador_ultima_posicion(){
	printf("INICIO PRUEBA LISTA ITERADOR EXTERNO ULTIMA POSICION\n");
	lista_t* lista = lista_crear();
    if(!lista) return;

 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	//Se agregan algunos elementos a la lista, creando una lista y agregando las posiciones
	void* arreglo[NUM_ALGUNOS_ELEMENTOS];
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++) lista_insertar_ultimo(lista, &arreglo[i]);
	print_test("se agregaron 10 elementos", true);
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	// Se prueba que el iterador efectivamente esté en el primer elemento de la lista.
	print_test("el iterador está en la primera posición", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
	print_test("el iterador no está al final", !lista_iter_al_final(iter));
	
	
	// Itero hasta el ultimo elemento
	while(!lista_iter_al_final(iter)){
		lista_iter_avanzar(iter);
	}
	print_test("el iterador está al final", lista_iter_al_final(iter));
	
	//Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.
	int valor = 1;
	print_test("inserto un elemento al final", lista_iter_insertar(iter, &valor));	
	print_test("el ultimo elemento de la lista es el insertado", lista_ver_ultimo(lista) == lista_iter_ver_actual(iter));
	//printf("%p %p", lista_ver_ultimo(lista), lista_iter_ver_actual(iter));		
	print_test("iterador no está al final", !lista_iter_al_final(iter));
	print_test("largo es 11", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS+1);
	
	//Remover el último elemento con el iterador cambia el último de la lista.	
	
	print_test("remuevo el ultimo elemento de la lista", lista_iter_borrar(iter) == &valor);	
	print_test("el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista) == &arreglo[NUM_ALGUNOS_ELEMENTOS-1]);
	//printf("%p %p", lista_ver_ultimo(lista), lista_iter_ver_actual(iter));		
	print_test("iterador está al final", lista_iter_al_final(iter));
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);	

	print_test("se destruyó el iterador", true);
	lista_iter_destruir(iter);
	
	
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true); 
	printf("\n");		
}

static void prueba_iterador_media_posicion(){
	printf("INICIO PRUEBA LISTA ITERADOR EXTERNO MEDIA POSICION\n");
	lista_t* lista = lista_crear();
    if(!lista) return;

 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	//Se agregan algunos elementos a la lista, creando una lista y agregando las posiciones
	void* arreglo[NUM_ALGUNOS_ELEMENTOS];
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++) lista_insertar_ultimo(lista, &arreglo[i]);
	print_test("se agregaron 10 elementos", true);
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	// Se prueba que el iterador efectivamente esté en el primer elemento de la lista.
	print_test("el iterador está en la primera posición", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
	print_test("el iterador no está al final", !lista_iter_al_final(iter));
	
	int valor = 1;
	//Insertar un elemento en el medio se hace en la posición correcta.
	while(!lista_iter_al_final(iter)){
		if(lista_iter_ver_actual(iter) == &arreglo[NUM_ALGUNOS_ELEMENTOS/2]) {
			lista_iter_insertar(iter, &valor);
			break;
		}
		lista_iter_avanzar(iter);
	}
	print_test("largo es 11", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS+1);
	print_test("ver actual es el dato que inserté", lista_iter_ver_actual(iter) == &valor);
	print_test("lo remuevo", lista_iter_borrar(iter) == &valor);
	print_test("si veo el actual es el elemento anterior que estaba en el medio", lista_iter_ver_actual(iter) == &arreglo[NUM_ALGUNOS_ELEMENTOS/2]);
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);	
	
	
	//creo un nuevo iterador para buscar el elemento borrado
	print_test("se destruyó el iterador", true);
	lista_iter_destruir(iter);
	lista_iter_t* iter_nuevo = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	// Pruebo que si busco el elemento borrado al medio ya no está.
	while(!lista_iter_al_final(iter_nuevo)){
		if(lista_iter_ver_actual(iter_nuevo) == &valor) {
			print_test("error el elemento borrado si está en la lista", false);
		}
		lista_iter_avanzar(iter_nuevo);
	}	

	print_test("el elemento borrado no está en la lista", true);
	print_test("se destruyó el iterador", true);
	lista_iter_destruir(iter_nuevo);
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true); 
	printf("\n");	
}

static void prueba_lista_iterar_aplicando_funcion(){
	printf("INICIO PRUEBA LISTA ITERADOR INTERNO APLICANDO FUNCION\n");
	lista_t* lista = lista_crear();
    if(!lista) return;
    
 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	//Se agregan a la lista punteros a ente;
	int arreglo[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++) lista_insertar_ultimo(lista, &arreglo[i]);
	print_test("se agregaron 10 elementos", true);
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);
	
	//creo una función que multiplica por dos a los numeros de la lista
	lista_iterar(lista, multiplicar_por_2, NULL);
	print_test("la lista se iteró aplicando la función", true);
	
	//me fijo que efectivamenta hay multiplicado por dos a los elementos de la lista
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);	
	int i = 0;
	while(!lista_iter_al_final(iter)){
		if(*(int*)lista_iter_ver_actual(iter) != arreglo[i]) print_test("la función visitar no funcionó", false); 
		lista_iter_avanzar(iter);
		i++;
	}	
	print_test("la función visitar funcionó", true);
	print_test("se destruyó el iterador", true);
	lista_iter_destruir(iter);
	
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true); 
	printf("\n");
}


static void prueba_iterador_insertar_lista(){
	printf("INICIO PRUEBA LISTA ITERADOR EXTERNO NO AFECTA EL USO DE PRIMITIVAS\n");
	lista_t* lista = lista_crear();
    if(!lista) return;
    
 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	//la idea es probar que las primitivas de la lista funcionan luego de terminar de usar el iterador
	int numero = 1;
	int numero_2 = 2;
	print_test("inserta en lista vacía", lista_iter_insertar(iter, &numero));  //
	print_test("ver_actual es el elemento que inserté", lista_iter_ver_actual(iter) == &numero);
	print_test("inserta en lista", lista_iter_insertar(iter, &numero_2));
	print_test("ver_actual es el elemento que inserté", lista_iter_ver_actual(iter) == &numero_2);
	lista_iter_destruir(iter);
	print_test("se destruyó el iterador", true);

	//inserto utilizando primitivas de la lista
	int numero_3 = 3;
	int numero_4 = 4;
	print_test("lista_insertar_ultimo funciona", lista_insertar_ultimo(lista, &numero_3)); 
	print_test("el elemento insertado es el que inserté", lista_ver_ultimo(lista) == &numero_3);
	print_test("lista_insertar primero funciona", lista_insertar_primero(lista, &numero_4));
	print_test("el primer elemento es el insertado", lista_ver_primero(lista) ==  &numero_4);
	
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true); 
	printf("\n");		
}

static void prueba_iterador_borrar_lista(){
	printf("PRUEBA ITERADOR BORRAR ELEMENTOS DE LA LISTA");
	// La idea es probar que al borrar elementos de una lista creada usando el iter no afecta el uso de las primitivas de la lista después de destruirlo
	lista_t* lista = lista_crear();
    if(!lista) return;

 	//Se prueba que la lista nueva esta vacía
 	print_test("se creó la lista", true);
	print_test("lista nueva está vacía", lista_esta_vacia(lista));
	
	//Se agregan algunos elementos a la lista, creando una lista y agregando las posiciones
	void* arreglo[NUM_ALGUNOS_ELEMENTOS];
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS; i++) lista_insertar_ultimo(lista, &arreglo[i]);
	print_test("se agregaron 10 elementos", true);
	print_test("largo es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("se creó el iterador", true);
	
	// Se prueba que el iterador efectivamente esté en el primer elemento de la lista.
	print_test("el iterador está en la primera posición", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
	print_test("el iterador no está al final", !lista_iter_al_final(iter));	
	
	// Borra la mitad de los elementos de la lista
	while (!lista_iter_al_final(iter)){
		if(lista_iter_ver_actual(iter) == &arreglo[NUM_ALGUNOS_ELEMENTOS/2]) break;
		lista_iter_borrar(iter);
	}
	lista_iter_destruir(iter);
	print_test("se destruyó el iterador", true);
	
	print_test("el primero es el elemento del medio", lista_ver_primero(lista) == &arreglo[NUM_ALGUNOS_ELEMENTOS/2]);
	print_test("el ultimo elmento es el correspondiente", lista_ver_ultimo(lista) == &arreglo[NUM_ALGUNOS_ELEMENTOS-1]);
	print_test("el tamaño es 5", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS/2);
	
	// Vuelvo a a agregar los elementos borrados por el iterador de forma que queden en el orden inicial
	for (int i = 0; i < NUM_ALGUNOS_ELEMENTOS/2; i++)lista_insertar_primero(lista, &arreglo[4-i]);
	
	// Verifico que se hayan agregado bien
	print_test("el tamaño es 10", lista_largo(lista) == NUM_ALGUNOS_ELEMENTOS); 
	for (int i= 0; i < NUM_ALGUNOS_ELEMENTOS; i++)if (lista_borrar_primero(lista) != &arreglo[i]) print_test("error de orden de elementos", false);
	print_test("los elementos se agregaron y eliminaron correctamente", true);	
	
	lista_destruir(lista, NULL);
	print_test("la lista no vacía se destruyó, función de destrucción NULL", true); 
	printf("\n");
}
void pruebas_lista_estudiante(){
	prueba_lista_vacia();
	prueba_lista_unico_elemento();
	prueba_lista__no_vacia_destruccion_de_datos();
	prueba_lista_elemento_null();
	prueba_lista_destruir_free();
	prueba_lista_destruir_pila();
	prueba_lista_volumen();
	prueba_lista_iterar_aplicando_funcion();

	//pruebas iterador externo
	prueba_iterador_primera_posicion();
	prueba_iterador_ultima_posicion();
	prueba_iterador_media_posicion();
	prueba_iterador_insertar_lista();
	prueba_iterador_borrar_lista();
}	
	
#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
