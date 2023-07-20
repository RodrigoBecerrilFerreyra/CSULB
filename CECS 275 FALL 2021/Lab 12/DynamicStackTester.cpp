/**
 * C++ program that tests an input string for balanced delimiters, given 
 * that they are parentheses, curly brackets, or square brackets.
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1.7
*/

#include <iostream>
#include "DynamicStack.h"
#include "DynamicStack.cpp"

using namespace std;

int main(){
    // Initialize storage/control variables.
    // Stack/search consists of individual characters from string.
    DynamicStack<char> delimitTest;
    // Store user's input text.
    string userInput;
    // String positioning/status counters.
    int nonDel = 0;
    int pos = 0;
    char matcher = '\0';
    int choice = 1;

    cout << "Testing string delimiting using stacks.\n";

    while(choice){
        // Reset positional/control variables before gathering input.
        nonDel = 0;
        pos = 0;
        matcher = '\0';
        // Alert user to give new input.
        cout << "Enter a string now.\n";
        cin >> userInput;
        // Loop through string until end OR right-hand delimiter has no pair.
        do {
            switch (userInput[pos]) {
                // Left-hand delimiters below get pushed onto stack.
                case '(': {
                    delimitTest.push('(');
                    break;
                }
                case '{': {
                    delimitTest.push('{');
                    break;
                }
                case '[': {
                    delimitTest.push('[');
                    break;
                }
                // Right-hand delimiters below pop stack and check for match.
                case ')': {
                    delimitTest.pop(matcher);
                    if (matcher != '(') {
                        cout << "Delimiting failed: parenthesis.\n";
                        nonDel = 1;
                    }
                    break;
                }
                case '}': {
                    delimitTest.pop(matcher);
                    if (matcher != '{') {
                        cout << "Delimiting failed: curly bracket.\n";
                        nonDel = 1;
                    }
                    break;
                }
                case ']': {
                    delimitTest.pop(matcher);
                    if (matcher != '[') {
                        cout << "Delimiting failed: square bracket.\n";
                        nonDel = 1;
                    }
                    break;
                }
                // Character from string was not a recognized delimiter.
                default:
                    break;
            }
            pos++;
        } while (userInput[pos] != 0 && nonDel == 0);

        // Verify that the stack is empty and non-delimited flag not active.
        if (delimitTest.isEmpty() && nonDel == 0) {
            cout << "String was fully delimited.\n";
        } else {
            cout << "String failed delimiting tests.\n";
            // Empty stack of any remaining values if exited abruptly.
            while (delimitTest.isEmpty() == false) {
                delimitTest.pop(matcher);
            }
        }
        cout << "Continue? Enter 0 now to exit and 1 to continue.\n";

        do{
            cin >> choice;
            if (choice != 0 && choice != 1) {
                cout << "Not a valid input. \n";
            }
        } while (choice != 0 && choice != 1);

        cout << "=======================================\n";
    }

    return 0;
}
