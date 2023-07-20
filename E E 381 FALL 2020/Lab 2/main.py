"""
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: E E 381 Lab 2
    Date: 02 October 2020
"""
from itertools import accumulate
import random
from math import isclose
from time import time

def nSidedDie(p):
    """
    Returns an integer in the interval [1, len(p)].\n
    Params: p (sequence) - list of probabilites for the sides of the die.\n
    Output: int - random integer in [1, len(p)] whose probability is dictated by p.\n
    Except: Throws ValueError if the elements of p do not sum to 1.
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
    
    p0 = 0.6; e0 = 0.05; e1 = 0.03

    # Problem 1
    print("\nProblem 1 starting...")
    start_time = time()

    successes = 0
    for _ in range(100000):
        S = nSidedDie([p0, 1-p0]) - 1
        R = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        successes += int(S == R) # adds 1 if S == R, 0 otherwise
    end_time = time()
    print("Problem 1 finished.")
    print(f"{successes} successes out of 100 000 (probability of success: {successes/100000})")
    print(f"Time taken: {end_time - start_time} s")

    # Problem 2
    print("\nProblem 2 starting...")
    start_time = time()

    results = []
    for _ in range(100000): # populate list with 2-tuples (S, R)
        S = nSidedDie([p0, 1-p0]) - 1
        R = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        results.append((S, R))
    
    tries, successes = 0, 0
    for tup in results: # find all tuples where S = 1
        if tup[0] != 1: continue # if S is not 1
        tries += 1 # always increment number of tries
        successes += tup[1] # 1 if R = 1, 0 if R = 0

    end_time = time()
    print("Problem 2 finished.")
    print(f"{successes} successes out of {tries} (probability of success: {successes/tries})")
    print(f"Time taken: {end_time - start_time} s")

    # Problem 3
    print("\nProblem 3 starting...")
    start_time = time()

    results = []
    for _ in range(100000): # populate list with 2-tuples (S, R)
        S = nSidedDie([p0, 1-p0]) - 1
        R = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        results.append((S, R))
    
    tries, successes = 0, 0
    for tup in results: # find all tuples where R = 1
        if tup[1] != 1: continue # if R is not 1
        tries += 1 # always increment number of tries
        successes += tup[0] # 1 if S = 1, 0 if S = 0

    end_time = time()
    print("Problem 3 finished.")
    print(f"{successes} successes out of {tries} (probability of success: {successes/tries})")
    print(f"Time taken: {end_time - start_time} s")

    # Problem 4
    print("\nProblem 4 starting...")
    start_time = time()

    successes = 0
    for _ in range(100000):
        S = nSidedDie([p0, 1-p0]) - 1
        R1 = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        R2 = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        R3 = (nSidedDie([e1, 1-e1]) - 1) if S else (nSidedDie([1-e0, e0]) - 1)
        D = (R1 & R2) | (R1 & R3) | (R2 & R3) # majority rule function with three variables (Boolean algebra)
        successes += (D == S) # adds 1 if D == S, 0 otherwise

    end_time = time()
    print("Problem 4 finished.")
    print(f"{successes} successes out of 100 000 (probability of success: {successes/100000})")
    print(f"Time taken: {end_time - start_time} s")

if __name__ == "__main__":
    main()
