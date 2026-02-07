from grafo import Grafo
from collections import deque
import random
import heapq

COEFICIENTE_AMORTIZACION = 0.85
COEFICIENTE_CONVERGENCIA_1 = 1000
COEFICIENTE_CONVERGENCIA_2 = 15
LARGO_WALKS = 10
VALOR_WALK_INICIAL = 1



# recibe un grafo no dirigido y devuelve un diccionario con el grado de cada vertice
def grados(grafo):
    grados = {}
    for v in grafo.obtener_vertices():
        grados[v] = 0
        for w in grafo.adyacentes(v):
            grados[v] += 1
    return grados

# recibe un grafo no pesado, un vertice y devuelve un diccionario con listas de 
# los caminos minimos del origen a cada vertice del grafo
def camino_minimo(grafo, origen):
    visitados = set()
    visitados.add(origen)
    caminos = {}
    caminos[origen] = []
    caminos[origen].append(origen)
    q = deque()
    q.append(origen)
    while q:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w in visitados:
                continue
            visitados.add(w)
            q.append(w)
            caminos[w] = []
            for i in range (0, len(caminos[v])):
                caminos[w].append(caminos[v][i])
            caminos[w].append(w)
    return caminos

def bfs(grafo, origen):
    #devuelve diccionario de grados
    visitados = set()
    visitados.add(origen)
    distancia = {}
    for v in grafo.obtener_vertices():
        distancia[v] = "inf"
    distancia[origen] = 0
    q = deque()
    q.append(origen)
    while q:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if not w in visitados:
                distancia[w] = distancia[v] +1
                visitados.add(w)
                q.append(w)
    return distancia


    



# recibe un grafo, un vertice de origen y un destino y devulve una lista con los vertices
# recorridos en el camino mas corto del origen al destino
def camino_mas_corto(grafo, origen, destino):
    caminos = camino_minimo(grafo, origen)
    if (destino not in caminos): 
        return None
    return caminos[destino]

# recibe un grafo, un vertice y un numero N y devuelve la cantidad de vertices
# que estan exactamente a N aristas del origen
def rango_n(grafo, origen, n):
    rango = 0
    distancias = bfs(grafo, origen)
    for v, distancia in distancias.items():
        if distancia == n:
            rango+=1
    return rango

# funcion auxiliar de ciclos_n 

def _ciclos_n(grafo, v, visitados, ciclo, n, origen):
    for w in grafo.adyacentes(v):
        if w in visitados and w!=origen:
            continue
        elif w==origen and n==0:
            ciclo.append(w)
            return True
        
        elif n==0 and w!=origen:
            continue
        elif n == 1 and not grafo.estan_unidos(w, origen):
            visitados.add(w)
            continue
        elif n!= 0 and w == origen: #si se volvio a encontrar con el origen y no se cumple nada creo que no lo deberia agregar al ciclo
            continue
        visitados.add(w)
        ciclo.append(w)
        if _ciclos_n(grafo, w, visitados, ciclo, n-1, origen):
            return True
        else: 
            ciclo.remove(w)
    return False


# recibe un grafo, un vertice y un numero N y devuelve una lista de los
# N vertices del ciclo que termina en su origen o None si no hay tal ciclo
def ciclos_n(grafo, origen, n):
    visitados = set()
    ciclo = []
    ciclo.append(origen)
    if _ciclos_n(grafo, origen, visitados, ciclo, n-1, origen):
        return ciclo    
    return None

# Recibe un grafo y devuelve la cantidad de vertices de este
def contar_vertices(grafo):
    vertices = 0
    for v in grafo.obtener_vertices():
        vertices += 1
    return vertices

# Recibe un grafo y un vertice y calcula la cantidad de adyacentes de este o 1 si no tiene ninguno
def contar_adyacentes(grafo, v):
    adyacentes = 0
    for w in grafo.adyacentes(v):
        adyacentes += 1
    if adyacentes==0:
        return 1
    return adyacentes
    

# recibe un grafo, y determina si es bipartito, devuelve true o false
def es_bipartito(grafo):
    visitados = set()
    azul = set()
    rojo = set()
    for v in grafo.obtener_vertices():
        if v not in visitados:
            visitados.add(v)
            azul.add(v)
            for w in grafo.adyacentes(v):
                if w not in visitados:
                    visitados.add(w)
                    rojo.add(w)
        else:
            for r in grafo.adyacentes(v):
                if r in rojo:
                    return False
        if v in rojo and v in azul:
            return False
    return True

# funcion auxiliar de page rank
def _page_rank(grafo, rank, grados, cantidad_v_grafo):
    for v in grafo.obtener_vertices():
        rank_aux = 0
        for w in grafo.adyacentes(v):
            rank_aux += (rank[w]/grados[w])
        rank[v] = (1-COEFICIENTE_AMORTIZACION)/cantidad_v_grafo + (COEFICIENTE_AMORTIZACION)*rank_aux
    

# recibe un grafo y calcula el page rank de todos sus vertices
# devuelve una lista de todos los vertices ordenados de mayor a menor page rank
def page_rank(grafo):
    ranking = {}
    
    grado = grados(grafo)
   
    cantidad_v_grafo = grafo.cantidad_vertices()
    
    for v in grafo.obtener_vertices():
        ranking[v] = 1/cantidad_v_grafo
  

    for i in range (0, COEFICIENTE_CONVERGENCIA_2):
        _page_rank(grafo, ranking, grado, cantidad_v_grafo)
    #Bien
    #return list(sorted(ranking, key=lambda c: ranking[c]))

    return ranking


# recibe un diccionario de pesos de los adyacentes a un vertice y devuelve un
# adyacente al azar basado en los valores de los pesos
def vertice_aleatorio(pesos):
    #Pesos es un diccionario de pesos, clave vértice vecino, valor el peso.
    total = sum(pesos.values())
    rand = random.uniform(0, total)
    acum = 0
    for vertice, peso_arista in pesos.items():
        if acum + peso_arista >= rand:
            return vertice
        acum += peso_arista


# random walk para caso equiprobable
def random_equiprobable(grafo, v, largo, valor_prp, grados, trasmitido):
    if largo==0:
        return
     #este es el que inicia
    adyacente = random.choice(grafo.adyacentes(v)) #calculo el adyacente proximo
    trasmitido = trasmitido/grados[adyacente]
    valor_prp[adyacente] += trasmitido
    largo -= 1
    return random_equiprobable(grafo, adyacente, largo, valor_prp, grados, trasmitido)

# random walk para caso no equiprobable
def random_no_equiprobable(grafo, v, pesos, largo, apariciones, valor, grados):
    if largo==0:
        return
    for w in grafo.adyacentes(v):
        pesos[w] = grafo.peso_arista(v,w)

    adyacente = vertice_aleatorio(pesos)
    heredado = valor*grados[v]
    apariciones[adyacente] += heredado
    largo -= 1
    return random_no_equiprobable(grafo, adyacente, pesos, largo, apariciones, heredado, grados)
    
# recibe un grafo y un vertice de origen y realiza un recorrido aleatorio de tamaño largo
# entre adyacentes una cantidad de veces y dependiendo de si es equiprobable (booleano)
# la posibilidad de ir a un adyacente o depende del peso
def random_walks(grafo, origen, largo, cantidad, grados): 
    apariciones = {}
    #inicializo a todos los vertices en 1
    for v in grafo.obtener_vertices():
        apariciones[v] = 0

    for i in range(cantidad):
        random_equiprobable(grafo, origen, largo, apariciones, grados, VALOR_WALK_INICIAL)
    #elimino a origen de apariciones 
    apariciones.pop(origen)
    return apariciones

# Recibe una lista de diccionarios y una clave y devuelve la suma de los valores que todos
# los diccionarios guarden para esa clave
def sumatoria_diccionarios(diccionarios, clave):
    sumatoria = 0
    for dic in diccionarios:
        if clave not in dic:
            continue
        sumatoria += dic[clave]
    return sumatoria

# Recibe una lista de diccionarios con las mismas claves y una de claves y devuelve un diccionario 
# con la suma de los valores de cada diccionario para cada clave, si el valor era 0 no se guarda
def fusionar_diccionarios(diccionarios, claves):
    fusionado = {}
    for key in claves:
        sumatoria = sumatoria_diccionarios(diccionarios, key)
        if sumatoria==0:
            continue
        fusionado[key] = sumatoria
    
    return fusionado

# Recibe el grafo y una lista de vertices y devolvera una lista decreciente 
# con los vertices de mayor similitud a los pasados en la lista.
def PR_personalizado(grafo, vertices):
    grado = grados(grafo)

    lista_diccionarios = []
    for v in vertices:
        lista_diccionarios.append(random_walks(grafo, v, LARGO_WALKS, COEFICIENTE_CONVERGENCIA_1, grado))
    
    return lista_diccionarios
    



    #tiene como clave a los prp y como valor a los users o canciones
def fusionar_dicc(lista_de_dicc):
    fusionado = {}
    for dic in lista_de_dicc:
        for clave, valor in dic.items():
            if valor == 0:
              #saco los que no tengan nada que ver con las canciones
                continue
            fusionado[valor] = clave
    return fusionado
   
    # ordeno las claves del dic fusionado para que me de en principio los user o canciones con mas prp
def obtener_lista_maximos_valores_prp(diccionario):
    lista = list(diccionario.keys())
    lista.sort(reverse=True)
    return lista