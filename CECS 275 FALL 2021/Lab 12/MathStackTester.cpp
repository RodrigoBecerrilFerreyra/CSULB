/**
 * C++ program that tests the MathStack class.
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1.7
 */

#include <iostream>
#include "MathStack.h"

int main()
{
    int buffer;
    // create a stack and push some numbers
    MathStack mystack(10);
    for(int i = 1; i <= 9; ++i)
        mystack.push(i);

    // testing MathStack::mult() with 9 and 8
    mystack.mult();
    mystack.pop(buffer);
    std::cout << "9 * 8 = " << buffer << " (should be 72)\n";

    // testing MathStack::div() with 7 and 6
    mystack.div();
    mystack.pop(buffer);
    std::cout << "floor(7 / 6) = " << buffer << " (should be 1)\n";

    // testing MathStack::addAll with 5 through 1
    mystack.addAll();
    mystack.pop(buffer);
    std::cout << "5 + 4 + 3 + 2 + 1 = " << buffer << " (should be 35)\n";

    // push some more numbers onto the stack
    for(int i = 1; i <= 9; ++i)
        mystack.push(i);

    // testing MathStack::multAll with 1 through 9
    mystack.multAll();
    mystack.pop(buffer);
    std::cout << "1*2*3*4*5*6*7*8*9 = " << buffer << " (should be 362880)\n";

    return 0;
}
