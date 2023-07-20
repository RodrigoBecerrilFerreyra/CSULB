/*
 * Prime number finder
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 2
 */
#include <fstream> // for file output

bool isPrime(int);

int main()
{
    std::ofstream outFile("prime_numbers.txt");
    // Problem 23 asks for the prime numbers from 1 to 100
    for(int i = 1; i <= 100; ++i)
    {
        if(isPrime(i))
        {
            outFile << i << " ";
        }
    }
    outFile.close();
    
    return 0;
}

/**
 * Determines whether or not the input is prime
 * using the brute-force trial division algorithm.
 * @param numToTest number that is either prime or composite
 * @return true if numToTest is prime, false if composite
*/
bool isPrime(int numToTest)
{
    /*
    Explanation of operation: the program starts by dividing numToTest
    by every whole number starting from 2. If numToTest is divisible by any
    number, then it is composite. If there is no number which does not give
    a remainder, then numToTest is prime.
    */
    
    // 1 is neither prime nor composite.
    // Anything less is undefined.
    if(numToTest < 2) return false;

    for(int divisor = 2; divisor < numToTest; ++divisor)
    {
        if(numToTest % divisor == 0)
            return false;
    }
    return true;
}
