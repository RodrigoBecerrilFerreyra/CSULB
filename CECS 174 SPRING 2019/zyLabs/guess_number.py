import random

tries = 1

print("I am thinking of a number between 1 and 10.")
rng = random.randint(1, 10) #range(1, 11)
while tries <= 5:
    user_input = int(input("Take a guess :\n"))

    while (user_input < 1) or (user_input > 10):
        user_input = int(input("Wrong value, re-enter:\n"))
    
    if user_input > rng:
        print("Your guess is to high.")
        tries += 1
    elif user_input < rng:
        print("Your guess is too low.")
        tries += 1
    else:
        print("Good job, you got it with", tries, "guesses")
        break #so loop-else won't trigger
else: #if user does not guess correctly
    print("You guessed wrong, the number I was thinking of was", rng)
