//Imprime la linea dividida por el num_columnas de forma ordenada.
void imprimir_linea_ordenada(char* linea, int num_columnas, int num_carac_leidos);

//Verifica que los parámetros sean válidos, si lo son devuelve true y sino false.
bool validar_parametros(int arg, char* argv[]);

//Recibe un archivo e imprime las lineas de este dividida por el numero de columnas de forma ordenada.
void imprimir_archivo_columnas(int num_columnas, FILE* archivo);

//Intenta abrir el archivo que se envía por parámetro y si falla imrpime un error por salida estándar, sino devuelve el archivo.
FILE* validar_archivo(char* argv[]);


