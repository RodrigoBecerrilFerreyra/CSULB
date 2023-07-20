/**
 * Dynamic Stack implementation file. Adapted from Page 1187 of
 * Starting Out with C++ by Tony Gaddis
 * @version 1.2
 */

#include <iostream>
#include "DynamicStack.h"

template <class T>
void DynamicStack<T>::push(T item)
{
    StackNode *newNode = nullptr; // Pointer to a new node

    // Allocate a new node and store input there.
    newNode = new StackNode;
    newNode -> value = item;

    // If there are no nodes in the list
    // make newNode the first node.
    if (isEmpty())
    {
        top = newNode;
        newNode -> next = nullptr;
    }
    else // Otherwise, insert newNode before top.
    {
        newNode -> next = top;
        top = newNode;
    }
}

template <class T>
void DynamicStack<T>::pop(T &item)
{
    StackNode *temp = nullptr; // Temporary pointer

    // First make sure the stack isn't empty.
    if (isEmpty())
    {   
        /* 
        NOTE: This std::cout method of error-catching is transcribed 
        exactly as from the book's template.
        */
        std::cout << "The stack is empty.\n";
    }
    else // pop value off top of stack
    {
        item = top -> value;
        temp = top -> next;
        delete top;
        top = temp;
    }
}

template <class T>
bool DynamicStack<T>::isEmpty()
{
    bool status;

    if(!top)
        status = true;
    else
        status = false;

    return status;
}

template <class T>
DynamicStack<T>::~DynamicStack()
{
    StackNode *nodePtr, *nextNode;

    // Position nodePtr at the top of the stack.
    nodePtr = top;

    // Traverse the list deleting each node.
    while (nodePtr != nullptr)
    {
        nextNode = nodePtr -> next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}
