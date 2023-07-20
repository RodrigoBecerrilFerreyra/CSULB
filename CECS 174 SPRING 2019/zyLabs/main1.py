# 7.22 Lab Ch7: Convert a Roman number to its decimal number presentation.

def convertDigit(u_char):
    RN = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D":500, "M": 1000}
    try:
        return RN[u_char]
    except KeyError:
        return 0

def romanToDecimal(u_string):

    # logic below
    """total = 0

  While the roman number string is not empty

         If value(first character) is at least value(second character), or the string has length 1    

                  Add value(first character) to total.
                  Remove the first character.

         Else
                  Add the difference, value(second character) - value(first character), to total.
                  Remove both characters."""
    total = 0

    while len(u_string) > 0:
        if (len(u_string) == 1) or (convertDigit(u_string[0]) >= convertDigit(u_string[1])):
            total += convertDigit(u_string[0])
            u_string = u_string[1:]
        else:
            total += (convertDigit(u_string[1]) - convertDigit(u_string[0]))
            u_string = u_string[2:]

    return total
