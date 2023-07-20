/**
 * Dynamic Stack header file. Adapted from Page 1187 of
 * Starting Out with C++ by Tony Gaddis
 * @version 1.2
 */

#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

template <class T>
class DynamicStack
{
    private: 
        // Structure for dynamic stack nodes
        struct StackNode
        {
            T value;         // Value in the node
            StackNode *next; // Pointer to the next node
        };

        StackNode *top;  // Pointer to the stack top
    public: 
        // Constructor
        /**
         * This function generates an empty stack.
        */
        DynamicStack()
        { top = nullptr; }

        // Destructor
        /**
         * This function deletes every node in the stack.
        */
        ~DynamicStack();

        // Stack operations
        /**
         * Member function push pushes the argument onto 
         * the stack.
        */
        void push(T);
        /**
         * Member function pop pops the value at the top 
         * of the stack off, and copies it into the variable 
         * passed as an argument. 
        */
        void pop(T &);
        /**
         * Member function isEmpty returns true if the stack 
         * is empty, or false otherwise.
        */
        bool isEmpty();
};

#endif