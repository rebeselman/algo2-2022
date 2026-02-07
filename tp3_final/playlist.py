import cancion
class Playlist:
    def __init__(self, nombre, id, creador):
        self.nombre = nombre
        self.id = id
        self.creador = creador
        self.canciones = [] #objetos canciones
    
    def agregar_cancion(self, cancion):
        if (cancion not in self.canciones): #ojo porque esto va a recorrer toda la lista de canciones siempre. se podría cambiar por un dicc para que sea o(1)
            self.canciones.append(cancion)

    def obtener_nombre(self):
        return self.nombre

    def obtener_id(self):
        return self.id
    
    def obtener_canciones(self):
        return self.canciones
    
    def obtener_nombre_creador(self):
        return self.creador
    
    
        

    