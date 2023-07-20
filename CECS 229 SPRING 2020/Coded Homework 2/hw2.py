def digits2letters(digits):
    """converts a string of double digits without spaces in the range 00-25 to a string of letters A-Z"""
    letter2digit = {"A" : "00", "B" : "01", "C" : "02", "D" : "03", "E" : "04", 
                  "F" : "05", "G" : "06", "H" : "07", "I" : "08", "J" : "09",
                  "K" : "10", "L" : "11", "M" : "12", "N" : "13", "O" : "14",  
                  "P" : "15", "Q" : "16", "R" : "17", "S" : "18", "T" : "19",
                  "U" : "20", "V" : "21", "W" : "22", "X" : "23", "Y" : "24", 
                  "Z" : "25"}
        
    digit2letter = dict((v,k) for k,v in letter2digit.items())  #creating a dictionary with keys and values exchanged
        
    letters = ""
    start = 0  #initializing starting index of first digit
    for i in range(0, len(digits), 2):
        digit = digits[start : start + 2]  # accessing the double digit
        letters += digit2letter[digit]     # concatenating to the string of letters
        start += 2                         # updating the starting index for next digit
    
    return letters

def letters2digits(letters):
    """converts a string of letters A-Z to a string of double digits without spaces in the range 00-25"""
    letter2digit = {"A" : "00", "B" : "01", "C" : "02", "D" : "03", "E" : "04", 
                  "F" : "05", "G" : "06", "H" : "07", "I" : "08", "J" : "09",
                  "K" : "10", "L" : "11", "M" : "12", "N" : "13", "O" : "14",  
                  "P" : "15", "Q" : "16", "R" : "17", "S" : "18", "T" : "19",
                  "U" : "20", "V" : "21", "W" : "22", "X" : "23", "Y" : "24", 
                  "Z" : "25"}
        
    digits = ""  #initializing digits string
    letters = "".join(letters.split()) #removing whitespaces in the text

    
    for i in range(0, len(letters)):
        if(letters[i].isalpha()):
            letter = letters[i].upper()  #converting to uppercase
            digit = letter2digit[letter]
            digits += digit     # concatenating to the string of digits
    
    return digits

def blocksize(n):
    """returns the size of a block in an RSA encrypted string"""
    twofive = "25"
    while int(twofive) < n:
        twofive += "25"
    return len(twofive) - 2

def modinv(a,m,gcd = False):
    """returns the inverse of a modulo m
    INPUT: a - integer
           m - positive integer
           gcd - if True then return the greatest common divisor of a and m instead
    OUTPUT: a inverse as an integer
    """
    r = [a, m]
    s = [1, 0]
    t = [0, 1]
    
    while r[1] != 0:
        div = r[0] // r[1]
        rs = r[0]; ss = s[0]; ts = t[0]
        r[0] = r[1]; s[0] = s[1]; t[0] = t[1]
        r[1] = rs - div*r[1]; s[1] = ss - div*s[1]; t[1] = ts - div*t[1]
    
    if not gcd:
        if r[0] != 1: raise ValueError("The given values are not relatively prime")
        return s[0] if s[0] >= 0 else s[0] + m
    else:
        return r[0]

def affineEncrypt(text, a, b):
    """encrypts the plaintext 'text', using an affine transformation key (a, b)
    INPUT:  text - plaintext as a string of letters
            a - integer satisfying gcd(a, 26) = 1.  Raises error if such is not the case
            b - integer 
            
    OUTPUT: The encrypted message as a string of characters
    """
    if modinv(a, 26, True) != 1: raise ValueError("The given key is invalid. The gcd(a,26) must be 1.")

    # Turn letters to numbers
    as_numbers = [int(letters2digits(i)) for i in text.replace(" ", "")]

    # Encryption formula
    encrypted = [(a * x + b) % 26 for x in as_numbers]

    # Join list and return
    encrypted_letters = []
    for i in encrypted:
        encrypted_letters.append(
            digits2letters(
                str(i) if i >= 10 else "0" + str(i)
                )
            ) #[digits2letters(str(i).zfill(2)) for i in encrypted]
            # Not sure if I'm allowed to use zfill so I'll play it safe.
    return "".join(encrypted_letters)

def affineDecrypt(ciphertext, a, b):
    """decrypts the string 'ciphertext', which was encrypted using an affine transformation key (a, b)
    INPUT:  ciphertext - a string of encrypted letters
            a - integer satisfying gcd(a, 26) = 1.  
            b - integer 
            
    OUTPUT: The decrypted message as a string of characters
    """
    if modinv(a, 26, True) != 1: raise ValueError("The given key is invalid. The gcd(a,26) must be 1.")

    a_bar = modinv(a, 26)

    # Turn letters to numbers
    as_numbers = [int(letters2digits(i)) for i in ciphertext.replace(" ", "")]

    # Decryption formula
    decrypted = [a_bar * (x - b) % 26 for x in as_numbers]

    # Join list and return
    decrypted_letters = []
    for i in decrypted:
        decrypted_letters.append(
            digits2letters(
                str(i) if i >= 10 else "0" + str(i)
            )
        ) #[digits2letters(str(i).zfill(2)) for i in decrypted]
        # Not sure if I'm allowed to use zfill so I'll play it safe.
    return "".join(decrypted_letters)

def encryptRSA(m, p, q, e):
    """encrypts the plaintext m, using RSA and the key (p * q, e)
    INPUT:  m - plaintext as a string of letters
            p, q - prime numbers used as part of the key n = p * q to encrypt the ciphertext
            e - integer satisfying gcd((p-1)*(q-1), e) = 1
            
    OUTPUT: The encrypted message as a string of digits
    """
    
    # Initialization of variables
    n = p * q
    size = blocksize(n)
    m = m.replace(" ", "")

    # Letters to numbers
    numbers = "".join([letters2digits(char) for char in m])

    # Separating into blocks of size size
    separated = []
    for i in range(1, len(numbers) + 1):
        if i % size == 0: separated.append(numbers[i - size : i])
        elif i == len(numbers): separated.append(numbers[i - i%size:])
    
    # Padding for last block
    while len(separated[-1]) != size:
        separated[-1] += "23"

    # Encryption algorithm
    encrypted = [str((int(m) ** e) % n) for m in separated]

    # Left zero padding for all blocks
    for i in range(len(encrypted)):
        while len(encrypted[i]) != size:
            encrypted[i] = "0" + encrypted[i]

    return " ".join(encrypted)

def decryptRSA(c, p, q, e):
    """decrypts the cipher c, which was encrypted using the key (p * q, e)
    INPUT:  c - ciphertext as a string of digits
            p, q - prime numbers used as part of the key n = p * q to encrypt the ciphertext
            e - integer satisfying gcd((p-1)*(q-1), e) = 1
            
    OUTPUT: The decrypted message as a string of letters
    """
    # Initialization of variables
    n = p * q
    e_bar = modinv(e, (p - 1) * (q - 1))
    separated = c.split(" ")
    size = blocksize(n)

    # Decryption function
    decrypted = [str((int(ci) ** e_bar) % n) for ci in separated]
    # Left padding with 0
    for i in range(len(decrypted)):
        while len(decrypted[i]) != size:
            decrypted[i] = "0" + decrypted[i]
    decrypted_str = "".join(decrypted)
    
    # Join string and return
    decrypted_letters = [digits2letters(decrypted_str[i:i + 2]) for i in range(0, len(decrypted_str) + 1, 2)]
    return "".join(decrypted_letters)
