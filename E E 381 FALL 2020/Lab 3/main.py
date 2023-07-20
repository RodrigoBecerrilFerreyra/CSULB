"""
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 3
    Date: 14 October 2020
"""

import matplotlib.pyplot as plt
import numpy as np
import random
from itertools import accumulate
from math import isclose, factorial, exp
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

def count_instances(values):
    """
    Returns an ordered list of tuples of the form (value, number of occurrences).
    """
    from collections import Counter
    c = Counter(values)
    return sorted([(i, c[i]) for i in c])

def main():

    N = 10000; n = 1000 # given

    # Problem 1
    print("\nProblem 1 starting...")
    start_time = time()

    # Math
    p = [0.2, 0.1, 0.15, 0.3, 0.2, 0.05] # given
    X = []
    for _ in range(N):
        successes = 0

        for _ in range(n): # no harm in nesting _

            rolls = [nSidedDie(p), nSidedDie(p), nSidedDie(p)] # roll three dice
            if rolls[0] == 1 and rolls[1] == 2 and rolls[2] == 3:
                successes += 1
        
        X.append(successes) # number of successes in n rolls
    
    end_time = time()
    print(f"Problem 1 complete. Time taken: {end_time - start_time} s.")

    # Plotting
    counted_X = count_instances(X)
    plt.stem(
        [i[0] for i in counted_X], #gives number
        [i[1]/N for i in counted_X], #gives number counts
        use_line_collection=True #suppresses unwanted output
        )
    plt.xlabel(f"Number of successes in {n} rolls")
    plt.ylabel("Experimental Probability")
    plt.title("Bernoulli Trials: PMF")
    plt.show()

    # Problem 2
    print("\nProblem 2 starting...")
    start_time = time()

    domain = len(counted_X)
    # Math
    # p = The probability that the exact roll we're looking for will occur
    p = 0.2 * 0.1 * 0.15
    q = 1-p
    X = []
    # Equivalent to math.comb (Python 3.7 does not support math.comb)
    comb = lambda a, b: factorial(a)/(factorial(b) * factorial(a-b))
    for x in range(domain):
        X.append(
            comb(n, x) * (p**x) * (q**(n-x))
        )

    end_time = time()
    print(f"Problem 2 complete. Time taken: {end_time - start_time} s.")

    # Plotting
    plt.stem(range(domain), X, use_line_collection=True)
    plt.xlabel(f"Number of successes in {n} rolls")
    plt.ylabel("Binomial Distribution Probability")
    plt.title("Bernoulli Trials: PMF - Binomial Formula")
    plt.show()

    # Problem 3
    print("\nProblem 3 starting...")
    start_time = time()

    # Math
    a = n * p # definition given by lab manual
    X = []
    for x in range(domain):
        X.append(
            a**x * exp(-a) / factorial(x)
        )

    end_time = time()
    print(f"Problem 3 complete. Time taken: {end_time - start_time} s.")

    # Plotting
    plt.stem(range(domain), X, use_line_collection=True)
    plt.xlabel(f"Number of successes in {n} rolls")
    plt.ylabel("Poisson Distribution Probability")
    plt.title("Bernoulli Trials: PMF - Poisson Approximation")
    plt.show()

if __name__ == "__main__":
    main()
