from math import pi

class SodaCan:
    def setHeight(self, x):
        self.height = x
    def setRadius(self, x):
        self.radius = x
    
    def getSurfaceArea(self):
        return (2 * pi * self.radius) * (self.radius + self.height)
    def getVolume(self):
        return pi * (self.radius ** 2) * self.height
