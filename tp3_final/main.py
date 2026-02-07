#!/usr/bin/python3

import sys
import recomendify

PRIMER_ARGUMENTO = 0
SEGUNDO_ARGUMENTO = 1
CANTIDAD_DE_ARGUMENTOS_VALIDOS_1 = 1
CANTIDAD_DE_ARGUMENTOS_VALIDOS_2 = 2
CANTIDAD_DE_ARGUMENTOS_VALIDOS_3 = 3
SEPARADOR_CANCIONES = ">>>>"
# python3 main.py spotify.tsv 

sys.setrecursionlimit(25000)


def procesar_comando_rango_ciclo(comando):
    if (len(comando) < CANTIDAD_DE_ARGUMENTOS_VALIDOS_3): return None 
    comando.pop(PRIMER_ARGUMENTO)
    numero = comando.pop(PRIMER_ARGUMENTO)
    cancion = ' '.join(comando)
    return int(numero), cancion



def procesar_comando_recomendacion(comando):

    if (len(comando) < CANTIDAD_DE_ARGUMENTOS_VALIDOS_3):
        return None
    comando.pop(PRIMER_ARGUMENTO)
    usuario_o_cancion = comando.pop(PRIMER_ARGUMENTO)
    numero = comando.pop(PRIMER_ARGUMENTO)
  
    comando = ' '.join(comando)
    lista_de_canciones =  comando.split(SEPARADOR_CANCIONES)

    for i in range(len(lista_de_canciones)):
        lista_de_canciones[i] = lista_de_canciones[i].strip()
    return usuario_o_cancion, int(numero), lista_de_canciones

    


def procesar_comando_mas_importantes(comando):
    
    if (len(comando) != CANTIDAD_DE_ARGUMENTOS_VALIDOS_2): return None
    return comando[SEGUNDO_ARGUMENTO]


def procesar_comando_camino(comando):
    if (len(comando) < CANTIDAD_DE_ARGUMENTOS_VALIDOS_2): return None
    comando.pop(PRIMER_ARGUMENTO)
    comando = ' '.join(comando)
    lista_de_canciones =  comando.split(SEPARADOR_CANCIONES)
    if (len(lista_de_canciones) != CANTIDAD_DE_ARGUMENTOS_VALIDOS_2): return None

    origen = lista_de_canciones[PRIMER_ARGUMENTO].strip()
    destino = lista_de_canciones[SEGUNDO_ARGUMENTO].strip()

    return origen, destino


def main():
    lista_argumentos = sys.argv
    if (len(lista_argumentos) != CANTIDAD_DE_ARGUMENTOS_VALIDOS_2): 
        print("Cantidad de argumentos inválida")
        return

    # Se inicia el programa
    programa = recomendify.Recomendify()

    # Se intenta procesar el archivo de datos
    if (not programa.procesar_archivo(lista_argumentos[SEGUNDO_ARGUMENTO])):
        print("Error al intentar leer el archivo")
        return
    
    # Aca se empieza a obtener inputs
    for comando in sys.stdin:
        subcomandos = comando.strip().split()
        if (not subcomandos): continue
        if (subcomandos[PRIMER_ARGUMENTO] == "camino"):
            res = procesar_comando_camino(subcomandos)
            if (res):
                origen, destino = res
                if (programa.cancion_valida(origen) and programa.cancion_valida(destino)):
                    programa.camino(origen, destino)
                else:
                    print("Tanto el origen como el destino deben ser canciones")
        elif (subcomandos[PRIMER_ARGUMENTO] == "mas_importantes"):
            res = procesar_comando_mas_importantes(subcomandos)
            if (res):
                numero = res
                programa.mas_importantes(int(numero))
        elif (subcomandos[PRIMER_ARGUMENTO] == "recomendacion"): 
            res = procesar_comando_recomendacion(subcomandos)
            if (res):
                usuario_o_cancion, numero, lista_canciones = res
                programa.recomendacion(usuario_o_cancion, numero, lista_canciones)
        
        elif (subcomandos[PRIMER_ARGUMENTO] == "ciclo"):
            res = procesar_comando_rango_ciclo(subcomandos)
            if (res):
                numero, cancion = res
                programa.ciclo(numero, cancion)      
        elif (subcomandos[PRIMER_ARGUMENTO] == "rango"):
            res = procesar_comando_rango_ciclo(subcomandos)
            if (res):
                numero, cancion = res
                programa.rango(numero, cancion)
            


if __name__ == '__main__':
    main()