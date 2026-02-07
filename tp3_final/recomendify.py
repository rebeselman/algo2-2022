
import biblioteca 
import readline
from main import CANTIDAD_DE_ARGUMENTOS_VALIDOS_1
from usuario import Usuario
from cancion import Cancion
from grafo import Grafo
from playlist import Playlist

SEPARADOR_CANCIONES_2 = "-->"
SEPARADOR_CANCIONES_3 = ";"



class Recomendify:
    def __init__(self):
        self.usuarios = {} # 'nombre_usuario' : Usuario 
        self.canciones = {} #'track - artist' : Cancion
        self.playlists = {} # 'id_playlist' : Playlist
        self.grafo_bipartito = None
        self.grafo_no_bipartito = None
        self.page_rank = None
        self.page_rank_cantidad = 0
        self.indices_page_rank = []


    def procesar_archivo(self, archivo):
        grafo_bipartito = Grafo(False)
        with open(archivo, 'r') as texto:
            #texto.readline()
            for linea in texto:
                id, user_id, track_name, artist, playlist_id, playlist_name, genres = linea.strip().split("\t")
                # se crea la cancion si no existe y se la agrega a la base de datos
                titulo = f'{track_name} - {artist}' # esto es porque pueden existir canciones de un mismo nombre de != artistas
                if (titulo not in self.canciones):
                    cancion_nueva = Cancion(track_name, artist, genres, titulo)
                    self.canciones[titulo] = cancion_nueva
                    grafo_bipartito.agregar_vertice(cancion_nueva)
                # se crea la playlist si no existe en la base de datos y se lo agrega
                if (playlist_id not in self.playlists):
                    playlist_nueva = Playlist(playlist_name, playlist_id, user_id)
                    self.playlists[playlist_id] = playlist_nueva

                playlist_leida = self.playlists[playlist_id] # ahora que existe la obtengo
                playlist_leida.agregar_cancion(self.canciones[titulo])

                # Se crea el usuario si no existe en la base de datos y se lo agrega
                if (user_id not in self.usuarios):
                    usuario_nuevo = Usuario(user_id)
                    self.usuarios[user_id] = usuario_nuevo
                    grafo_bipartito.agregar_vertice(usuario_nuevo)

                usuario_leido = self.usuarios[user_id] 
                usuario_leido.agregar_nueva_playlist(playlist_leida) #esto no agrega nada si la playlist ya existe entre las del user
                # grafo bipartito
                if (not grafo_bipartito.estan_unidos(usuario_leido, self.canciones[titulo])):
                    grafo_bipartito.agregar_arista(usuario_leido, self.canciones[titulo], playlist_id)

        self.grafo_bipartito = grafo_bipartito

        #if (len(self.canciones) + len(self.usuarios) != grafo_bipartito.cantidad_vertices()):
        #    print("error")
        #for cancion in self.canciones:
        #    if (not self.grafo_bipartito.vertice_en_grafo(self.canciones[cancion])):
        #        print(f"{cancion} no esta en el grafo bipartito")
        #print("todo ok")

        #for usuario in self.usuarios:
        #    if (not self.grafo_bipartito.vertice_en_grafo(self.usuarios[usuario])):
        #        print(f"{usuario} no esta")
        #print("todo ok")

        #for playlist in self.playlists:
        #    user_id = self.playlists[playlist].obtener_nombre_creador()
        #    for cancion in self.playlists[playlist].obtener_canciones():
        #        if (not self.grafo_bipartito.estan_unidos(self.canciones[cancion.obtener_titulo()], self.usuarios[user_id])):
        #            print("grafo mal construido")
        #            return
        #print("todo ok")
        
        for v in grafo_bipartito.obtener_vertices():
            if (type(v) == Usuario):
                print(v.obtener_nombre(), "le gustan estas canciones :")
                for w in grafo_bipartito.adyacentes(v):
                    print(w.obtener_titulo())
                

        #                return
        #print("todo ok")         
        return True

    def cancion_valida(self, titulo):
        return titulo in self.canciones

    #def chequeo_grafo_no_bipartito(self):
    #    for usuario in self.usuarios:
    #        for playlist in self.usuarios[usuario].obtener_playlist():
    #            for cancion in playlist.obtener_canciones():
    #                for playlist1 in self.usuarios[usuario].obtener_playlist():
    #                    for cancion1 in playlist1.obtener_canciones():
    #                        if (cancion != cancion1 and not self.grafo_no_bipartito.estan_unidos(cancion, cancion1)):
    #                            print("mal contruido")
                                





    def camino(self, origen, destino):
        mas_corto_camino = biblioteca.camino_mas_corto(self.grafo_bipartito, self.canciones[origen], self.canciones[destino])
        if (mas_corto_camino==None):
            print("No se encontro recorrido")
            return
        for i in range(len(mas_corto_camino) -1):
            vertice = mas_corto_camino[i]
            vertice_proximo = mas_corto_camino[i+1]
            if (type(vertice) == Cancion):
                id_playlist = self.grafo_bipartito.peso_arista(vertice, vertice_proximo)
                print(f"{vertice.obtener_titulo()} --> aparece en playlist --> {self.playlists[id_playlist].obtener_nombre()} --> de --> ", end = "")
            else:
                id_playlist = self.grafo_bipartito.peso_arista(vertice, vertice_proximo)
                print(f"{vertice.obtener_nombre()} --> tiene una playlist --> {self.playlists[id_playlist].obtener_nombre()} --> donde aparece --> ", end = "")                  
        print(f"{self.canciones[destino].obtener_titulo()}")

    def crear_grafo_no_bipartito(self):
        grafo_no_bipartito = Grafo(False)
        # agrego todos las canciones al grafo
        for cancion in self.canciones:
            grafo_no_bipartito.agregar_vertice(self.canciones[cancion])

        #tamanio = grafo_no_bipartito.cantidad_vertices()
        #chequeo
        #if (len(self.canciones) != tamanio): print("el grafo esta mal hecho :(")


        #for usuario in self.usuarios:
        #    for playlist1 in self.usuarios[usuario].obtener_playlist():
        #        for cancion in  playlist1.obtener_canciones():
        #            for playlist2 in self.usuarios[usuario].obtener_playlist():
        #                for cancion2 in playlist2.obtener_canciones():
        #                    if (cancion != cancion2 and not grafo_no_bipartito.estan_unidos(cancion, cancion2)):
        #                        grafo_no_bipartito.agregar_arista(cancion, cancion2)
        for v in self.grafo_bipartito.obtener_vertices():
            if (type(v) == Cancion):
                for w in self.grafo_bipartito.adyacentes(v):
                    #mis adyacentes son usuarios 
                    for playlist in w.obtener_playlist():
                        for cancion in playlist.obtener_canciones():
                            if (v.obtener_titulo() != cancion.obtener_titulo() and  not grafo_no_bipartito.estan_unidos(v, cancion)):
                                grafo_no_bipartito.agregar_arista(v, cancion)
                    
        for v in grafo_no_bipartito.obtener_vertices():
            print(v.obtener_titulo(), "es adyacente a")
            for w in grafo_no_bipartito.adyacentes(v):
                print(w.obtener_titulo())
            

        self.grafo_no_bipartito = grafo_no_bipartito 

        #self.chequeo_grafo_no_bipartito()

                 
    def crear_page_rank(self):
        page_rank_ = biblioteca.page_rank(self.grafo_bipartito)
        page_rank = biblioteca.fusionar_dicc([page_rank_])
        self.page_rank_cantidad = len(page_rank)
        lista_indices = biblioteca.obtener_lista_maximos_valores_prp(page_rank)
        self.indices_page_rank = lista_indices
        self.page_rank = page_rank
    
    # Nos muestra las n canciones más importantes o centrales del mundo según 
    # el algoritmo de PageRank
    def mas_importantes(self, n):
        if (not self.page_rank):
            self.crear_page_rank()
        c = n
        for i in range(self.page_rank_cantidad):
            if (c == 0):
                break
            elif type(self.page_rank[self.indices_page_rank[i]]) == Usuario:
                continue
            elif c==1:
                print(f"{self.page_rank[self.indices_page_rank[i]].obtener_titulo()}")
                c-=1
            else:
                print(f"{self.page_rank[self.indices_page_rank[i]].obtener_titulo()}; ", end ="")
                c -= 1


    def recomendacion(self, usuarios_o_canciones, n, lista):
        gustadas = set()
        for cancion in lista:
            gustadas.add(self.canciones[cancion])
        song = None
        if (usuarios_o_canciones == "usuarios"):
            song =  False
        else: song = True

        prp = biblioteca.PR_personalizado(self.grafo_bipartito, gustadas)
        rank = biblioteca.fusionar_dicc(prp)
        lista_prp = biblioteca.obtener_lista_maximos_valores_prp(rank)
        len_prp = len(lista_prp)
        u_c_ya_recomendados = set()
        c = n
        for i in range(len_prp):
            
            if c == 0:
                break
            elif rank[lista_prp[i]] in gustadas or rank[lista_prp[i]] in u_c_ya_recomendados:
                continue
            elif not song and type(rank[lista_prp[i]]) == Usuario:
                if c==1:
                    print(f"{rank[lista_prp[i]].obtener_nombre()}")
                else:
                    print(f"{rank[lista_prp[i]].obtener_nombre()}; ", end ="")
                    u_c_ya_recomendados.add(rank[lista_prp[i]])
                c -= 1 
            elif song and type(rank[lista_prp[i]]) == Cancion:
                if c==1:
                    print(f"{rank[lista_prp[i]].obtener_titulo()}")
                    
                else:
                    print(f"{rank[lista_prp[i]].obtener_titulo()}; ", end ="")
                    u_c_ya_recomendados.add(rank[lista_prp[i]])
                c -=1  
    
    

    # Imprime un ciclo de largo n que comience en la canción indicada.
    # Complejidad: O(C**n)
    def ciclo(self, n, cancion):
        if (self.grafo_no_bipartito==None):
            self.crear_grafo_no_bipartito()
        ciclos = biblioteca.ciclos_n(self.grafo_no_bipartito, self.canciones[cancion], n)
        if (ciclos==None): 
            print("No se encontro recorrido")
            return 
        for i in range(n):
            print(f"{ciclos[i].obtener_titulo()} --> ", end = "")
        print(f"{ciclos[n].obtener_titulo()}")
            

    # Imprime la cantidad de canciones que se encuentren a n saltos desde la cancion
    # pasada por parámetro. 
    # Complejidad: 0(C + L)
    def rango(self, n, cancion):

        #print("todo ok")
        if (self.grafo_no_bipartito==None):
            self.crear_grafo_no_bipartito()
        #if (self.prueba_grafo_no_bipartito == 0 and self.grafo_bipartito):
        #    self.chequeo_grafo_no_bipartito()
        #    self.prueba_grafo_no_bipartito = 1

        print(f"{biblioteca.rango_n(self.grafo_no_bipartito, self.canciones[cancion], n)}")
        
