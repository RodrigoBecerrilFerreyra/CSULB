# project1_rps_becerrilferreyra.py
#
# Name(s): Rodrigo Becerril Ferreyra
#
# Date: 2019-02-25
#
#
import random #for random choice of bot

# RPS is all the possible choices
RPS = ["ROCK", "PAPER", "SCISSORS"]

while True:
    # getting and parsing user input
    user_choice = input("\nPlease enter your choice of \"Rock\", \"Paper\", or \"Scissors\".\n")
    user_choice = user_choice.upper()
    
    # input validation
    # will infini-loop if user does not have the correct input
    if (len(user_choice) == 0) or ((user_choice != RPS[0]) and (user_choice != RPS[1]) and (user_choice != RPS[2])):
        print("Input is invalid. Please re-enter your input.")
        continue

    # game logic below

    # random number generator assigns a choice to bot
    comp = RPS[random.randint(0, 2)]

    # Print both the user input and bot's choice
    print("Your choice: " + user_choice)
    print("Bot's choice: " + comp)

    # logic
    if comp == user_choice:
        print("It's a tie!")
    else: #if not a tie
        for i in range(-1, 2): #going to loop through RPS plus RPS[-1]
            if (comp == RPS[i]) and (user_choice == RPS[i+1]): #These are all the possibilities of user winning
                print("You win!")
                break
        else: #If user doesn't tie or win, he loses.
            print("You lose!")


    # User option to repeat

    user_choice = input("\nDo you wish to quit? y/n\n")
    user_choice = user_choice.strip()
    if (len(user_choice) == 0) or (user_choice[0].upper() == "N"):
        continue
    break

print("Thank you for playing!")
