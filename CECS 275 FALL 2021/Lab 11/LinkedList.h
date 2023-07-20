/**
 * LinkedList header file. Taken from Page 1141 of
 * Starting Out with C++ by Tony Gaddis
 * @version 1
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <class T>
class LinkedList
{
    private:
        struct ListNode
        {
            T value;
            ListNode* next;
        };

        ListNode* head;
    
    public:
        LinkedList() {head = nullptr;}
        ~LinkedList();

        // linked list operations
        /**
         * appendNode appends a node containing the value
         * passed into newValue, to the end of the list.
         * @param newValue The value to append.
         */
        void appendNode(T);

        /**
         * The insertNode function inserts a node with
         * newValue copied to its value member.
         * @param newValue The value to insert.
         */
        void insertNode(T);

        /**
         * The deleteNode function searches for a node
         * with searchValue as its value. The node, if found,
         * is deleted from the list and from memory.
         * @param searchValue The value to search for.
         */
        void deleteNode(T);

        /**
         * displayList shows the value
         * stored in each node of the linked list
         * pointed to by head.
         */
        void displayList() const;

        /**
         * Iterates over theArray and inserts all values into the linked list.
         * All values are inserted in order.
         * @param theArray An array to insert into the list.
         * @param arrayLength The length of theArray.
         * @author Rodrigo Becerril Ferreyra
         */
        void mergeArray(const T theArray[], const int arrayLength);

        /**
         * search iterates through the linked list to find the first node 
         * whose value matches the defined parameter.
         * @param searchValue Desired value/contents to search for.
         * @return The linked list node containing the requested value.
         * @author Ethan Hua
         */
        int search(T) const;
};

#endif
