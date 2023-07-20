def testForAnagram(str1, str2):

    lst1 = [i for i in str1] #can't use strings, immutable
    lst2 = [i for i in str2]

    if len(lst1) != len(lst2): #can't be anagram if different length
        return "Different words"

    while len(lst1) > 0:
        if lst1[0] not in lst2:
            return "Different words"
        del lst2[lst2.index(lst1[0])]
        del lst1[0]

    return "Anagram"

def main():
    print(testForAnagram("dusty", "study"))

main()
