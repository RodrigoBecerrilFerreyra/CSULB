// Implementation file for the MathStack class
#include "MathStack.h"

void MathStack::add()
{
    int num, sum;

    // Pop the first two values off the stack.
    pop(sum);
    pop(num);

    // Add the two values, store in sum.
    sum += num;

    // Push sum back onto the stack.
    push(sum);
}

void MathStack::sub()
{
    int num, diff;

    // Pop the first two values off the stack.
    pop(diff);
    pop(num);

    // Subtract num from diff.
    diff -= num;

    // Push diff back onto the stack.
    push(diff);
}


void MathStack::mult()
{
    int num, prod;

    // Pop the first two values off the stack.
    pop(prod);
    pop(num);

    // Multiply num and prod.
    prod *= num;

    // Push prod back onto the stack.
    push(prod);
}

void MathStack::div()
{
    int num, quot;

    // Pop the first two values off the stack.
    pop(quot);
    pop(num);

    // Divide quot by num.
    quot /= num;

    // Push quot back onto the stack.
    push(quot);  
}

void MathStack::addAll()
{
    int sum, num = 0;

    // Continually pop values off the stack until it is empty.
    while(isEmpty() != true)
    {
        // Add the most recently popped value to sum.
        pop(num);
        sum += num;
    }
    
    // Push sum back onto the stack.
    push(sum);
}

void MathStack::multAll()
{
    int prod = 1;
    int num = 0;

    // Continually pop values off the stack until it is empty.
    while(isEmpty() != true)
    {
        // Multiply the most recently popped value to prod.
        pop(num);
        prod *= num;
    }
    
    // Push prod back onto the stack.
    push(prod);
    
}
