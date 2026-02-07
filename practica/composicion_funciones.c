#include "composicion_funciones.h"
#include <stdlib.h>
#include <stdio.h>
#include "pila.h"
const size_t CAPACIDAD_INICIAL = 10;

struct composicion{
	pila_t* pila_funciones;
};



//Inicializa la composición para que en algún momento se puedan agregar funciones para emular composiciones.
composicion_t* composicion_crear(){ //es de orden 8*O(1) -> O(1)
	composicion_t* composicion_nueva = malloc(sizeof(composicion_t)); //O(1)
	if (!composicion_nueva) return NULL; //O(1)
	pila_t* pila_funciones_nueva = pila_crear();//O(1) 
	if (!pila_funciones_nueva){	//O(1)
		free(composicion_nueva); //O(1)
		return NULL; //O(1)

	}
	composicion_nueva ->pila_funciones =  pila_funciones_nueva; //O(1)
	return composicion_nueva; //O(1)
}

void composicion_destruir(composicion_t* composicion){ // es de orden O(1)+ O(N)-> O(N)
	pila_destruir(composicion->pila_funciones);
	free(composicion);//O(1)
}

//Se agregan funciones a la composición en el orden correcto, por ejemplo para f(g(h(x))) deberías prime
//ro agregar f, g y h y al final llamar a composicion aplicar, en ese orden.
bool composicion_agregar_funcion(composicion_t* composicion, double (*f)(double)){  //Orden 2O(1)-> O(1)
	bool res = pila_apilar(composicion->pila_funciones, f); //O(1)
	return res; //O(1)
}



//devuelve el valor de la composición al pasarle un numero real.
double composicion_aplicar(composicion_t* composicion, double numero){ // O(1) + O(N)-> O(N)
	double res; //O(1)
	//if (cola_esta_vacia(composicion->cola_funciones)) return;
	double (*aplicar_funcion)(double) = pila_desapilar(composicion->pila_funciones); //O(1)
	res = aplicar_funcion(numero);//? depende de la funcion que haya apilado el usuario.
	while (!pila_esta_vacia(composicion->pila_funciones)){//O(N) depende del valor de N funciones encoladas
		aplicar_funcion = pila_desapilar(composicion->pila_funciones);//O(1)
		res = aplicar_funcion(res);//? ídem
	}
	return res; //O(1)
	
}


//int (*p[4]) (int x, int y);
// result = (*p[op]) (i, j);
//  printf("%d", result);

