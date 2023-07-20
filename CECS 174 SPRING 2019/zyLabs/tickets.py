tickets = 20
buyers = 0

while tickets > 0:
    print("There are currently {} tickets remaining.".format(tickets))

    user_input = int(input("How many tickets would you like to purchase?\n"))
    while (user_input > 4) or (user_input > tickets):
        print("Sorry, you can't buy that many.")
        user_input = int(input("How many tickets would you like to purchase?\n"))
    else:
        buyers += 1
        tickets -= user_input

print("The total number of buyers was", buyers)    
