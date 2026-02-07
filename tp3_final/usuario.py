import playlist

class Usuario:
    def __init__(self, nombre):
        self.nombre = nombre
        self.playlists = [] #lista de objetos playlists
        self.playlists_cantidad = 0
      

    def obtener_nombre(self):
        return self.nombre


    def cantidad_de_playlists(self):
        # Esto es para obtener la cantidad en O(1)
        return self.cantidad_de_playlists
    
    def agregar_nueva_playlist(self, playlist):
        if(playlist not in self.playlists): #ojo porque recorre toda la lista cada vez que agrega
            self.playlists.append(playlist)
            self.playlists_cantidad += 1
        
    
    def obtener_playlist(self):
        return self.playlists




    

    


