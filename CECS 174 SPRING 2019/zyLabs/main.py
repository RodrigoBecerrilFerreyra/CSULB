class Mammal:
    def __init__(self, species):
        self.species = species
    def show_species(self):
        return "I am a " + self.species

class Dog(Mammal):
    def makesounds(self):
        return "Wolf wolf!"

class Cat(Mammal):
    def makesounds(self):
        return "Meow!"

#def main():
#    kitty = Cat("Cat")
#    doggy = Dog("Dog")

#    for i in [kitty, doggy]:
#        print(i.show_species())
#        print(i.makesounds())

#main()

print(".", end="")
