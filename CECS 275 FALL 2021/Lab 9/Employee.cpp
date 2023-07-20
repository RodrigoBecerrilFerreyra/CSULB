/**
 * Employee class implementation file.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1
 */

#include "Employee.h"

/**
 * Default class constructor for a no-parameter object creation. 
 * Loads pre-defined default values into member variables.
 * @return "Employee" object with generic name, ID, and [current-year] date
*/
Employee::Employee(){
    setDefaults();
}

/**
 * Class constructor for a named employee with no other information. 
 * Loads the new name into the corresponding field.
 * @return "Employee" object with custom name and generic ID/hire date.
*/
Employee::Employee(std::string newEmp){
    setDefaults();
    employeeName = newEmp;
}

/**
 * Class constructor for a named employee with a generated unique ID. 
 * Loads the new employee and their ID into the corresponding fields. 
 * @return "Employee" object with custom name, their ID, and generic date.
*/
Employee::Employee(std::string newEmp, int newID){
    setDefaults();
    employeeName = newEmp;
    setNumber(newID);
}

/**
 * Class constructor for a known employee, their ID, and when they were hired.  
 * Completely overwrites generic defaults with provided information.
 * @return "Employee" object containing given name, ID, and hire date.
*/
Employee::Employee(std::string newEmp, int newID, std::string newDate){
    setDefaults();
    employeeName = newEmp;
    setNumber(newID);
    hireDate = newDate;
}

/**
 * Mutator member function that overwrites the object's current name  
 * data with a provided string.
 * @param newEmp Text string containing replacement name
*/
void Employee::setName(std::string newEmp){
    employeeName = newEmp;
}

/**
 * Mutator member function that overwrites the object's current ID  
 * number with the provided int value, provided it is non-negative. 
 * @param newID Replacement ID for overwriting
*/
void Employee::setNumber(int newID){
    if (newID > 0){
        employeeNumber = newID;
    }
}

/**
 * Mutator member function that overwrites the object's currently held  
 * date string with a new string intended to represent the date the 
 * employee was hired.
 * @param newDate Replacement text string containing hiring date
*/
void Employee::setDate(std::string newDate){
    hireDate = newDate;
}

/**
 * Private function used by constructors to quickly default to given 
 * arbitrary values before user's new information is known.
*/
void Employee::setDefaults(){
    employeeName = "John Doe";
    employeeNumber = 123456789;
    hireDate = "January 1, 2021";
}
