/*
* This C++ program compares a user's monthly spending to a pre-set
* monthly budget divided into subcategories by use of structs.
* CECS 275 - Fall 2021
* @author Ethan Hua
* @author Rodrigo Becerril Ferreyra
* @version 1.94
*
*/

#include <iostream> // Used for simple I/O
#include <iomanip>  // Used for report formatting

using namespace std;

/* 
"Monthly Budget" struct
Contains information on total spending across 10 different categories.
For use as both user's spending and the proposed budgetary limits.
Inputs are set up as doubles due to spending using cents as well as dollars.
Struct definitions allow multiple fields to be placed on the same line if
they share a type; this was done here to save newline spaces.
*/
struct MonthlyBudget{
    double Housing,Utilities,HoHo,Transit,Food;
    double Medical,Insurance,Enrich,Clothing,Misc;
};

// Function Prototypes
MonthlyBudget getBudget();
void compBudget(const MonthlyBudget&,const MonthlyBudget&);
MonthlyBudget calcBudget(const MonthlyBudget&,const MonthlyBudget&);
void printCost(double);
void headPrint();
double structSums(const MonthlyBudget&,const MonthlyBudget&);

int main(){
    // master "while" loop control for repeated input
    int loop = 1;

    /*
    Initialize two structs for storing expenses.
    "user" will contain inputs from current user.
    "actualBudget" represents the initial budgetary limits as established by
    Chapter 11 Programming Challenges Problem 11.
    */
    MonthlyBudget user;
    MonthlyBudget actualBudget;

    // Initial budgetary values
    actualBudget.Housing = 500; actualBudget.Utilities = 150;
    actualBudget.HoHo = 65; actualBudget.Transit = 50;
    actualBudget.Food = 250; actualBudget.Medical = 30;
    actualBudget.Insurance = 100; actualBudget.Enrich = 150;
    actualBudget.Clothing = 75; actualBudget.Misc = 50;

    // Terminal context messages
    cout << "This program compares user spending to an allotted budget. \n";
    cout << "Please enter personal monthly expenses. \n";

    // main program loop; gets budget from user to use in comparisons
    while (loop) {
        
        // Begin prompting user for input
        user = getBudget();
        // Perform operations on budgets and prepare report
        compBudget(actualBudget,user);

        // Prompt user to run again
        cout << "\n";
        cout << "Begin new budget calculation? ";
        cout << "Enter 0 to exit and 1 to continue. \n";
        cin.clear();

        do{
            cin >> loop;
            if (loop != 0 && loop != 1) {
                cout << "Not a valid input. \n";
            } // Input control/verification
        } while (loop != 0 && loop != 1);

    }

    cout << "Terminating... \n";

    return 0;

}

/**
 * Prompts user to begin filling out a personal "MonthlyBudget"
 * struct that will contain all of their current month's spending
 * across 10 pre-defined categories. Does not verify for/against
 * positive and negative numbers; assumed that a negative input
 * would mean the user saved/gained money relative to category for
 * whatever reason (e.g. renting house, gifted food, tax credit).
 * 
 * @return The stratified budgets struct containing the user's inputs.
*/
MonthlyBudget getBudget(){
    // New struct, used for return
    MonthlyBudget newB;

    // User input prompts
    cout << "Enter housing cost: "; 
    cin >> newB.Housing; cout << "\n"; cin.clear();
    cout << "Enter utilities cost: "; 
    cin >> newB.Utilities; cout << "\n"; cin.clear();
    cout << "Enter household expenses cost: "; 
    cin >> newB.HoHo; cout << "\n"; cin.clear();
    cout << "Enter transportation costs: "; 
    cin >> newB.Transit; cout << "\n"; cin.clear();
    cout << "Enter food costs: "; 
    cin >> newB.Food; cout << "\n"; cin.clear();
    cout << "Enter medical costs: "; 
    cin >> newB.Medical; cout << "\n"; cin.clear();
    cout << "Enter insurance costs: "; 
    cin >> newB.Insurance; cout << "\n"; cin.clear();
    cout << "Enter entertainment costs: "; 
    cin >> newB.Enrich; cout << "\n"; cin.clear();
    cout << "Enter clothing costs: "; 
    cin >> newB.Clothing; cout << "\n"; cin.clear();
    cout << "Enter miscellaneous costs: "; 
    cin >> newB.Misc; cout << "\n"; cin.clear();

    // newB struct is returned to call for storage
    return newB;
}

/**
 * Accepts two MonthlyBudget structs to begin processing for printing.
 * Primarily alls for other functions to do actual math and printing 
 * based on that math; has some basic printouts and summations included.
 * 
 * @param limitB The first term of the equation; intended to represent
 *               the upper limit of spending for the month.
 *               Predefined budget goes here.
 * @param spendB The second term of the equation; intended to represent
 *               the actual spending for the month.
 *               User's input budget goes here.
*/
void compBudget(const MonthlyBudget &limitB,const MonthlyBudget &spendB){
    // Struct used to store individual finalized comparison values
    MonthlyBudget diffs;
    // Calculates differences between first and second submitted budgets
    diffs = calcBudget(limitB, spendB);
    // Report formatting print; does not do anything
    headPrint();
    /* 
    Prints given budget category and the difference between first and second
    values for that category given earlier operands.
    */
    cout << "Housing" << setw(20) << ":"; printCost(diffs.Housing);
    cout << "Utilities" << setw(18) << ":"; printCost(diffs.Utilities);
    cout << "Household Expenses" << setw(9) << ":"; printCost(diffs.HoHo);
    cout << "Transportation" << setw(13) << ":"; printCost(diffs.Transit); 
    cout << "Food" << setw(23) << ":"; printCost(diffs.Food);
    cout << "Medical" << setw(20) << ":"; printCost(diffs.Medical);
    cout << "Insurance" << setw(18) << ":"; printCost(diffs.Insurance);
    cout << "Entertainment" << setw(14) << ":"; printCost(diffs.Enrich);
    cout << "Clothing" << setw(19) << ":"; printCost(diffs.Clothing);
    cout << "Miscellaneous" << setw(14) << ":"; printCost(diffs.Misc);
    // Find value of difference between original budget and actual expenses.
    double finalCheck = structSums(limitB, spendB);
    // Report formatting print; does not do anything
    cout << "============================================= \n";
    /* 
    Reports to the user how much money was left in the overall budget
    or by how much the total spending went over the total budget.
    */
    if (finalCheck > 0) {        // More budget left than spent
        cout << "Remaining Excess" << setw(11) << ":"; printCost(finalCheck);
    } else if (finalCheck < 0) { // Spent more than allocated budget
        cout << "Total Deficit" << setw(14) << ":"; printCost(finalCheck);
    } else if (finalCheck == 0){
        cout << "BUDGET MATCHED SPENDINGS" << setw(3) << ":"; 
        printCost(finalCheck);
    } else {                    // Catch-all generic error statement
        cout << "ERROR: COULD NOT CALCULATE TOTAL OVER/UNDER VALUE. \n";
    }
    return;
}

/**
 * Accepts two MonthlyBudget structs to calculate differences between
 * each struct's respective types.
 * @param pre The first term of the equation; intended to represent
 *            the upper limit of spending for the month.
 *            Predefined budget goes here.
 * @param act The second term of the equation; intended to represent
 *            the actual spending for the month.
 *            User's input budget goes here.
 * @return    Structure containing differences of above operands.
*/
MonthlyBudget calcBudget(const MonthlyBudget &pre,const MonthlyBudget &act){
    // New struct, used for return
    MonthlyBudget fin;

    // Finds differences between [pre] and [act]
    fin.Housing = pre.Housing - act.Housing;
    fin.Utilities = pre.Utilities - act.Utilities;
    fin.HoHo = pre.HoHo - act.HoHo;
    fin.Transit = pre.Transit - act.Transit;
    fin.Food = pre.Food - act.Food;
    fin.Medical = pre.Medical - act.Medical;
    fin.Insurance = pre.Insurance - act.Insurance;
    fin.Enrich = pre.Enrich - act.Enrich;
    fin.Clothing = pre.Clothing - act.Clothing;
    fin.Misc = pre.Misc - act.Misc;

    // fin struct is returned to call for storage
    return fin;
}
/**
 * Dedicated printout function used to format budget report.
 * Stylizes negative and positive values properly relative to USD ($) sign.
 * Notifies reader if budget category was OVER or UNDER limit to the left of
 * the formatted budgetary printout.
 * @param value Input value to be tested for positive/negative and
 *              printout adjustment.
*/
void printCost(double value){
    // Initialize comparison & storage variable
    double positive = 0;
    double negate = -1;

    if (value < positive) { // Negative real number detected
        // Inverse number
        positive = value * negate;
        // Print out formatted negative number
        cout << " [OVER] -$" << setprecision(2) << fixed << positive << "\n";
    } else if (value == positive) { // Value is exactly zero
        // Print out formatted positive number
        cout << " [EVEN] $" << setprecision(2) << fixed << value << "\n";
    } else { // Non-negative real number
        // Print out formatted positive number
        cout << " [UNDER] $" << setprecision(2) << fixed << value << "\n";
    }

    return;
}

/**
 * Dedicated printout function used to format budget report's header.
 * Contains name of "table" and denotes purpose of columns.
*/
void headPrint(){

    // Report formatting print; does not do anything
    cout << "============================================= \n";
    cout << "==========MONTHLY BUDGET USE REPORT========== \n";
    cout << "============================================= \n";
    cout << "CATEGORY" << setw(19) << "|  $ REMAINING \n";
    cout << "============================================= \n";

    return;
}

/**
 * Accepts two MonthlyBudget structs to calculate the finalized
 * difference between the totals of each respective struct's members.
 * @param limit  Struct intended to contain predefined upper spending limit.
 * @param spend  Struct intended to contain user's input spending that month.
 * @return       Double containing difference of two structs' totals.
*/
double structSums(const MonthlyBudget &limit,const MonthlyBudget &spend){
    // Used to store totals of all subcategories
    double sumOfMonth = 0;
    double sumOfLimit = 0;
    double finalSum = 0;

    /*
    Generates sum of all values in each respective struct, then finds the
    difference between the first and the second.
    */
    sumOfLimit = limit.Housing + limit.Utilities + limit.HoHo
                + limit.Transit + limit.Food + limit.Medical
                + limit.Insurance + limit.Enrich + limit.Clothing 
                + limit.Misc;
    sumOfMonth = spend.Housing + spend.Utilities + spend.HoHo
                + spend.Transit + spend.Food + spend.Medical 
                + spend.Insurance + spend.Enrich + spend.Clothing 
                + spend.Misc;
    finalSum = sumOfLimit - sumOfMonth;

    return finalSum;
}
