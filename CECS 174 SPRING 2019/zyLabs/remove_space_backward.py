user_input = input("Enter a string:\n")

# Goes through the user input string and adds the character to nospaces if it isn't a space.
nospaces = ""
for index in user_input:
    if index != " ":
        nospaces += index

# Loops through nospaces backwards and adds each character to backwards (string).
backwards = ""
for index in range(len(nospaces)-1, -1, -1): # len(nospaces) - 1 to avoid indexerror, stop at -1 to get all characters
    backwards += nospaces[index]

print("The new string:", backwards)
