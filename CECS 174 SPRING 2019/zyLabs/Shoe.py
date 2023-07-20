class Shoe:
    def __init__(self, color, size):
        self.color = color
        self.size = size
    def getType(self):
        return "shoes"
    def describe(self):
        return "{color} {type}: size {size}".format(color=self.color, type=self.getType(), size=self.size)

class Boots(Shoe):
    def __init__(self, color, size, height):
        super().__init__(color, size)
        self.height = height
    def getType(self):
        return "boots"
    def describe(self):
        return super().describe() + ", height " + str(self.height)
class Sneakers(Boots):
    def __init__(self, color, size, height, lace_color):
        super().__init__(color, size, height)
        self.lace_color = lace_color
    def getType(self):
        return "sneakers"
    def describe(self):
        return super().describe() + ", lace color " + self.lace_color

print(".", end="")
