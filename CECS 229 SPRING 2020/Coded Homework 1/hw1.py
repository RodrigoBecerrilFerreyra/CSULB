def gcd(a, b):
    mod = a % b
    if mod == 0:
        return min(a, b)
    else:
        return gcd(b, mod)

def binaryExpansion(b, n):
    """Returns a list containing the powers of powers of 2 of b."""
    binExp = reversed([int(i) for i in bin(round(n))[2:]]) #binary expansion of n
    decExp = []
    for index, value in enumerate(binExp):
        decExp.append(b ** (value * 2**index)) #example: 3^11 = 3^(1*2^3) * 3^(0*2^2) * 3^(1*2^1) * 3^(1*2^0) = 177147
    return sorted(decExp)

def modExp(b=1, n=1, m=1, list_=None):
    array = binaryExpansion(b, n) if not list_ else list_

    # base case
    if len(array) == 1:
        return array[0] % m
    
    # recursive case
    first_mod = array[-1] % m
    second_mod = modExp(m=m, list_=array[:-1])
    return (first_mod * second_mod) % m #corollary

# This is not giving expected result for bezoutCoeffs(414, 662)
#def bezoutCoeffs(a, b):
#    og = {"a": a, "b": b}
#    s = [1, -(b // a)]
#    t = [0, 1]
#    r = b % a
#
#    if r == 0: return (s[0], t[0])
#
#    gcd_ = gcd(a, b)
#    i = 2
#    while r != gcd_:
#        s.append(s[i-2] - (s[i-1] * (b // a)))
#        t.append(t[i-2] - (t[i-1] * (b // a)))
#
#        r = b % a
#        b = a
#        a = r
#        i +=1
#    
#    if (og['a'] * s[-1] + og['b'] * t[-1] == gcd_):
#        result = (s[-1], t[-1])
#    elif (og['a'] * t[-1] + og['b'] * s[-1] == gcd_):
#        result = (t[-1], s[-1])
#
#    return result

def bezoutCoeffs(a, b): #taken from https://www.dcode.fr/bezout-identity
    r = [a, b]
    s = [1, 0]
    t = [0, 1]
    
    while r[1] != 0:
        div = r[0] // r[1]
        rs = r[0]; ss = s[0]; ts = t[0]
        r[0] = r[1]; s[0] = s[1]; t[0] = t[1]
        r[1] = rs - div*r[1]; s[1] = ss - div*s[1]; t[1] = ts - div*t[1]
    
    return (s[0], t[0])

print(modExp(b=1415, n=13, m=2537))
