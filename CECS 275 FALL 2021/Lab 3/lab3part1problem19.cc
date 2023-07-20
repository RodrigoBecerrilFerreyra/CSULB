/*
* This C++ program computes and displays a user's hospital charges based on
* their status as an inpatient or an outpatient. This version generates the
* printout in an external .txt file.
* CECS 275 - Fall 2021
* @author Ethan Hua
* @author Rodrigo Becerril Ferreyra
* @version 2.4
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Function prototypes
void greeter();
int patientType();
double configuration(int);
double billGenerator(int,double,double,double);
double billGenerator(double,double);

int main(){

    greeter();
    
    int choice = patientType();

    configuration(choice);

    return 0;
}

/**
* Text output function that contextualizes the program for the end user.
* Defines "inpatient" and "outpatient" to minimize ambiguity.
* 
*/
void greeter(){

    cout << "------------------------" << endl;

    cout << "This program calculates a patient's total fees accrued" << endl;
    cout << "over the course of their hospital attendance." << endl;

    cout << endl;

    cout << "An inpatient is defined as one that required stay at the" << endl;
    cout << "hospital for at least one full day or overnight." << endl;

    cout << endl;

    cout << "An outpatient is defined as a patient or individual" << endl;
    cout << "that did not require at least an overnight stay." << endl;

    cout << endl;

    cout << "Was this patient admitted as an inpatient or as an outpatient?" 
    << endl;
}

/** 
* Verifies user's patient identity by repeatedly accepting and comparing input
* until an understood string is passed to the function.
*
* @return Patient's identity as inpatient or outpatient as int 0 or 1
*/
int patientType(){

    bool unverified = true;    // loop control variable
    int validatedPatient = 0;  // patient default cause at 0
    string patient = "";       // initialized empty string input

    cout << "Input the admission type now." << endl;

    // Continuous loop used to verify & prompt user for correct
    // patient identification string.
    do{
        cin >> patient; // user inputs patient type here

        if(patient == "Inpatient" || patient == "inpatient"){
            cout << "You have input: inpatient." << endl;
            cout << "**************************" << endl;
            unverified = false; // disable verification loop
            validatedPatient = 0;
        }
        else if(patient == "Outpatient" || patient == "outpatient"){
            cout << "You have input: outpatient." << endl;
            cout << "**************************" << endl;
            unverified = false; // disable verification loop
            validatedPatient = 1;
        }
        else{ // catch-all for typos, integer input, or other irregularities
            cout<<"Could not identify patient type." << endl;
            cout<<"Please enter either \"Inpatient\" or \"Outpatient\"." 
            << endl;
        }

    }while(unverified);

    return validatedPatient;
}

/**
* Uses integer input representation of patient type to prompt fee
* data collection from user, then prints bill. 
* Function continually accepts input for a list of parameters based on 
* patient status until all inputs confirmed valid, and finishes by printing 
* an itemized list of fees as well as total bill using user's submissions.
* @param patientData integer 0 or 1 used to denote inpatient or outpatient 
* @return sum total of all user's fees
*/
double configuration(int patientData){

    ofstream outFile; // ready outgoing file storage for Q19

    // fee storage variables
    int duration = 0;            // length of stay (inpatients)
    double hospitalFee = 0;      // rate per day of stay (inpatients)
    double dailyCharges = 0;     // product of duration and hospitalFee
    double medicalFee = 0;       // fees for medication
    double servicesFee = 0;      // fees for staff service
    double finalCharges = 0;     // total of all above fees

    // verification loop control variables
    bool validDays = false;
    bool validHospitalFee = false;
    bool validMedicalFee = false;
    bool validServicesFee = false;

    outFile.open("bill.txt"); // uses "bill.txt" in directory to store summary

    if(patientData == 0){ // inpatient case

        do{
            cout << "Input the number of days admitted: ";
            cin >> duration;
            if(duration > 0){ // inpatient stays for at least 1 day
                validDays = true; // disable verification loop
            }
            else{
                cout << "Not a valid day count." << endl;
            } // Continues prompting input until greater than 0
        }while(validDays == false);

        do{
            cout << "Input the daily rate charged (in USD): $";
            cin >> hospitalFee;
            if(hospitalFee >= 0){ // user pays no money or any value above 0
                validHospitalFee = true; // disable verification loop
            }
            else{
                cout << "Not a valid fee." << endl;
            } // Continues prompting input until greater than or equal to 0
        }while(validHospitalFee == false);

        do{
            cout << "Input the medication charges (in USD): $";
            cin >> medicalFee;
            if(medicalFee >= 0){ // user pays no money or any value above 0
                validMedicalFee = true; // disable verification loop
            }
            else{
                cout << "Not a valid fee." << endl;
            } // Continues prompting input until greater than or equal to 0
        }while(validMedicalFee == false);

        do{
            cout << "Input the services charges (in USD): $";
            cin >> servicesFee;
            if(servicesFee >= 0){ // user pays no money or any value above 0
                validServicesFee = true; // disable verification loop
            }
            else{
                cout << "Not a valid fee." << endl;
            } // Continues prompting input until greater than or equal to 0
        }while(validServicesFee == false);

        // calculates total of daily fees for printout
        dailyCharges = (duration*hospitalFee);
        
        // overloaded function call --> case 1
        finalCharges = billGenerator(duration,hospitalFee,medicalFee,servicesFee);

        // format top of outgoing saved file
        outFile << "Services Rendered" << endl;
        outFile << "*****************" << endl;
        
        if(duration == 1){ // specific formatting for only 1 day
            outFile << "Patient was admitted for " << duration 
            << "day." << endl;
        }
        else{ // "days" plural for all other possible numbers
            outFile << "Patient was admitted for " << duration 
            << " days." << endl;
        }

        outFile << "Daily Rate...............: $" << setprecision(2) <<
        fixed << hospitalFee << endl;
        outFile << "    Daily Total..........: $" << setprecision(2) <<
        fixed << dailyCharges << endl;
        outFile << "Medication Fees..........: $" << setprecision(2) <<
        fixed << medicalFee << endl;
        outFile << "Services Fees............: $" << setprecision(2) << 
        fixed << servicesFee << endl;

        outFile << endl;
        outFile << "Final charges incurred...: $" << setprecision(2) << 
        fixed << finalCharges;

        outFile.close();

        return finalCharges;
    }

    else if(patientData == 1){ // outpatient case

        do{
            cout << "Input the medication charges (in USD): $";
            cin >> medicalFee;
            if(medicalFee >= 0){ // user pays no money or any value above 0
                validMedicalFee = true; // disable verification loop
            }
            else{
                cout << "Not a valid fee." << endl;
            } // Continues prompting input until greater than or equal to 0
        }while(validMedicalFee == false);

        do{
            cout << "Input the services charges (in USD): $";
            cin >> servicesFee;
            if(servicesFee >= 0){ // user pays no money or any value above 0
                validServicesFee = true; // disable verification loop
            }
            else{
                cout << "Not a valid fee." << endl;
            } // Continues prompting input until greater than or equal to 0
        }while(validServicesFee == false);

        // overloaded function call --> case 2
        finalCharges = billGenerator(medicalFee,servicesFee);

        // format top of outgoing saved file
        outFile << "Services Rendered" << endl;
        outFile << "*****************" << endl;

        outFile << "Medication Fees..........: $" << setprecision(2) << 
        fixed << medicalFee << endl;
        outFile << "Services Fees............: $" << setprecision(2) << 
        fixed << servicesFee << endl;

        outFile << endl;
        outFile << "Final charges incurred...: $" << setprecision(2) 
        << fixed << finalCharges;

        outFile.close();

        return finalCharges;
    }

    else{ // catch-all case for unexpected parameter value
        cout << "Error. Could not generate bill." << endl;
        finalCharges = 0;
        return finalCharges;
    }
}

/**
* Calculates sum of fees input by user, assuming they are an inpatient. 
* Overloaded function case 1 defined by problem 15. 
* Differentiated by int parameter in this definition. 
*
* @param days duration of stay in hospital
* @param rate fee paid per day spent in hospital
* @param medication aggregate cost of medications used on patient
* @param services fees for hospital equipment upkeep/use
*/ 
double billGenerator(int days, double rate, double medication, double services){
    // total daily fee generated by days multiplied by rate
    // then summed with flat fees
    double totalCharges = (days * rate) + medication + services;
    return totalCharges;
}

/**
* Calculates sum of fees input by user, assuming they are an outpatient. 
* Overloaded function case 2 defined by problem 15. 
* Differentiated by use of only 2 parameters. 
*
* @param medication aggregate cost of medications used on patient
* @param services fees for hospital equipment upkeep/use
*/ 
double billGenerator(double medication, double services){
    // simple sum of two parameters
    double totalCharges = medication + services;
    return totalCharges;
}