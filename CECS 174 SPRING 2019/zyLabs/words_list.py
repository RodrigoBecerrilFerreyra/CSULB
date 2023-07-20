# Custom printing for use in lab
def print_list(lst):
    print("The following words are not in the 100 most common word list:")
    for i in lst:
        print(i)

# Get 100 most common words from file and store in var
with open(r"100-most-common-words.txt", 'r') as infile:
    COMMON_WORDS = infile.read().split("\n")[:-1]

# File name input error handling
filename = input("Enter the input file name:\n")
try:
    infile = open(filename, 'r')

    badwords = []

    # Reads file line by line
    for line in infile:
        words_in_line = line.strip().rstrip(",?!").lower().split() #parsing
        # Reads word by word in line
        for i in words_in_line:
            if i not in COMMON_WORDS:
                badwords.append(i)

    print_list(badwords)

except FileNotFoundError as e:
    print("ERR: File Not Found", str(e))
finally:
    infile.close()
