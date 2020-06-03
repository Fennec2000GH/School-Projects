
import math

class Pakuri:
    """Model for a single Pakuri"""
    def __init__(self, name, species, level=0):
        """Constructor assigning name, species, and level"""
        self.Name = name
        self.Species = species
        self.Level = level
        self.__attack = 0
        self.__defense = 0
        self.__stamina = 0

    def name(self):
        """Get name of Pakuri"""
        return self.Name

    def species(self):
        """Get species of Pakuri"""
        return self.Species

    def level(self):
        """Gets level of Pakuri"""
        return self.Level

    def hp(self):
        """Calculates the Pakuri object’s health points (HP)"""
        return math.floor(self.__stamina * self.Level / 6)

    def cp(self):
        """Calculates the Pakuri object’s combat power (CP)"""
        return math.floor(self.__attack * math.sqrt(self.__defense) * math.sqrt(self.__stamina) * self.Level * 0.08)

