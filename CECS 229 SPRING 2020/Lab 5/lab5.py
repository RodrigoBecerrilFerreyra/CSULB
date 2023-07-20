import math
def translate(S, z0):
    """
    translates the complex numbers of set S by z0
    INPUT: 
        * S - set of complex numbers
        * z0 - complex number
    OUT:
        * T - set consisting of points in S translated by z0
    """
    T = []
    for z in S:
        T.append(z0 + z)
    return set(T)

def scale(S, k):
    """
    scales the complex numbers of set S by k.  
    INPUT: 
        * S - set of complex numbers
        * k - positive float, raises ValueError if k <= 0
    OUT:
        * T - set consisting of points in S scaled by k
        
    """
    if k <= 0:
        raise ValueError("ERROR: Scaling factor must be a positive float")
    
    T = []
    for z in S:
        T.append(z*k)
    return set(T)

def rotate(S, theta):
    """
    rotates the complex numbers of set S by theta radians.  
    INPUT: 
        * S - set of complex numbers
        * theta - float. If negative, the rotation is clockwise. If positive the rotation is counterclockwise. If zero, no rotation.
    OUT:
        * T - set consisting of points in S rotated by theta radians
        
    """
    T = []
    for z in S:
        mag = math.hypot(z.imag, z.real)
        arg = math.atan2(z.imag, z.real) + theta
        T.append(mag * math.cos(arg) + mag * math.sin(arg)*1j) #Euler's formula
    return set(T)
