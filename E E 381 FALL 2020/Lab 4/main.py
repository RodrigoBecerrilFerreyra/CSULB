"""
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 07 November 2020
"""

import numpy as np
import matplotlib.pyplot as plt 
from time import time

def NormPDF(u, o, x):
    numerator = (x-u)**2
    denominator = 2*(o**2)
    radical = np.sqrt(2*np.pi*(o**2))
    return 1/radical*np.exp(-numerator/denominator)
def UnitPDF(a, b, x):
    return (1/abs(b-a))*np.ones(np.size(x))
def ExpoPDF(t, b):
    return (1/b)*np.exp(-t/b)

def main():
    n = 10000
    # Problem 1
    print("\nProblem 1.1 starting...")
    start_time = time()

    a = 1.0; b = 4.0

    X = np.random.uniform(a, b, n)

    # the following is appropriated off the sample code that was given
    nbins = 30
    edgecolor = 'w'
    bins = [float(x) for x in np.linspace(a, b, nbins+1)]
    h1, binedges = np.histogram(X, bins, density=True)
    be1 = binedges[0:np.size(binedges)-1]
    be2 = binedges[1:np.size(binedges)]
    b1 = (be1 + be2)/2
    barwidth = b1[1]-b1[0]
    plt.close('all')

    plt.figure()
    plt.axes(
        title="Problem 1.1: PDF of Uniform Distribution",
        xlabel="x", ylabel="P(x) = 1/(b-a)"
        )
    plt.bar(b1, h1, width=barwidth, edgecolor=edgecolor)

    plt.plot(b1, UnitPDF(a, b, b1), 'r')

    mu_X = np.mean(X)
    std_X = np.std(X)
    print("The calculated expected value and standard deviation of X are")
    print(f"{mu_X} and {std_X}, respectively.\n")
    print("The theoretical expected value and standard deviation of X are")
    print(f"{(a+b)/2} and {np.sqrt(((b-a)**2)/12)}, respectively.\n")

    end_time = time()
    print(f"Problem 1.1 finished! Time taken: {end_time - start_time}")
    plt.show()

    ###############################################################

    print("\nProblem 1.2 starting...")
    start_time = time()

    beta = 40

    T = np.random.exponential(beta, n)

    # the following is appropriated off the sample code that was given
    nbins = 100
    edgecolor = 'w'
    bins = [float(x) for x in np.linspace(0, max(T), nbins+1)]
    h1, binedges = np.histogram(T, bins, density=True)
    be1 = binedges[0:np.size(binedges)-1]
    be2 = binedges[1:np.size(binedges)]
    b1 = (be1 + be2)/2
    barwidth = b1[1]-b1[0]
    plt.close('all')

    plt.figure()
    plt.axes(
        title="Problem 1.2: PDF of Exponential Distribution",
        xlabel="x", ylabel="P(x) = (1/B)*exp(-x/B)"
    )
    plt.bar(b1, h1, width=barwidth, edgecolor=edgecolor)

    plt.plot(b1, ExpoPDF(b1, beta), 'r')

    mu_T = np.mean(T)
    std_T = np.std(T)
    print("The calculated expected value and standard deviation of X are")
    print(f"{mu_T} and {std_T}, respectively.\n")
    print("The theoretical expected value and standard deviation of X are")
    print(f"{beta} and {beta}, respectively.\n")

    end_time = time()
    print(f"Problem 1.2 finished! Time taken: {end_time - start_time}")
    plt.show()

    #########################################################################

    print("\nProblem 1.3 starting...")
    start_time = time()

    mu = 2.5; sigma = 0.75

    N = np.random.normal(mu, sigma, n)

    # the following is appropriated off the sample code that was given
    nbins = 50
    edgecolor = 'w'
    bins = [float(x) for x in np.linspace(min(N), max(N), nbins+1)]
    h1, binedges = np.histogram(N, bins, density=True)
    be1 = binedges[0:np.size(binedges)-1]
    be2 = binedges[1:np.size(binedges)]
    b1 = (be1 + be2)/2
    barwidth = b1[1]-b1[0]
    plt.close('all')

    fig3 = plt.figure()
    plt.axes(
        title="Problem 1.3: PDF of Normal Distribution",
        xlabel="x", ylabel="P(x) = (1/o*sqrt(2pi))*exp(-((x-u)^2)/(2o^2))"
    )
    plt.bar(b1, h1, width=barwidth, edgecolor=edgecolor)

    plt.plot(b1, NormPDF(mu, sigma, b1), 'r')

    mu_N = np.mean(N)
    std_N = np.std(N)
    print("The calculated expected value and standard deviation of X are")
    print(f"{mu_N} and {std_N}, respectively.\n")
    print("The theoretical expected value and standard deviation of X are")
    print(f"{mu} and {sigma}, respectively.\n")

    end_time = time()
    print(f"Problem 1.3 finished! Time taken: {end_time - start_time}")
    plt.show()

    # Problem 2
    print("\nProblem 2 starting...")
    start_time = time()

    a = 1.0; b = 4.0
    mu_W = (b+a)/2; std_W = np.sqrt((b-a)**2/12)
    S = np.zeros(n)
    for nbooks in [1, 5, 10, 15]:
        # the following is appropriated off the sample code that was given
        for i in range(n):
            S[i] = np.sum(np.random.uniform(a, b, nbooks))
        nbins = 40
        edgecolor = 'w'
        bins = [float(x) for x in np.linspace(nbooks*a, nbooks*b, nbins+1)]
        h1, bin_edges = np.histogram(S, bins, density=True)
        be1 = bin_edges[0:np.size(bin_edges)-1]
        be2 = bin_edges[1:np.size(bin_edges)]
        b1 = (be1+be2)/2
        barwidth = b1[1]-b1[0]

        plt.figure()
        plt.axes(
            title=f"Problem 2: Sum of n={nbooks} Uniform Distributions",
            xlabel=f"Thickness of {nbooks} books (cm)", ylabel="Probability"
        )
        mu_S = np.mean(S); std_S = np.std(S)
        plt.bar(b1, h1, width=barwidth, edgecolor=edgecolor)
        plt.plot(b1, NormPDF(nbooks*mu_W, std_W*np.sqrt(nbooks), b1), 'r')
        print(f"Expected: n={nbooks}, mu={nbooks*mu_W}, sigma={std_W*np.sqrt(nbooks)}")
        print(f"Calculated: n={nbooks}, mu={mu_S}, sigma={std_S}")

    end_time = time()
    print(f"Problem 2 finished! Time taken: {end_time - start_time}")
    plt.show()

    # Problem 3
    print("\nProblem 3 starting...")
    start_time = time()

    beta = 40
    C = np.zeros(n)
    for i in range(n):
        C[i] = np.sum(np.random.exponential(beta, 24))

    # the following is appropriated off the sample code that was given
    nbins = 30
    edgecolor = 'w'
    bins = [float(x) for x in np.linspace(min(C), max(C), nbins+1)]
    h1, binedges = np.histogram(C, bins, density=True)
    be1 = binedges[0:np.size(binedges)-1]
    be2 = binedges[1:np.size(binedges)]
    b1 = (be1 + be2)/2
    barwidth = b1[1]-b1[0]
    plt.close('all')

    plt.figure()
    plt.axes(
        title="Problem 3: PDF of Sum of Exponential Distributions",
        xlabel="Lifetime of a pack of 24 batteries", ylabel="Probability"
    )
    plt.bar(b1, h1, width=barwidth, edgecolor=edgecolor)

    plt.plot(b1, NormPDF(24*beta, np.sqrt(24)*beta, b1), 'r')

    plt.figure()
    plt.axes(
        title="Problem 3: PDF of Sum of Exponential Distributions",
        xlabel="Lifetime of a pack of 24 batteries", ylabel="Probability (Cumulative)"
    )
    plt.plot(b1, np.cumsum(h1)*barwidth)
    plt.grid(axis="both")

    end_time = time()
    print(f"Problem 3 finished! Time taken: {end_time - start_time}")
    plt.show()

if __name__ == "__main__":
    main()
