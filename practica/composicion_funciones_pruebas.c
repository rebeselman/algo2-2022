#include "composicion_funciones.h"
#include <stdio.h>
//funciones para probar TDA
double suma_1(double num1){
	return num1 + 1.05;
}

double multiplicar_por_2(double num1){
	return num1*2.0;
}

double restar_1(double num1){
	return num1 - 1.0;
}



static void prueba(void){
	composicion_t* composicion_nueva = composicion_crear();
	composicion_agregar_funcion(composicion_nueva, suma_1);
	composicion_agregar_funcion(composicion_nueva, multiplicar_por_2);
	composicion_agregar_funcion(composicion_nueva, restar_1);
	double res = composicion_aplicar(composicion_nueva, 4.0);
	printf("%lf\n", res);
	
	composicion_destruir(composicion_nueva);
	
}





int main(void){
	prueba();
}
