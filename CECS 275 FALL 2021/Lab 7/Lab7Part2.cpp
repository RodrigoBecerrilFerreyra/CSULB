/*
* This C++ program stores an array of string objects containing
* names and phone numbers and allows the user to search the contents
* for desired entries.
* CECS 275 - Fall 2021
* @author Ethan Hua
* @author Rodrigo Becerril Ferreyra
* @version 1.71
*
*/

#include <iostream> // Used for simple I/O
#include <string>   // Used for string-based manipulation/functions
#include <cctype>   // Used for uppercase-casting for case-insensitivity

using namespace std;

int nameComp(string,string);
string castUpper(string);

int main(){
    // Loop control variable
    int search = 1;
    // Counter for number of names that match or contain user input
    int results = 0;
    string query;
    /*
    Phone number array, created as directed by Chapter 10 Programming 
    Challenge 18 to contain at least 10 entries. The format is the
    first name and last name, separated by the corresponding phone
    number using a comma. Defined as "const" as it is not expected to
    be modified at any point in the program runtime.
    "phonebooksize" should be updated in tandem with more entries being
    added to the list.
    */
    const string phonebook[15] = {"Alejandra Cruz, 555-1223",
        "Joe Looney, 555-0097","Geri Palmer, 555-8787","Li Chen, 555-1212",
        "Holly Gaddis, 555-8878","Sam Wiggins, 555-0998","Bob Kain,555-8712",
        "Tim Haynes, 555-7676","Warren Gaddis, 555-9037",
        "Jean James, 555-4939","Ron Palmer, 555-2783","Noel Jones, 555-8134",
        "Toby Fox, 555-1846","Yen Sid, 555-1955","Yugiri Hana, 555-3142"};
    const int phonebookSize = 15;

    // User prompt
    cout << "Would you like to find a phone number? \n";

    while(search){
        // Reset name-match counter
        results = 0;

        // User prompt
        cout << "Enter a name or partial name now! \n";

        cin >> query;

        /*
        Linear search through "phonebook" string array to find entries that
        match with user's request either partially or completely.
        */
        for(int list = 0; list < phonebookSize; list++){
            results += nameComp(query, phonebook[list]);
        }
        // If no entries matched, alert user.
        if (results == 0) {
            cout << "No entries were found. \n";
        }

        // Prompt user to run again.
        cout << "\nSearch for another name? ";
        cout << "Enter 0 to exit and 1 to continue. \n";
        cin.clear();

        do{
            cin >> search;
            if (search != 0 && search != 1) {
                cout << "Not a valid input. \n";
            } // Input control/verification
        } while (search != 0 && search != 1);

    }

    cout << "Terminating... \n";

    return 0;
    
}

/**
 * Accepts two strings as input to identify if any sections of either string
 * correspond to or contain one another, returning a numerical representation
 * according to this comparison and a terminal output if there is a match.
 * @param received The first string input, intended to accept the user's
 *                 input request.
 * @param entry    The second string input, intended to accept the actual
 *                 phonebook entry currently being compared.
 * @return         The truth value of the comparison regarding whether
 *                 the second string contains elements of the first.
*/
int nameComp(string received, string entry){

    /*
    The use of uppercase conversion results in a null-terminated string.
    As a result, we can assume that the last character in any string will
    be a null character, and searching through any strings will thus always
    result in a match found in the last or "-1" index.
    */
    int nullChar = -1;

    // Converts both user input and current entry to all-uppercase.
    string convertEntry = castUpper(entry);
    string convertInput = castUpper(received);

    // Variable logs first position a match was found between the two strings.
    int comparator = convertEntry.find(convertInput);

    // If a match was found at the final position, assume no other matches.
    if (comparator == nullChar) {
        // Immediately return to call with "false"/no match/0
        return 0;
    }

    // Presumed that something in entry matched with user query, so output.
    cout << entry << "\n";
    // Return to call with "true"/match found/1
    return 1;
}

/**
 * Accepts a base string as an input and converts all alphabetical contents
 * to their uppercase equivalents in order to allow case-insensitive
 * comparisons in other functions.
 * 
 * @param target    Original reference string submitted for processing.
 * @return          All-uppercase conversion of the original reference string.
*/
string castUpper(string target){
    // Defines start position of any string as 0.
    int stringStart = 0;
    // Initialize string to use as buffer.
    string convertTarget = target;

    // Identify length of the target string for loop.
    int nameLength = convertTarget.length();

    /*
    Convert characters in string to upper case one-by-one.
    Only characters are acted upon; integers are left as they are.
    */
    for(int strRef=0; strRef < nameLength; strRef++){
        convertTarget[strRef] = toupper(convertTarget[strRef]);
    }

    // Returns the all-uppercase string to the call.
    return convertTarget;

}
