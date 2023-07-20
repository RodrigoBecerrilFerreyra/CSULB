def image2complex(img_name):
    """
    IN: img_name - the name of the image to read
    OUT: set of complex numbers x+yi where the intensity of pixel (x,y) is greater than 120
    """
    import image
    
    # data is a list of lists such that the intensity of pixel (x,y) is given by data[h-1-y][x]
    # where h = height of the image
    T = []
    data = image.color2gray(image.file2image("img01.png"))
    for y in range(0, -len(data), -1): #Had to do something weird here due to the -y in the formula
        for x in range(len(data[0])):
            if data[y][x] < 120: T.append(x-y*1j)
    return set(T)

def reflectV(S, h):
    """
    reflects the complex numbers of set S about the vertical line x = h.  
    INPUT: 
        * S - set of complex numbers
        * h - float
    OUT:
        * set consisting of points in S reflected about the line x = h.
        
    """
    T = []
    for z in S:
        T.append((2*h - z.real) + z.imag*1j)
    return set(T)

def reflectH(S, k):
    """
    reflects the complex numbers of set S about the horizontal line y = k.  
    INPUT: 
        * S - set of complex numbers
        * k - float
    OUT:
        * set consisting of points in S reflected about the line y = k.
        
    """
    T = []
    for z in S:
        T.append(z.real + (2*k - z.imag)*1j)
    return set(T)