# Plotting and linear algebra modules
import matplotlib.pyplot as plt
import numpy as np
# Random Number Generation module
import random
# For counting instances
from collections import Counter
# Used in nSidedDie(p)
from itertools import accumulate
from math import isclose
# Used in main()
from time import time

def nSidedDie(p):
    """
    Returns an integer in the interval [1, len(p)].
    Params: p (sequence) - list of probabilites for the sides of the die.
    Output: int - random integer from [1, len(p)] whose probability is dictated by p.
    Except: Throws ValueError if the elements of p do not sum to 1.

    Dependencies:
    import random
    from itertools import accumulate
    from math import isclose
    """
    if not isclose(sum(p), 1):
        raise ValueError("Probabilities provided do not sum to 1.")
    #return random.choices(range(1, len(p) + 1), weights=p) #optimal way to do this
                           #probability = [0.10, 0.15, 0.20, 0.05, 0.30, 0.10, 0.10]
    cumsum = list(accumulate(p)) #returns [0.10, 0.25, 0.45, 0.50, 0.80, 0.90, 1.00]
    randnum = random.random()
    # loops through cumsum and finds the number which is less than value
    for index, value in enumerate(cumsum):
        if randnum <= value: #randnum will never be equal to 1 (guaranteed by Python)
            return index + 1

def main():
    pass
    # Problem 1
    print("Problem 1 running.")
    start_time = time()
    plt.figure()
    # work
    probabilities = [0.10, 0.15, 0.20, 0.05, 0.30, 0.10, 0.10]
    outcomes = []
    for i in range(10000): outcomes.append(nSidedDie(probabilities)) #populates outcomes list

    # plotting
    c = Counter(outcomes) #Counter object that can be treated as a dictionary
    outcomes = sorted([(i, c[i]) for i in c]) #returns a list of ordered tuples in the form (value, occurrences)
    plt.stem(
        [i[0] for i in outcomes], #gives number
        [i[1]/10000 for i in outcomes], #gives number counts
        use_line_collection=True #suppresses unwanted output
        )
    plt.xlabel("Die roll")
    plt.ylabel("Probability")
    plt.title("Problem 1")
    print(f"Problem 1 took {time() - start_time} seconds.\n")
    plt.show()

    # Problem 2
    print("Problem 2 running.")
    start_time = time()
    plt.figure()
    # work
    successes = []
    for i in range(100000): #100 000 tests
        counter = 0
        while(True):
            counter += 1
            roll1 = nSidedDie([1/6, 1/6, 1/6, 1/6, 1/6, 1/6])
            roll2 = nSidedDie([1/6, 1/6, 1/6, 1/6, 1/6, 1/6])
            if (roll1 + roll2) == 7:
                successes.append(counter)
                break
    
    # plotting
    c = Counter(successes) #Counter obj
    successes = sorted([(i, c[i]) for i in c]) #sorted list of tuples
    plt.stem(
        [i[0] for i in successes], #value
        [i[1]/100000 for i in successes], #num of occurrences
        use_line_collection=True
    )
    plt.xlabel("Tries needed to get a sum of 7")
    plt.ylabel("Probability")
    plt.title("Problem 2")
    print(f"Problem 2 took {time() - start_time} seconds.\n")
    plt.show()

    # Problem 3
    print("Problem 3 running.")
    start_time = time()
    successes = 0
    for i_outer in range(100000):
        coin_tracker = []
        for i_inner in range(100): coin_tracker.append(random.randint(0, 1))
        if coin_tracker.count(1) == 50: successes += 1
    print(f"Probability of getting 50 head and 50 tails: {successes}/100000 or {successes/100000}")
    print(f"Problem 3 took {time() - start_time} seconds.\n")

    # # Problem 4
    # print("Problem 4 Test 1 running.")
    # start_time = time()
    # m = 80000; k = 7

    # # Test 1: m terms in hacker list
    # successes = 0
    # for i_outer in range(1000):
    #     hacker_list = []
    #     # Generate m 4-letter words
    #     for i_inner in range(m):
    #         hacker_list.append(
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122))
    #         )
    #     password = (
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122))
    #     )
    #     successes += int(password in hacker_list) #1 if present, else 0
    
    # print(f"Hacker list #1 hits: {successes} out of 1000 (or {successes/1000}).")
    # # print(f"Problem 4 Test 1 took {time() - start_time} seconds.\n")

    # print("Problem 4 Test 2 running.")
    # start_time = time()
    # successes = 0
    # for i_outer in range(1000):
    #     hacker_list = []
    #     # Generate m*k 4-letter words
    #     for i_inner in range(m*k):
    #         hacker_list.append(
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122))
    #         )
    #     password = (
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122))
    #     )
    #     successes += int(password in hacker_list)
    
    # print(f"Hacker list #2 hits: {successes} out of 1000 (or {successes/1000}).")
    # print(f"Problem 4 Test 2 took {time() - start_time} seconds.\n")

    # print("Problem 4 Test 3 running.")
    # start_time = time()
    # successes = 0
    # for i_outer in range(1000):
    #     hacker_list = []
    #     # Generate 368914 4-letter words
    #     for i_inner in range(368914):
    #         hacker_list.append(
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122)) +
    #             chr(random.randint(97, 122))
    #         )
    #     password = (
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122)) +
    #         chr(random.randint(97, 122))
    #     )
    #     successes += int(password in hacker_list)
    
    # print(f"Hacker list #3 hits: {successes} out of 1000 (or {successes/1000}).")
    # print(f"Problem 4 Test 3 took {time() - start_time} seconds.\n")

if __name__ == "__main__":
    main()
