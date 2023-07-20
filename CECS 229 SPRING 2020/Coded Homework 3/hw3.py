import math
class Vec:
    def __init__(self, contents = []):
        """constructor defaults to empty vector
           accepts list of elements to initialize a vector object with the 
           given list
        """
        self.elements = contents
        return
    
    def __len__(self):
        return len(self.elements)
    
    def __getitem__(self, key):
        if key >= len(self) or key < -len(self):
            raise IndexError("Index is out of range.")
        if key < 0:
            key += len(self)
        return self.elements[key]
    
    def __abs__(self):
        """Overloads the built-in function abs(v)
            returns the Euclidean norm of vector v
        """
        return math.sqrt(sum([i**2 for i in self.elements]))
        
    def __add__(self, other):
        """Overloads the + operation to support Vec + Vec
         raises ValueError if vectors are not same length
        """
        if type(other) != Vec or len(other) != len(self):
            raise ValueError("Addition is only defined for vectors of the same length.")
        
        newvec = []
        for i in range(len(self)):
            newvec.append(self[i] + other[i])
        
        return Vec(newvec)
    
    
    def __mul__(self, other):
        """Overloads the * operator to support 
            - Vec * Vec (dot product) raises ValueError if vectors are not same length in the case of dot product
            - Vec * float (component-wise product)
            - Vec * int (component-wise product)
            
        """
        if type(other) == Vec: #define dot product
            if len(other) != len(self):
                raise ValueError("The dot product is only defined for vectors of the same length.")
            sum_ = 0
            for i in range(len(self)):
                sum_ += self[i] * other[i]
            return sum_
            
        elif type(other) == float or type(other) == int: #scalar-vector multiplication
            return Vec([i*other for i in self])
            
    
    def __rmul__(self, other):
        """Overloads the * operation to support 
            - float * Vec
            - int * Vec
        """
        return self.__mul__(other)
    
    def __str__(self):
        """returns string representation of this Vec object"""
        return str(self.elements) # does NOT need further implementation
    
    def __sub__(self, other):
        return self.__add__(-1*other)