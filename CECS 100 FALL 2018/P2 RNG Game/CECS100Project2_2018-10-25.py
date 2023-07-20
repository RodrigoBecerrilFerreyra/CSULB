# Rodrigo Becerril Ferreyra 
# 017584071
# CECS 100 Autumn 2018
# 2018-10-25
# Project 2
# "Random-Number-Generator Game"

# Corresponds to #11 in p. 281 in the text
# Objective: make a game using randomly generated numbers without importing the "random" module.
# ---------------------------------------

# For initial seed
import time

# Main RNG. See https://en.wikipedia.org/wiki/Linear_congruential_generator
def rng(seed):
    return int((2 * seed + 0) % 6997) #range: 1 to 6997

def mathgame():
    # Will keep track of player's winning streak.
    score = 0
    # Will keep track of player's wrong misses.
    wrong = 3

    # Numlist stores random numbers, and the game will use two random indexes
    numlist = []

    # Instructions
    print("\nWelcome to Math Game!\nSimplify the expression. Get it  three times and it's game over!\n")

    # Gives the initial seed for random number generation.
    # * 10000000 ensures a whole number while keeping precision.
    seed = (time.time() * 10000000)

    # Will keep running as long as user gets the answer right.
    while(1):
        # Will populate numlist with 100 numbers
        for i in range(100):
            seed = rng(seed)
            numlist.append(seed)

        # assign values to num variables
        num1 = numlist[rng(seed) % 100]
        seed = rng(seed)
        num2 = numlist[rng(seed) % 100]

        # The equation
        print(str(num1) + " + " + str(num2))
        
        total = num1 + num2

        # A try block is always a good idea when user input is involved.
        try:
            # The user can enter his answer here.
            ui = int(input())

            # The following will be skipped if user input is invalid.

            # Compares user input to actual sum.
            # If incorrect, wrong will be decrimented and the correct answer printed.
                # if wrong <= 0 the game will end.
                # else, the game will continue.
            # If correct, score is incremented and the problem is reset.
            if ui != total:
                wrong -= 1
                print("\nAww, you failed! The answer was " + str(total) + ".", end = "")
                if wrong != 1:
                    print(" You have " + str(wrong) + " tries left.")
                else:
                    print(" You have " + str(wrong) + " try left.")

                if wrong == 0:
                    print("Aww! You ran out of lives! Your score was " + str(score) + ". Try again next time!")
                    break

            else:
                print("\nGreat job! On to the next one.")
                score += 1
        # Catches the user error if ui is invalid.
        except ValueError:
            print("\nOops! That is not a valid number. Try removing any spaces or commas.")

def guessgame():

    wrong = 3

    # Generate random numbers 1 <= x <= 20 and put them in a list of 100 elements
    # Pick one element at random and put it into a variable
    seed = (time.time() * 10000000)
    numlist = []

    for i in range(100):
        seed = (rng(seed) % 20) + 1
        numlist.append(seed)
    num1 = numlist[rng(seed) % 100]

    print("\nWelcome to Guessing Game!\nI'm thinking of a number between one and twenty. What number is it?")
    print("You get three tries.")
    while(True):
        try:
            ui = int(input())

            if ui == num1:
                print("\nYou got it!")
                break
            elif ui < num1:
                if (ui + 5) >= num1:
                    print("\nYou are close, but you undershot.")
                    wrong -= 1
                else:
                    print("\nYou undershot.")
                    wrong -= 1
            elif ui > num1:
                if (ui - 5) <= num1:
                    print("\nYou are close, but you overshot.")
                    wrong -= 1
                else:
                    print("\nYou overshot.")
                    wrong -= 1
            
            if wrong <= 0:
                print("\nAww, you're out of lives! The answer was " + str(num1) + ". Try again next time.")
                break
        except ValueError:
            print("\nYou didn't enter a valid number!")

def printhelp():
    print("""
    Math Game:
        In this game, you must calculate the simple addition equation seen on screen.
        Make sure to get it right; you only have three tries!
        Don't worry, you are not timed, so take all the time you want.
        See how far you can go!
    Guessing Game:
        In this game, you must guess which number the computer is thinking of.
        The number is a number between 1 and 20.
        You get three guesses, so make sure to get it right!
        If you get close to the number, you will get a hint as to how far you are.
        Try to guess the number in the least amount of tries!
    """)

def main():
    print("Welcome to RNG Games! Please choose a game to play.")
    print("1: Math Game\n2: Guessing Game\n3: Help")
    while(True):
        try:
            ui = int(input())
            if(ui > 3):
                raise ValueError
            break
        except ValueError:
            print("\nPlease input either a 1, a 2, or a 3.")
    
    if ui==1:
        mathgame()
    elif ui==2:
        guessgame()
    else:
        printhelp()
        main()
    
# Call to main function.
main()
