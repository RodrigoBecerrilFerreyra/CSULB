user_list = []

while len(user_list) < 5:
    
    try:
        user_input = float(input("\nPlease enter a floating point number:\n"))
    except ValueError:
        print("ERROR: Not a number.")
        continue

    if user_input not in user_list:
        user_list.append(user_input)
    else:
        print("\nThe number is already in the list!")

print("The numbers are:", user_list)
