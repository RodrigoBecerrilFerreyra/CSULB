/*
 * Sum of All Digits Calculator
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 4
 */
#include <iostream>

int sumOfAllDigits(int);

int main()
{
    int user_value, total, old_value;
    // The following while loop runs until the user inputs a positive integer.
    while(true)
    {
        std::cout << "Please enter a positive integer: ";
        std::cin >> user_value;
        if(user_value <= 0)
        {
            std::cout << "Positive integers are whole numbers greater than 0. "
                      << "Please try again." << std::endl;
            continue;
        }

        std::cout << "You have entered " << user_value << "." << std::endl;

        int total = sumOfAllDigits(user_value);

        std::cout << "The sum of all the digits in " << user_value << " is "
                << total << "." << std::endl;
    }
}

/**
* Adds the sum of the digits of the input and returns that sum.
* @param numToSum the number whose digits will be summed
* @return the sum of all digits
*/
int sumOfAllDigits(int numToSum)
{
    int total = 0;

    while(numToSum != 0)
    // numToSum being 0 means that the variable was one digit in this
    //   iteration, and that there are no more digits to total.
    {
        // The expression "% 10" returns the most insignificant digit
        //   (in decimal): for example, 90121 % 10 returns 1.
        total += numToSum % 10;
        // Due to the properties of integer division, dividing by 10
        //   removes the variable's least significant digit.
        numToSum /= 10;
    }

    return total;
}
