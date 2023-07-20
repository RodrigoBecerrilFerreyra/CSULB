"""
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 6
    Date: 12 December 2020
"""
import matplotlib.pyplot as plt
import numpy as np
from time import time

def main():
    # Problem 1
    sequences = [np.zeros(15) for i in range(10000)]
    # States are 0, 1, and 2
    P = ["pre-allocating" for i in range(15)]
    P[0] = np.array([[1/2, 1/4, 1/4],
                    [1/4, 1/8, 5/8],
                    [1/3, 2/3, 0]])
    P_accumulated = [[1/2, 3/4, 1],
                    [1/4, 3/8, 1],
                    [1/3, 1, 1]]
    
    # Populate sequences
    for i in range(10000):
        # Initial state
        randomNumber = np.random.random()
        sequences[i][0] = 0 if randomNumber < 1/4 else 2
        for j in range(1, 15):
            randomNumber = np.random.random()
            if randomNumber < P_accumulated[int(sequences[i][j-1])][0]:
                sequences[i][j] = 0
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][1]:
                sequences[i][j] = 1
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][2]:
                sequences[i][j] = 2
    
    # Find probabilities
    num_zeros = np.zeros(15)
    num_ones = np.zeros(15)
    num_twos = np.zeros(15)
    for j in range(15):
        for i in range(10000):
            if sequences[i][j] == 0:
                num_zeros[j] += 1
            elif sequences[i][j] == 1:
                num_ones[j] += 1
            elif sequences[i][j] == 2:
                num_twos[j] += 1
    num_zeros /= 10000
    num_ones /= 10000
    num_twos /= 10000

    # Repeated multiplication for powers
    P[1] = np.matmul(P[0], P[0])
    for i in range(1, 15):
        P[i] = np.matmul(P[i-1], P[0])

    P_multiplied = [np.array([1/4, 0, 3/4])]
    for i in range(14):
        P_multiplied.append(np.matmul(P_multiplied[0], P[i]))

    calc_zeros = np.zeros(15)
    calc_ones = np.zeros(15)
    calc_twos = np.zeros(15)

    for index in range(15):
        calc_zeros[index] = P_multiplied[index][0]
        calc_ones[index] = P_multiplied[index][1]
        calc_twos[index] = P_multiplied[index][2]

    # Graphs
    # Sample
    plt.figure()
    plt.plot(range(15), sequences[0], '-g.')
    plt.title("Sample Three-State Markov Chain (One Run)")
    plt.xlabel('Step Number')
    plt.ylabel('State Number')

    # Measured
    plt.figure()
    plt.plot(range(15), num_zeros, '-r.', label="State 0")
    plt.plot(range(15), num_ones, '-g.', label="State 1")
    plt.plot(range(15), num_twos, '-b.', label="State 2")
    plt.title("Simulated Three-State Markov Chain")
    plt.xlabel('Step Number')
    plt.ylabel('Probability')
    plt.legend(loc = 'upper right')

    # Calculated
    plt.figure()
    plt.plot(range(15), calc_zeros, '-r.', label="State 0")
    plt.plot(range(15), calc_ones, '-g.', label="State 1")
    plt.plot(range(15), calc_twos, '-b.', label="State 2")
    plt.title("Measured Three-State Markov Chain")
    plt.xlabel('Step Number')
    plt.ylabel('Probability')
    plt.legend(loc = 'upper right')

    plt.show()

    # Problem 2
    P = ["pre-allocating" for i in range(20)]
    P[0] = np.array([[0, 1, 0, 0, 0], # Page A
        [1/2, 0, 1/2, 0, 0], # Page B
        [1/3, 1/3, 0, 0, 1/3], # Page C
        [1, 0, 0, 0, 0], # Page D
        [0, 1/3, 1/3, 1/3, 0]]) # Page E
    
    # Equal probabilities
    # Repeated multiplication for powers
    P[1] = np.matmul(P[0], P[0])
    for i in range(1, 20):
        P[i] = np.matmul(P[i-1], P[0])
    P_multiplied = [np.ones(5)*(1/5)]
    for i in range(19):
        P_multiplied.append(np.matmul(P_multiplied[0], P[i]))

    calc_zeros = np.zeros(20)
    calc_ones = np.zeros(20)
    calc_twos = np.zeros(20)
    calc_threes = np.zeros(20)
    calc_fours = np.zeros(20)

    for index in range(20):
        calc_zeros[index] = P_multiplied[index][0]
        calc_ones[index] = P_multiplied[index][1]
        calc_twos[index] = P_multiplied[index][2]
        calc_threes[index] = P_multiplied[index][3]
        calc_fours[index] = P_multiplied[index][4]
    
    plt.figure()
    plt.plot(range(20), calc_zeros, '-r.', label="Page A")
    plt.plot(range(20), calc_ones, '-g.', label="Page B")
    plt.plot(range(20), calc_twos, '-b.', label="Page C")
    plt.plot(range(20), calc_threes, '-y.', label="Page D")
    plt.plot(range(20), calc_fours, '-m.', label="Page E")
    plt.title("Five-State Markov Chain Representing Webpages")
    plt.xlabel('Step Number')
    plt.ylabel('Probability')
    plt.legend(loc = 'upper right')
    # Ranking: B, A, C, E, D

    # Starting at Page E
    P_multiplied = [np.array([0, 0, 0, 0, 1])]
    for i in range(19):
        P_multiplied.append(np.matmul(P_multiplied[0], P[i]))

    calc_zeros = np.zeros(20)
    calc_ones = np.zeros(20)
    calc_twos = np.zeros(20)
    calc_threes = np.zeros(20)
    calc_fours = np.zeros(20)

    for index in range(20):
        calc_zeros[index] = P_multiplied[index][0]
        calc_ones[index] = P_multiplied[index][1]
        calc_twos[index] = P_multiplied[index][2]
        calc_threes[index] = P_multiplied[index][3]
        calc_fours[index] = P_multiplied[index][4]
    
    plt.figure()
    plt.plot(range(20), calc_zeros, '-r.', label="Page A")
    plt.plot(range(20), calc_ones, '-g.', label="Page B")
    plt.plot(range(20), calc_twos, '-b.', label="Page C")
    plt.plot(range(20), calc_threes, '-y.', label="Page D")
    plt.plot(range(20), calc_fours, '-m.', label="Page E")
    plt.title("Five-State Markov Chain Starting at Page E")
    plt.xlabel('Step Number')
    plt.ylabel('Probability')
    plt.legend(loc = 'upper right')
    # Same ranking as before

    plt.show()

    # Problem 3 & 4
    sequences = [np.zeros(15) for i in range(10000)]
    P = np.array([
        [1, 0, 0, 0, 0],
        [0.3, 0, 0.7, 0, 0],
        [0, 0.5, 0, 0.5, 0],
        [0, 0, 0.6, 0, 0.4],
        [0, 0, 0, 0, 1]
    ])
    P_accumulated = [
        [1, 0, 0, 0, 0],
        [0.3, 0, 1, 0, 0],
        [0, 0.5, 0, 1, 0],
        [0, 0, 0.6, 0, 1],
        [0, 0, 0, 0, 1]
    ]
    
    # Populate sequences
    for i in range(10000):
        # Initial state
        sequences[i][0] = 2
        for j in range(1, 15):
            randomNumber = np.random.random()
            if randomNumber < P_accumulated[int(sequences[i][j-1])][0]:
                sequences[i][j] = 0
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][1]:
                sequences[i][j] = 1
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][2]:
                sequences[i][j] = 2
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][3]:
                sequences[i][j] = 3
            elif randomNumber < P_accumulated[int(sequences[i][j-1])][4]:
                sequences[i][j] = 4

    # Find probabilities
    num_zeros = np.zeros(15)
    num_ones = np.zeros(15)
    num_twos = np.zeros(15)
    num_threes = np.zeros(15)
    num_fours = np.zeros(15)
    for j in range(15):
        for i in range(10000):
            if sequences[i][j] == 0:
                num_zeros[j] += 1
            elif sequences[i][j] == 1:
                num_ones[j] += 1
            elif sequences[i][j] == 2:
                num_twos[j] += 1
            elif sequences[i][j] == 3:
                num_threes[j] += 1
            elif sequences[i][j] == 4:
                num_fours[j] += 1
    num_zeros /= 10000
    num_ones /= 10000
    num_twos /= 10000
    num_threes /= 10000
    num_fours /= 10000

    plt.figure()
    plt.plot(range(15), num_zeros, '-r.', label="State 0")
    plt.plot(range(15), num_ones, '-g.', label="State 1")
    plt.plot(range(15), num_twos, '-b.', label="State 2")
    plt.plot(range(15), num_threes, '-y.', label="State 3")
    plt.plot(range(15), num_fours, '-m.', label="State 4")
    plt.title("Simulated Five-State Markov Chain")
    plt.xlabel('Step Number')
    plt.ylabel('Probability')
    plt.legend(loc = 'upper right')

    # find a model that ends in 0
    for i in range(10000):
        if sequences[i][-1] == 0:
            plt.figure()
            plt.plot(range(15), sequences[i], '-g.')
            plt.title("Sample Five-State Drunkard's Walk (Ending in State 0)")
            plt.xlabel('Step Number')
            plt.ylabel('State Number')
            break
    # find a model that ends in 4
    for i in range(10000):
        if sequences[i][-1] == 4:
            plt.figure()
            plt.plot(range(15), sequences[i], '-g.')
            plt.title("Sample Five-State Drunkard's Walk (Ending in State 4)")
            plt.xlabel('Step Number')
            plt.ylabel('State Number')
            break
    plt.show()

    plt.show()

if __name__ == "__main__":
    main()
