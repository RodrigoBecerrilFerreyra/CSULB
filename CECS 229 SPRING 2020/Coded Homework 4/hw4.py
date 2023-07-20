import math
#import image
#from numpy import arange

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

class Matrix:
    
    def __init__(self, rows=[[]]):

        for i in range(len(rows)):
            if len(rows[i]) != len(rows[i-1]):
                raise ValueError("All rows must be of equal length.")

        self.Rowsp = rows
        self.dim = {'m': len(self.Rowsp), 'n': len(self.Rowsp[0])} #mxn matrix
        self.calcColSp()
    
    def calcColSp(self):
        self.Colsp = []
        column = []
        for j in range(self.dim['n']):
            for i in range(self.dim['m']):
                column.append(self.Rowsp[i][j])
            self.Colsp.append(column)
            column = []
    
    def __str__(self):
        returnstr = ""
        maxval = len(str(self.max_val()))
        minval = len(str(self.min_val()))
        length = max([maxval, minval])

        for row in self.Rowsp:
            for entry in row:
                returnstr += (str(entry).zfill(length) + " ")
            returnstr += "\n"
        return returnstr
    
    def max_val(self):
        max_in_row = [max(row) for row in self.Rowsp]
        return max(max_in_row)
    def min_val(self):
        min_in_row = [min(row) for row in self.Rowsp]
        return min(min_in_row)
    
    def setRow(self, row, newrow):
        """Replaces row row with newrow."""

        if len(newrow) != len(self.Rowsp[0]):
            raise ValueError("Incompatible row length.")

        self.Rowsp[row - 1] = newrow
        self.calcColSp()
    
    def setCol(self, col, newcol):
        """Replaces column col with newcol."""

        if len(newcol) != len(self.Rowsp):
            raise ValueError("Incompatible column length.")

        for i in range(len(self.Rowsp)):
            self.Rowsp[i][col - 1] = newcol[i]
        self.calcColSp()
    
    def setEntry(self, i, j, value):
        """Replaces entry of row i column j with value."""
        self.Rowsp[i - 1][j - 1] = value
        self.calcColSp()
    

    def getRow(self, row):
        """Returns the row-th row."""
        return self.Rowsp[row - 1]

    def getCol(self, col):
        """Returns the col-th column."""
        retcol = []
        for row in self.Rowsp:
            retcol.append(row[col - 1])
        return retcol
    
    def getEntry(self, i, j):
        """Returns the entry in row i column j."""
        return self.Rowsp[i - 1][j - 1]
    
    def getRowSpace(self):
        """Returns the row space."""
        return self.Rowsp
    def getColSpace(self):
        """Returns the column space."""
        return self.Colsp
    
    def getdiag(self, k):
        """Returns the diagonal of self with offset k."""
        row = 0; column = 0

        if k > 0: column += k
        elif k < 0: row += -k

        diag = []
        while True:
            try:
                diag.append(self.Rowsp[row][column])
                row += 1; column += 1
            except IndexError:
                break
        return diag
    
    def __add__(self, other):
        if type(other) != Matrix or self.dim != other.dim:
            raise ValueError("Addition is only defined for matrices of the same dimensions.")

        m = self.dim['m']; n = self.dim['n']

        newMatrix = Matrix([[0 for col in range(n)] for row in range(m)])
        for x in range(m):
            for y in range(n):
                newMatrix.setEntry(x + 1, y + 1, self.getEntry(x + 1, y + 1) + other.getEntry(x + 1, y + 1))
        return newMatrix
    
    def __mul__(self, other):
        if type(other) == int or type(other) == float: #Multiplying by a scalar
            newMatrix = Matrix([[1 for col in range(self.dim['n'])] for row in range(self.dim['m'])])
            for x in range(self.dim['m']):
                for y in range(self.dim['n']):
                    newMatrix.setEntry(x + 1, y + 1, self.getEntry(x + 1, y + 1) * other)

        elif type(other) == Matrix: #Multiplying by a matrix
            if self.dim['n'] != other.dim['m']:
                raise ValueError("Matrix multiplication is only defined for matrices whose inner dimension is equal.")
            
            newMatrix = Matrix([[0 for col in range(other.dim['n'])] for row in range(self.dim['m'])]) #mxp * pxn = mxn
            for r, row in enumerate(self.getRowSpace()):
                for c, col in enumerate(other.getColSpace()):
                    newMatrix.setEntry(r + 1, c + 1, Vec(row) * Vec(col))
        
        elif type(other) == Vec: #Multiplying by a row/column vector
            if self.dim['n'] == 1: #row vector

                newMatrix = Matrix([[0 for col in range(len(other))] for row in range(self.dim['m'])]) #mx1 * 1xl = mxl
                for r, row in enumerate(self.getRowSpace()):
                    for c, col in enumerate(other):
                        newMatrix.setEntry(r + 1, c + 1, Vec(row) * Vec([col]))
            
            elif self.dim['n'] == len(other): #column vector
                
                newMatrix = Matrix([[0] for row in range(self.dim['m'])]) #mxl * lx1 = mx1
                for r, row in enumerate(self.getRowSpace()):
                    newMatrix.setEntry(r + 1, 1, Vec(row) * other)

            else:
                raise ValueError("Matrix multiplication is only defined for matrices whose inner dimension is equal.")
        else:
            raise TypeError("Error: Unsupported type.")
        
        return newMatrix

    def __rmul__(self, other):
        if type(other) == int or type(other) == float: #Multiplying by a scalar
        #     newMatrix = Matrix([[1 for col in range(self.dim['n'])] for row in range(self.dim['m'])])
        #     for x in range(self.dim['m']):
        #         for y in range(self.dim['n']):
        #             newMatrix.setEntry(x + 1, y + 1, self.getEntry(x + 1, y + 1) * other)
        # return newMatrix
            return self.__mul__(other)

    def __sub__(self, other):
        return self.__add__(other*-1)

def png2graymatrix(filename):
    """
    takes a png file and returns a Matrix object of the pixels 
    INPUT: filename - the path and filename of the png file
    OUTPUT: a Matrix object with dimensions m x n, assuming the png file has width = n and height = m, 
    """
    data = image.color2gray(image.file2image(filename))
    return Matrix(data)
def graymatrix2png(matrix, path):
    """
    returns a png file created using the Matrix object, img_matrix
    INPUT: 
        * img_matrix - a Matrix object where img_matrix[i][j] is the intensity of the (i,j) pixel
        * path - the location and name under which to save the created png file 
    OUTPUT: 
        * a png file
    """
    image.image2file(matrix.getRowSpace(), path)
