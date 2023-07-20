/**
 * Program to recursively test if a text string is a palindrome.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1.37
 */

#include <iostream> // Used for terminal output and obtaining user input
#include <string>   // Used for general string object generation purposes
#include <cctype>   // Used for single-character manipulation

using namespace std;

// Function prototypes
bool isPalindrome(const string);
bool palinTest(const string,int,int);
void testedPrint(const string);

int main(){
    // Stores user input
    string userTest;
    // User input loop control
    int loop = 1;
    // Context
    cout << "Beginning palindrome tests. \n";
    // Example
    string sample = "Able was I, ere I saw Elba.";
    testedPrint(sample);
    // Master user-input loop for collecting data to test
    while (loop) {
        // Context printed at top of every new loop
        cout << "Enter new test here. \n";
        cout << "Send a [0] to quit. \n";
        // "getline" to ensure whole single-line input read
        getline(cin,userTest);
        if (userTest == "0") {
        // User wishes to quit
            loop = 0;
        } else {
        // Send user's input string to function for test/result print.
            testedPrint(userTest);
        }
    }

    cout << "Terminating...\n";
    return 0;
}

/**
 * Pre-recursion string-checking function used to prepare data for the 
 * recursive implementation. Obtains the length of the string and 
 * immediately returns true for input strings less than 2 characters long 
 * as they are palindromes by default. Otherwise, test begins by feeding 
 * recursive function the beginning and ending (absent the NULL terminator) 
 * indexes of the string as well as the string itself. 
 * @param test    Character array to be measured.
 * @return        Truth value of whether character array is a palindrome. 
*/
bool isPalindrome(const string test){
    // Check the length of the input string.
    int testLen = test.length();
    if (testLen < 2) {
    // NULL & Single-character strings are palindromes by default.
        return true;
    } else {
    // Begin recursively checking if input string is recursive.
        return palinTest(test, 0, testLen-1);
    }
}

/**
 * Recursive palindrome verification function. Begins at both ends of a 
 * provided string and draws closer to the midpoint until it is either 
 * reached or an unmatched pair of letters or numbers across both ends 
 * is found. Function ignores non-alphanumeric characters by calling 
 * itself again advanced one position relative to start/end. Maintains 
 * case-insensitivity by casting alphabetical characters to upper-case.
 * 
 * @param test      Referenced character array.
 * @param start     The index on the left-hand-side of the array. 
 * @param end       The index on the right-hand-side of the array.
 * @return          Truth value of the given pair of indexes matching. 
*/
bool palinTest(const string test, int start, int end){
    if (start == end) {
    // Indexes have met in the middle, given string is odd-length.
        return true;
    } else if (toupper(test[start]) == toupper(test[end])) {
    // Character (near/at) start matches character (near/at) end.
        if (start+1 != end) {
        // Verify not testing an even-length string's "middle" section.
            return palinTest(test, start+1, end-1);
        } else {
        // For even-length string, "middle" has been met.
            return true;
        }
    } else if (isalnum(test[start]) == 0) {
    // Character (near/at) start is non-alphanumeric; do not care.
        return palinTest(test, start+1, end);
    } else if (isalnum(test[end]) == 0){
    // Character (near/at) end is non-alphanumeric; do not care.
        return palinTest(test, start, end-1);
    } else {
    // Currently indexed characters are alphanumeric but do not match.
        return false;
    }
}

/**
 * Terminal output handler that accepts a string to be checked by 
 * the pre-recursion palindrome verification function. Outputs the 
 * original string in quotation marks and a result based on the 
 * returned boolean value of the processed string. 
 * 
 * @param check      Desired string to verify for palindrome-status.
*/
void testedPrint(const string check){
    // Stores returned value of test
    bool verified = false;
    // Sends string to recursive palindrome-checking function
    verified = isPalindrome(check);
    // Format output
    cout << "===============================\n";
    if (verified == 0) {
        // BOOL of FALSE
        cout << "\"" << check << "\""  << " is NOT a palindrome.\n";
        cout << "===============================\n";
    } else if (verified == 1) {
        // BOOL of TRUE
        cout << "\"" << check << "\""  << " is a palindrome.\n";
        cout << "===============================\n";
    } else {
        // For unexpected errors
        cout << "Could not verify input. \n";
        cout << "===============================\n";
    }
}