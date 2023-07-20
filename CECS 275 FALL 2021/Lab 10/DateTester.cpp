/**
 * Program to print out & update dates in one of three specified formats
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 2.5
 */

#include <iostream>  // Used for outputting to terminal and receiving inputs
#include <string>    // Used for string object creation
#include "Date.h"    // Requisite custom library

using namespace std;

// Function prototypes
void massDatePrint(Date);
void userDefConst1(void);
void userDefConst2(void);
void userDefConst3(void);
int inputVerify(void);

int main(){
    // Loop control variable
    int control = 1;
    // Constructor selection variable
    int params = 0;

    cout << "**************************************\n";
    cout << "****Testing [Date] Class Functions****\n";
    cout << "**************************************\n";
    cout << "Testing user input now: \n";
    while(control){
        cout << "Testing constructors...\n";
        cout << "Input a value 0-3 for constructor test. \n";
        cout << "Input a 4 to exit now. \n";
        cin >> params;
        switch(params){
            case 0: {
                cout << "--------------------------------------\n";
                cout << "Testing default constructor. \n";
                Date defaultConstruction;
                massDatePrint(defaultConstruction);
                cout << "Continue testing? 0 to exit, 1 to continue. \n";
                params = inputVerify();
                if (params == 1) {
                    break;
                }
                control = 0;
                break;
            }
            case 1: {
                cout << "--------------------------------------\n";
                userDefConst1();
                cout << "Continue testing? 0 to exit, 1 to continue. \n";
                params = inputVerify();
                if (params == 1) {
                    break;
                }
                control = 0;
                break;
            }
            case 2: {
                cout << "--------------------------------------\n";
                userDefConst2();
                cout << "Continue testing? 0 to exit, 1 to continue. \n";
                params = inputVerify();
                if (params == 1) {
                    break;
                }
                control = 0;
                break;
            }
            case 3: {
                cout << "--------------------------------------\n";
                userDefConst3();
                cout << "Continue testing? 0 to exit, 1 to continue. \n";
                params = inputVerify();
                if (params == 1) {
                    break;
                }
                control = 0;
                break;
            }
            case 4: {
                control = 0;
                break;
            }
            default: {
                cout << "Did not recognize input. Please use number 0-3. \n";
                break;
            }
        }


    }
    cout << "Terminating constructor test; moving to member function tests.\n";

    Date date1(1, 1, 1970), date2(1, 1, 1970);

    // The following code tests the rest of the Date member functions.
    do
    {
        // testing stream insertion and extraction operators
        std::cout << "Please enter a date for the date1 object.\n";
        std::cout << "Format: <day> <month> <year>: ";
        std::cin >> date1;
        std::cout << "Please enter a date for the date2 object.\n";
        std::cout << "Format: <day> <month> <year>: ";
        std::cin >> date2;

        // The individual print functions have already been tested above.
        std::cout << "date1 is " << date1 << ".\n";
        std::cout << "date2 is " << date2 << ".\n";

        // testing operator-
        std::cout << "The number of days between the two dates is "
          << (date1 - date2) << ".\n";
        std::cout << "To verify, the following number should be the same as "
          << "the previous: " << (date2 - date1) << ".\n";
        
        std::cout << "Finished? Enter 1 to continue, or 0 to quit: ";
        std::cin >> params;
    }
    while(params);
    std::cout << "Terminating...\n";
    return 0;
}

/**
 * Function used to output a formatted and distinct block of all 3 variations
 * of date output. Obtains strings containing dates and then writes to
 * terminal.
 * @param target  Date-class object that should be read for calendar dates.
*/
void massDatePrint(Date target){
    string numbers = target.printNumDate();
    string written = target.printCommaDate();
    string dmy     = target.printDMYDate();
    cout << "--------------------------------------\n";
    cout << numbers << "\n";
    cout << written << "\n";
    cout << dmy << "\n";
    cout << "--------------------------------------\n";
}

/**
 * Context-provision function that assists user in generating a Date
 * object that accepts only the [Day] parameter.
*/
void userDefConst1(){
    int uDay = 0;
    cout << "Testing day-only constructor. \n";
    cout << "Input your chosen Day now. \n";
    cin >> uDay;
    Date dConstruction(uDay);
    massDatePrint(dConstruction);
}

/**
 * Context-provision function that assists user in generating a Date
 * object that accepts both the [Day] and [Month] parameters.
*/
void userDefConst2(){
    int uDay, uMonth = 0;
    cout << "Testing day-and-month constructor. \n";
    cout << "Input your chosen Day and Month now. \n";
    cout << "Day first: \n";
    cin >> uDay;
    cout << "Month second: \n";
    cin >> uMonth;
    Date dmConstruction(uDay,uMonth);
    massDatePrint(dmConstruction);
}

/**
 * Context-provision function that assists user in generating a Date
 * object with the [Day], [Month], and [Year] parameters.
*/
void userDefConst3(){
    int uDay, uMonth = 0;
    int uYear = -1;
    cout << "Testing complete new date constructor. \n";
    cout << "Input your desired Day, Month, and Year now. \n";
    cout << "Day first: \n";
    cin >> uDay;
    cout << "Month second: \n";
    cin >> uMonth;
    cout << "Year last: \n";
    cin >> uYear;
    Date dmyConstruction(uDay,uMonth,uYear);
    massDatePrint(dmyConstruction);
}

/**
 * User-input control loop meant to facilitate verification of continued
 * execution of program.
 * @return 0 or 1 representing cessation or repeat, respectively.
*/
int inputVerify(){
    int choice = 0;

    do{
        cin >> choice;
        if (choice != 0 && choice != 1) {
            cout << "Not a valid input. \n";
        }
    } while (choice != 0 && choice != 1);

    return choice;
}
