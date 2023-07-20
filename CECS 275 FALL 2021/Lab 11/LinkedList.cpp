#include <iostream>
#include "LinkedList.h"

template <class T>
void LinkedList<T>::appendNode(T newValue)
{
    ListNode* newNode; // To point to a new node
    ListNode* nodePtr; // To move through the list

    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->value = newValue;
    newNode->next = nullptr;

    // If there are no nodes in the list
    // make newNode the first node.
    if(!head)
        head = newNode;
    else // otherwise, insert newNode at end
    {
        nodePtr = head;

        // Find the last node in the list.
        while(nodePtr->next)
            nodePtr = nodePtr->next;
        
        // Insert newNode as the last node.
        nodePtr->next = newNode;
    }
}

template <class T>
void LinkedList<T>::displayList() const
{
    ListNode* nodePtr; // To move through the list

    // Position nodePtr at the head of the list.
    nodePtr = head;

    // While nodePtr points to a node, traverse
    // the list.
    while(nodePtr)
    {
        // Display the value in this node.
        std::cout << nodePtr->value << std::endl;

        // Move to the next node.
        nodePtr = nodePtr->next;
    }
}

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
    ListNode* newNode; // A new node
    ListNode* nodePtr; // To traverse the list
    ListNode* previousNode = nullptr; // The previous node

    // Allocates a new node and store num there.
    newNode = new ListNode;
    newNode->value = newValue;

    // If there are no nodes in the list
    // make newNode the first node.
    if(!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else // Otherwise, insert newNode.
    {
        // Position nodePtr at the end of the list.
        nodePtr = head;

        // Initialize previousNode to nullptr.
        previousNode = nullptr;

        // Skip all nodes whose value is less than num.
        while(nodePtr != nullptr && nodePtr->value < newValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        // If the new node is to be the 1st node in the list,
        // insert it before all other nodes.
if(previousNode == nullptr)
{
    head = newNode;
    newNode->next = nodePtr;
}
        else // Otherwise insert after the previous node.
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
    ListNode* nodePtr; // To traverse the list
    ListNode* previousNode; // To point to the previous node

    // If the list is empty, do nothing.
    if(!head)
        return;
    
    // Determine if the first node is the one.
    if(head->value == searchValue)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }
    else
    {
        // Initialize nodePtr to head of list.
        nodePtr = head;

        // Skip all nodes whose value member is
        // not equal to num.
        while(nodePtr != nullptr && nodePtr->value != searchValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        // If nodePtr is not at the end of the list,
        // link the previous node to the node after
        // nodePtr, then delete nodePtr.
        if(nodePtr)
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }
    }
}

/**
 * Destructor
 * This function deletes every node in the list.
 */
template <class T>
LinkedList<T>::~LinkedList()
{
    ListNode* nodePtr; // To traverse the list
    ListNode* nextNode; // To point to the next node

    // Position nodePtr at the end of the list.
    nodePtr = head;

    // While nodePtr is not at the end of the list...
    while(nodePtr)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr->next;

        // Delete the current node.
        delete nodePtr;

        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
}

template <class T>
void LinkedList<T>::mergeArray(const T theArray[], const int arrayLength)
{
    for(int i = 0; i < arrayLength; ++i)
        insertNode(theArray[i]);
}

template <class T>
int LinkedList<T>::search(T searchValue) const
{
    ListNode* nodePtr; // To move through the list
    int nodePos = 1; // To capture current list position

    // Position nodePtr at the head of the list.
    nodePtr = head;

    // While nodePtr points to a node, traverse
    // the list.
    while(nodePtr)
    {
        // If the current node is the desired item, return the
        // node's position in the linked list.
        if(nodePtr->value == searchValue){
            return nodePos;
        }

        // Move to the next node.
        nodePtr = nodePtr->next;
        nodePos += 1;
    }

    // If the searched item could not be found, return NULL.
    return 0;
}
