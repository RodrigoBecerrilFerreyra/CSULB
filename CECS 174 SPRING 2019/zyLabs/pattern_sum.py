def sumOfPattern(m, n):
    numstr = str(m)
    sumlst = []
    for i in range(1, n+1):
        sumlst.append(int(numstr * i))

    return sum(sumlst)
