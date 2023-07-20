/*
 * Sum of All Digits Calculator
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 3
 */
#include <iostream>

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

        // The variable total will hold the final answer.
        // The variable old_value holds the user's input, which is necessary
        //   because the variable user_value will be modified in the process of
        //   finding the answer.
        total = 0; old_value = user_value;
        // user_value being 0 means that the variable was one digit in this
        //   iteration, and that there are no more digits to total.
        while(user_value != 0)
        {
            // The expression "% 10" returns the most insignificant digit
            //   (in decimal): for example, 90121 % 10 returns 1.
            total += user_value % 10;
            // Due to the properties of integer division, dividing by 10
            //   removes the variable's least significant digit.
            user_value /= 10;
        }

        std::cout << "The sum of all the digits in " << old_value << " is "
                << total << "." << std::endl;
    }
}
