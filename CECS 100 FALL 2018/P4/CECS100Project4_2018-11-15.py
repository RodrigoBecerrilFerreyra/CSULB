# CECS 100 Project 4
# Reference: Text pages 293 - 295
# 11 November 2018
# Rodrigo Becerril Ferreyra
# CSULB ID 017584071

# We will write data to a text file.

def main():
    # Open a text file with the name you gave it, name.txt.
    outfile = open(r"thanksgiving.txt", 'w') #write mode

    # Let's write to the file
    outfile.write("Turkey with stuffing\n"
    "Mashed potatoes with gravy\n"
    "Awful canned cranberries\n"
    "Cocktails\n"
    "Pumpkin pie\n")
    outfile.close()


main()
