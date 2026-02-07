import random

class Grafo:
    def __init__(self, dirigido = False):
        self.dirigido = dirigido
        self.grafo = {}
        self.cantidad = 0
    
    def vertice_en_grafo(self, vertice):
        if (vertice not in self.grafo):
            return False
        return True

    def cantidad_vertices(self):
        return self.cantidad

    def agregar_vertice(self, vertice):
        if vertice in self.grafo:
            raise Exception("Ese vertice ya existe")
        self.grafo[vertice] = {}
        self.cantidad += 1
        
    def estan_unidos(self, vertice_1, vertice_2):
        if vertice_1 not in self.grafo or vertice_2 not in self.grafo:
            raise Exception("Uno de los vertices no es valido")
      
        if vertice_2 in self.grafo[vertice_1]:
            return True
        return False

    def peso_arista(self, vertice_1, vertice_2):
        if vertice_1 not in self.grafo or vertice_2 not in self.grafo:
            raise Exception("Uno de los vertices no es valido")
        if not self.estan_unidos(vertice_1, vertice_2):
            raise Exception("El vertice_1 no tiene como adyacente al vertice_2")
        return self.grafo[vertice_1][vertice_2]

    def obtener_vertices(self):
        vertices = []
        for vertice in self.grafo:
            vertices.append(vertice)
        return vertices

    def vertice_aleatorio(self):
        return random.choice(list(self.grafo.keys()))

    def adyacentes(self, vertice):
        if vertice not in self.grafo:
            raise Exception("Vertice no valido")
        adyacentes = []
        for adyacente in self.grafo[vertice]:
            adyacentes.append(adyacente)
        return adyacentes
     
                
    def borrar_vertice(self, vertice):
        if not vertice in self.grafo:
            print(vertice)
            raise Exception("Vertice no valido")
        
        # Itero los vertices del grafo para borrar a vertice de los adyacentes de otros vertices.
        for v in self.grafo:
            if vertice in self.grafo[v]:
                self.grafo[v].pop(vertice)


    def agregar_arista(self, vertice_1, vertice_2, peso = 1):
        if not self.estan_unidos(vertice_1, vertice_2):
            self.grafo[vertice_1][vertice_2] = peso
            if not self.dirigido:
                self.grafo[vertice_2][vertice_1] = peso


    def borrar_arista(self, vertice_1, vertice_2):
        if self.estan_unidos(vertice_1, vertice_2):
            self.grafo[vertice_1].pop(vertice_2)
            if self.dirigido:
                self.grafo[vertice_2].pop(vertice_1)
    
    