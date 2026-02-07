class Cancion:
    def __init__(self, nombre, artista, generos, titulo):
        self.nombre = nombre
        self.artista = artista
        self.generos = generos
        self.titulo = titulo
    
    def obtener_nombre(self):
        """Devuelve el nombre de la canción"""
        return self.nombre
    
    def obtener_artista(self):
        """Devuelve el nombre del cantante de la canción"""
        return self.artista

    def obtener_generos(self):
        """Devuelve los géneros a los que pertenece la canción"""
        return self.generos

    def obtener_titulo(self):
        return self.titulo