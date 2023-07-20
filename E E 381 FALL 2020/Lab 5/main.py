"""
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 17 November 2020
"""

import numpy as np
import matplotlib.pyplot as plt
from time import time

def main():
    N = 1_500_000 # Population size
    mu = 55 # population mean, grams
    sigma = 5 # population std, grams
    sample_means = np.zeros(200)

    # Problem 1
    print("\nProblem 1 starting...")
    start_time = time()

    population = np.random.normal(mu, sigma, N)

    # sample size elements from population
    for size in range(1, 201): # Z in [1, 200]
        sample = []
        for _ in range(size):
            sample.append(population[np.random.randint(N)])
        sample_means[size-1] = np.mean(sample)
    end_time = time()
    
    domain = np.linspace(1, 200, 1001)
    # 95% confidence interval
    plt.figure()
    ax = plt.gca()
    ax.set_ylim([45, 65])
    ax.set_xlim([0, 200])
    ax.set_xlabel("Sample size")
    ax.set_ylabel("Arithmetic mean of sample (g)")
    plt.title("Sample Means and 95% Confidence Intervals")

    plt.plot(domain, mu + 1.96 * sigma/np.sqrt(domain), "--r")
    plt.plot(domain, mu - 1.96 * sigma/np.sqrt(domain), "--r")
    plt.scatter(np.arange(1, 201, 1), sample_means, marker=".")
    
    # 99% confidence interval
    plt.figure()
    ax = plt.gca()
    ax.set_ylim([45, 65])
    ax.set_xlim([0, 200])
    ax.set_xlabel("Sample size")
    ax.set_ylabel("Arithmetic mean of sample (g)")
    plt.title("Sample Means and 99% Confidence Intervals")

    plt.plot(domain, mu + 2.58 * sigma/np.sqrt(domain), "--g")
    plt.plot(domain, mu - 2.58 * sigma/np.sqrt(domain), "--g")
    plt.scatter(np.arange(1, 201, 1), sample_means, marker=".")
    plt.show()
    
    print(f"Problem 1 complete! Time taken: {end_time - start_time} s.")

    # Problem 2
    print("\nProblem 2 starting...\n")
    print("Values are given in per cent.")
    start_time = time()

    for size in [5, 40, 120]:
        successes = [0, 0, 0, 0]
        for _ in range(10000):
            # Create and populate list from population
            X = np.zeros(size)
            for i in range(size): X[i] = population[np.random.randint(N)]
            X_bar = np.mean(X); S_hat = np.sqrt(np.sum((X - X_bar)**2)/(size-1))

            # Normal 95% confidence [0]
            successes[0] += X_bar - 1.96*(S_hat/np.sqrt(size)) <= mu <= X_bar + 1.96*(S_hat/np.sqrt(size))

            # Student's t-distribution 95% confidence [1]
            successes[1] += X_bar - 2.78*(S_hat/np.sqrt(size)) <= mu <= X_bar + 2.78*(S_hat/np.sqrt(size))

            # Normal 99% confidence [2]
            successes[2] += X_bar - 2.58*(S_hat/np.sqrt(size)) <= mu <= X_bar + 2.58*(S_hat/np.sqrt(size))

            # Student's t-distribution 99% confidence [3]
            successes[3] += X_bar - 4.60*(S_hat/np.sqrt(size)) <= mu <= X_bar + 4.60*(S_hat/np.sqrt(size))
        print(f"For size={size}: {successes[0]/100} {successes[2]/100} {successes[1]/100} {successes[3]/100}")
    
    end_time = time()
    print(f"\nProblem 2 complete! Time taken: {end_time - start_time} s.")

if __name__ == "__main__":
    main()
