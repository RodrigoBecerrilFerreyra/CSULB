class Employee:
    def __init__(self):
        self._name = ""
        self._baseSalary = 0.0
    def setName(self, name):
        pass
    def setBaseSalary(self, newSalary):
        pass
    def getName(self):
        pass
    def getSalary(self):
        pass

class Manager(Employee):
    def __init__(self, bonus):
        super().__init__()
        self._bonus = bonus
        