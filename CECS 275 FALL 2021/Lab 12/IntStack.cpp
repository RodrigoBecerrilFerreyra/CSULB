// Implementation file for the IntStack class
#include <iostream>
#include "IntStack.h"

IntStack::IntStack(int size)
{
    stackArray = new int[size];
    stackSize = size;
    top = -1;
}

IntStack::IntStack(const IntStack &obj)
{
    // Create the stack array.
    if (obj.stackSize > 0)
        stackArray = new int[obj.stackSize];
    else
        stackArray = nullptr;

    // Copy the stackSize attribute.
    stackSize = obj.stackSize;

    // Copy the stack contents.
    for (int count = 0; count < stackSize; count++)
        stackArray[count] = obj.stackArray[count];

    // Set the top of the stack.
    top = obj.top;
}

IntStack::~IntStack()
{
    delete [] stackArray;
}

void IntStack::push(int num)
{
    if (isFull())
    {
        std::cout << "The stack is full.\n";
    }
    else
    {
        top++;
        stackArray[top] = num;
    }
}

void IntStack::pop(int &num)
{
    if(isEmpty())
    {
        std::cout << "The stack is empty.\n";
    }
    else
    {
        num = stackArray[top];
        top--;
    }
}

bool IntStack::isFull() const
{
    bool status;
    if (top == stackSize - 1)
        status = true;
    else
        status = false;

    return status;
}

bool IntStack::isEmpty() const
{
    bool status;
    if (top == -1)
        status = true;
    else
        status = false;

    return status;
}