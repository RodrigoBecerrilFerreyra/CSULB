/*
* This C++ program reads numbers from a text file and processes frequencies
* of the values within the file to be printed in a new text file.
* CECS 275 - Fall 2021
* @author Ethan Hua
* @author Rodrigo Becerril Ferreyra
* @version 3.8
*
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(){

    ifstream inFile;
    ofstream outFile;

    int numbers = 1;      // loop control for star printing
    int data;             // data file input storage
    char comma;           // data file "comma" character storage
    double iterCount = 0; // running counter for numbers in file

    // running counters for data occurrences
    int count1 = 0; int count2 = 0; int count3 = 0; int count4 = 0;
    int count5 = 0; int count6 = 0; int count7 = 0; int count8 = 0;
    int count9 = 0; int count10 = 0; int count11 = 0; int count12 = 0;
    int count13 = 0; int count14 = 0; int count15 = 0; int count16 = 0;
    int count17 = 0; int count18 = 0; int count19 = 0; int count20 = 0;
    int count21 = 0; int count22 = 0; int count23 = 0; int count24 = 0;
    int count25 = 0; int count26 = 0; int count27 = 0; int count28 = 0;
    int count29 = 0; int count30 = 0; int count31 = 0; int count32 = 0;
    int count33 = 0; int count34 = 0; int count35 = 0; int count36 = 0;
    int count37 = 0; int count38 = 0; int count39 = 0; int count40 = 0;
    int count41 = 0; int count42 = 0; int count43 = 0; int count44 = 0;
    int count45 = 0; int count46 = 0; int count47 = 0; int count48 = 0;
    int count49 = 0; int count50 = 0;

    // variable used to store value of average of all numbers
    double average;

    inFile.open("data.txt");

    if(inFile){

        cout << "File found." << endl;

        // while loop runs until end of file
        while(inFile >> data){

            // iterCount is the amount of numbers there are in the file.
            iterCount++;

            // cout << data << endl;

            // This switch statement increments the associated counter variable
            // of the number encountered when reading the data.
            switch(data){
                case 1: count1++;
                        break;
                case 2: count2++;
                        break;
                case 3: count3++;
                        break;
                case 4: count4++;
                        break;
                case 5: count5++;
                        break;
                case 6: count6++;
                        break;
                case 7: count7++;
                        break;
                case 8: count8++;
                        break;
                case 9: count9++;
                        break;
                case 10: count10++;
                        break;
                case 11: count11++;
                        break;
                case 12: count12++;
                        break;
                case 13: count13++;
                        break;
                case 14: count14++;
                        break;
                case 15: count15++;
                        break;
                case 16: count16++;
                        break;
                case 17: count17++;
                        break;
                case 18: count18++;
                        break;
                case 19: count19++;
                        break;
                case 20: count20++;
                        break;
                case 21: count21++;
                        break;
                case 22: count22++;
                        break;
                case 23: count23++;
                        break;
                case 24: count24++;
                        break;
                case 25: count25++;
                        break;
                case 26: count26++;
                        break;
                case 27: count27++;
                        break;
                case 28: count28++;
                        break;
                case 29: count29++;
                        break;
                case 30: count30++;
                        break;
                case 31: count31++;
                        break;
                case 32: count32++;
                        break;
                case 33: count33++;
                        break;
                case 34: count34++;
                        break;
                case 35: count35++;
                        break;
                case 36: count36++;
                        break;
                case 37: count37++;
                        break;
                case 38: count38++;
                        break;
                case 39: count39++;
                        break;
                case 40: count40++;
                        break;
                case 41: count41++;
                        break;
                case 42: count42++;
                        break;
                case 43: count43++;
                        break;
                case 44: count44++;
                        break;
                case 45: count45++;
                        break;
                case 46: count46++;
                        break;
                case 47: count47++;
                        break;
                case 48: count48++;
                        break;
                case 49: count49++;
                        break;
                case 50: count50++;
                        break;
                default: {
                    // cout << "Number out of index @ " << iterCount << "." << endl;
                    // cout << "Retracting iteration count." << endl;
                    iterCount -= 1;
                }
            }

            // This is a way to ensure that the next read will read data,
            // not a comma.
            inFile >> comma;
        }

        inFile.close();

        average = (1*count1 + 2*count2 + 3*count3 + 4*count4 + 5*count5 +
                    6*count6 + 7*count7 + 8*count8 + 9*count9 + 10*count10 +
                    11*count11 + 12*count12 + 13*count13 + 14*count14 + 15*count15 +
                    16*count16 + 17*count17 + 18*count18 + 19*count19 + 20*count20 +
                    21*count21 + 22*count22 + 23*count23 + 24*count24 + 25*count25 +
                    26*count26 + 27*count27 + 28*count28 + 29*count29 + 30*count30 +
                    31*count31 + 32*count32 + 33*count33 + 34*count34 + 35*count35 +
                    36*count36 + 37*count37 + 38*count38 + 39*count39 + 40*count40 +
                    41*count41 + 42*count42 + 43*count43 + 44*count44 + 45*count45 +
                    46*count46 + 47*count47 + 48*count48 + 49*count49 + 50*count50)
                    / iterCount;

        outFile.open("frequency.txt");

        // This for loop prints stars equal to the number of occurrences in
        // the data file.
        for(numbers = 1; numbers < 51; numbers++){
            outFile << numbers << ":";
            switch(numbers){
                case 1: {
                    for(int stars = 0; stars < count1; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 2: {
                    for(int stars = 0; stars < count2; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 3: {
                    for(int stars = 0; stars < count3; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 4: {
                    for(int stars = 0; stars < count4; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 5: {
                    for(int stars = 0; stars < count5; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 6: {
                    for(int stars = 0; stars < count6; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 7: {
                    for(int stars = 0; stars < count7; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 8: {
                    for(int stars = 0; stars < count8; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 9: {
                    for(int stars = 0; stars < count9; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 10: {
                    for(int stars = 0; stars < count10; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 11: {
                    for(int stars = 0; stars < count11; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 12: {
                    for(int stars = 0; stars < count12; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 13: {
                    for(int stars = 0; stars < count13; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 14: {
                    for(int stars = 0; stars < count14; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 15: {
                    for(int stars = 0; stars < count15; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 16: {
                    for(int stars = 0; stars < count16; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 17: {
                    for(int stars = 0; stars < count17; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 18: {
                    for(int stars = 0; stars < count18; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 19: {
                    for(int stars = 0; stars < count19; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 20: {
                    for(int stars = 0; stars < count20; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 21: {
                    for(int stars = 0; stars < count21; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 22: {
                    for(int stars = 0; stars < count22; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 23: {
                    for(int stars = 0; stars < count23; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 24: {
                    for(int stars = 0; stars < count24; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 25: {
                    for(int stars = 0; stars < count25; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 26: {
                    for(int stars = 0; stars < count26; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 27: {
                    for(int stars = 0; stars < count27; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 28: {
                    for(int stars = 0; stars < count28; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 29: {
                    for(int stars = 0; stars < count29; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 30: {
                    for(int stars = 0; stars < count30; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 31: {
                    for(int stars = 0; stars < count31; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 32: {
                    for(int stars = 0; stars < count32; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 33: {
                    for(int stars = 0; stars < count33; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 34: {
                    for(int stars = 0; stars < count34; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 35: {
                    for(int stars = 0; stars < count35; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 36: {
                    for(int stars = 0; stars < count36; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 37: {
                    for(int stars = 0; stars < count37; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 38: {
                    for(int stars = 0; stars < count38; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 39: {
                    for(int stars = 0; stars < count39; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 40: {
                    for(int stars = 0; stars < count40; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 41: {
                    for(int stars = 0; stars < count41; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 42: {
                    for(int stars = 0; stars < count42; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 43: {
                    for(int stars = 0; stars < count43; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 44: {
                    for(int stars = 0; stars < count44; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 45: {
                    for(int stars = 0; stars < count45; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 46: {
                    for(int stars = 0; stars < count46; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 47: {
                    for(int stars = 0; stars < count47; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 48: {
                    for(int stars = 0; stars < count48; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 49: {
                    for(int stars = 0; stars < count49; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                case 50: {
                    for(int stars = 0; stars < count50; stars++)
                        outFile << "*";
                    outFile << endl;
                    break;
                }
                default: outFile << "could not find data" << endl;
            }
        }

        // Frequency-finding logic.
        // The first pass finds the highest number of occurrences.
        int highestNumberOfOccurrences = count1;
        highestNumberOfOccurrences = (count2 > highestNumberOfOccurrences) ? count2 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count3 > highestNumberOfOccurrences) ? count3 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count4 > highestNumberOfOccurrences) ? count4 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count5 > highestNumberOfOccurrences) ? count5 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count6 > highestNumberOfOccurrences) ? count6 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count7 > highestNumberOfOccurrences) ? count7 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count8 > highestNumberOfOccurrences) ? count8 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count9 > highestNumberOfOccurrences) ? count9 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count10 > highestNumberOfOccurrences) ? count10 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count11 > highestNumberOfOccurrences) ? count11 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count12 > highestNumberOfOccurrences) ? count12 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count13 > highestNumberOfOccurrences) ? count13 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count14 > highestNumberOfOccurrences) ? count14 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count15 > highestNumberOfOccurrences) ? count15 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count16 > highestNumberOfOccurrences) ? count16 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count17 > highestNumberOfOccurrences) ? count17 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count18 > highestNumberOfOccurrences) ? count18 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count19 > highestNumberOfOccurrences) ? count19 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count20 > highestNumberOfOccurrences) ? count20 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count21 > highestNumberOfOccurrences) ? count21 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count22 > highestNumberOfOccurrences) ? count22 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count23 > highestNumberOfOccurrences) ? count23 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count24 > highestNumberOfOccurrences) ? count24 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count25 > highestNumberOfOccurrences) ? count25 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count26 > highestNumberOfOccurrences) ? count26 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count27 > highestNumberOfOccurrences) ? count27 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count28 > highestNumberOfOccurrences) ? count28 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count29 > highestNumberOfOccurrences) ? count29 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count30 > highestNumberOfOccurrences) ? count30 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count31 > highestNumberOfOccurrences) ? count31 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count32 > highestNumberOfOccurrences) ? count32 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count33 > highestNumberOfOccurrences) ? count33 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count34 > highestNumberOfOccurrences) ? count34 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count35 > highestNumberOfOccurrences) ? count35 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count36 > highestNumberOfOccurrences) ? count36 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count37 > highestNumberOfOccurrences) ? count37 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count38 > highestNumberOfOccurrences) ? count38 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count39 > highestNumberOfOccurrences) ? count39 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count40 > highestNumberOfOccurrences) ? count40 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count41 > highestNumberOfOccurrences) ? count41 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count42 > highestNumberOfOccurrences) ? count42 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count43 > highestNumberOfOccurrences) ? count43 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count44 > highestNumberOfOccurrences) ? count44 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count45 > highestNumberOfOccurrences) ? count45 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count46 > highestNumberOfOccurrences) ? count46 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count47 > highestNumberOfOccurrences) ? count47 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count48 > highestNumberOfOccurrences) ? count48 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count49 > highestNumberOfOccurrences) ? count49 : highestNumberOfOccurrences;
        highestNumberOfOccurrences = (count50 > highestNumberOfOccurrences) ? count50 : highestNumberOfOccurrences;

        //cout << "Highest number of occurrences = " << highestNumberOfOccurrences << endl;

        // The second pass finds how many numbers have this number.
        int numberOfMaxOccurrences = 0;
        if(count1 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count2 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count3 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count4 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count5 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count6 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count7 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count8 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count9 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count10 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count11 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count12 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count13 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count14 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count15 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count16 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count17 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count18 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count19 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count20 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count21 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count22 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count23 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count24 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count25 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count26 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count27 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count28 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count29 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count30 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count31 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count32 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count33 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count34 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count35 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count36 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count37 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count38 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count39 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count40 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count41 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count42 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count43 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count44 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count45 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count46 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count47 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count48 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count49 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;
        if(count50 == highestNumberOfOccurrences)
            ++numberOfMaxOccurrences;

        //cout << "Number of max occurrences = " << numberOfMaxOccurrences << endl;

        bool alreadyPrinted1 = false,
             alreadyPrinted2 = false,
             alreadyPrinted3 = false,
             alreadyPrinted4 = false,
             alreadyPrinted5 = false,
             alreadyPrinted6 = false,
             alreadyPrinted7 = false,
             alreadyPrinted8 = false,
             alreadyPrinted9 = false,
            alreadyPrinted10 = false,
            alreadyPrinted11 = false,
            alreadyPrinted12 = false,
            alreadyPrinted13 = false,
            alreadyPrinted14 = false,
            alreadyPrinted15 = false,
            alreadyPrinted16 = false,
            alreadyPrinted17 = false,
            alreadyPrinted18 = false,
            alreadyPrinted19 = false,
            alreadyPrinted20 = false,
            alreadyPrinted21 = false,
            alreadyPrinted22 = false,
            alreadyPrinted23 = false,
            alreadyPrinted24 = false,
            alreadyPrinted25 = false,
            alreadyPrinted26 = false,
            alreadyPrinted27 = false,
            alreadyPrinted28 = false,
            alreadyPrinted29 = false,
            alreadyPrinted30 = false,
            alreadyPrinted31 = false,
            alreadyPrinted32 = false,
            alreadyPrinted33 = false,
            alreadyPrinted34 = false,
            alreadyPrinted35 = false,
            alreadyPrinted36 = false,
            alreadyPrinted37 = false,
            alreadyPrinted38 = false,
            alreadyPrinted39 = false,
            alreadyPrinted40 = false,
            alreadyPrinted41 = false,
            alreadyPrinted42 = false,
            alreadyPrinted43 = false,
            alreadyPrinted44 = false,
            alreadyPrinted45 = false,
            alreadyPrinted46 = false,
            alreadyPrinted47 = false,
            alreadyPrinted48 = false,
            alreadyPrinted49 = false,
            alreadyPrinted50 = false;

        // From here, it depends on how many numbers
        // are going to be printed out.
        // First, print the common case: at least one number
        // will always be printed out.
        if(count1 == highestNumberOfOccurrences){
            if(!alreadyPrinted1)
            {
                alreadyPrinted1 = true;
                outFile << "#1";
            }
        }
        else if(count2 == highestNumberOfOccurrences){
            if(!alreadyPrinted2)
            {
                alreadyPrinted2 = true;
                outFile << "#2";
            }
        }
        else if(count3 == highestNumberOfOccurrences){
            if(!alreadyPrinted3)
            {
                alreadyPrinted3 = true;
                outFile << "#3";
            }
        }
        else if(count4 == highestNumberOfOccurrences){
            if(!alreadyPrinted4)
            {
                alreadyPrinted4 = true;
                outFile << "#4";
            }
        }
        else if(count5 == highestNumberOfOccurrences){
            if(!alreadyPrinted5)
            {
                alreadyPrinted5 = true;
                outFile << "#5";
            }
        }
        else if(count6 == highestNumberOfOccurrences){
            if(!alreadyPrinted6)
            {
                alreadyPrinted6 = true;
                outFile << "#6";
            }
        }
        else if(count7 == highestNumberOfOccurrences){
            if(!alreadyPrinted7)
            {
                alreadyPrinted7 = true;
                outFile << "#7";
            }
        }
        else if(count8 == highestNumberOfOccurrences){
            if(!alreadyPrinted8)
            {
                alreadyPrinted8 = true;
                outFile << "#8";
            }
        }
        else if(count9 == highestNumberOfOccurrences){
            if(!alreadyPrinted9)
            {
                alreadyPrinted9 = true;
                outFile << "#9";
            }
        }
        else if(count10 == highestNumberOfOccurrences){
            if(!alreadyPrinted10)
            {
                alreadyPrinted10 = true;
                outFile << "#10";
            }
        }
        else if(count11 == highestNumberOfOccurrences){
            if(!alreadyPrinted11)
            {
                alreadyPrinted11 = true;
                outFile << "#11";
            }
        }
        else if(count12 == highestNumberOfOccurrences){
            if(!alreadyPrinted12)
            {
                alreadyPrinted12 = true;
                outFile << "#12";
            }
        }
        else if(count13 == highestNumberOfOccurrences){
            if(!alreadyPrinted13)
            {
                alreadyPrinted13 = true;
                outFile << "#13";
            }
        }
        else if(count14 == highestNumberOfOccurrences){
            if(!alreadyPrinted14)
            {
                alreadyPrinted14 = true;
                outFile << "#14";
            }
        }
        else if(count15 == highestNumberOfOccurrences){
            if(!alreadyPrinted15)
            {
                alreadyPrinted15 = true;
                outFile << "#15";
            }
        }
        else if(count16 == highestNumberOfOccurrences){
            if(!alreadyPrinted16)
            {
                alreadyPrinted16 = true;
                outFile << "#16";
            }
        }
        else if(count17 == highestNumberOfOccurrences){
            if(!alreadyPrinted17)
            {
                alreadyPrinted17 = true;
                outFile << "#17";
            }
        }
        else if(count18 == highestNumberOfOccurrences){
            if(!alreadyPrinted18)
            {
                alreadyPrinted18 = true;
                outFile << "#18";
            }
        }
        else if(count19 == highestNumberOfOccurrences){
            if(!alreadyPrinted19)
            {
                alreadyPrinted19 = true;
                outFile << "#19";
            }
        }
        else if(count20 == highestNumberOfOccurrences){
            if(!alreadyPrinted20)
            {
                alreadyPrinted20 = true;
                outFile << "#20";
            }
        }
        else if(count21 == highestNumberOfOccurrences){
            if(!alreadyPrinted21)
            {
                alreadyPrinted21 = true;
                outFile << "#21";
            }
        }
        else if(count22 == highestNumberOfOccurrences){
            if(!alreadyPrinted22)
            {
                alreadyPrinted22 = true;
                outFile << "#22";
            }
        }
        else if(count23 == highestNumberOfOccurrences){
            if(!alreadyPrinted23)
            {
                alreadyPrinted23 = true;
                outFile << "#23";
            }
        }
        else if(count24 == highestNumberOfOccurrences){
            if(!alreadyPrinted24)
            {
                alreadyPrinted24 = true;
                outFile << "#24";
            }
        }
        else if(count25 == highestNumberOfOccurrences){
            if(!alreadyPrinted25)
            {
                alreadyPrinted25 = true;
                outFile << "#25";
            }
        }
        else if(count26 == highestNumberOfOccurrences){
            if(!alreadyPrinted26)
            {
                alreadyPrinted26 = true;
                outFile << "#26";
            }
        }
        else if(count27 == highestNumberOfOccurrences){
            if(!alreadyPrinted27)
            {
                alreadyPrinted27 = true;
                outFile << "#27";
            }
        }
        else if(count28 == highestNumberOfOccurrences){
            if(!alreadyPrinted28)
            {
                alreadyPrinted28 = true;
                outFile << "#28";
            }
        }
        else if(count29 == highestNumberOfOccurrences){
            if(!alreadyPrinted29)
            {
                alreadyPrinted29 = true;
                outFile << "#29";
            }
        }
        else if(count30 == highestNumberOfOccurrences){
            if(!alreadyPrinted30)
            {
                alreadyPrinted30 = true;
                outFile << "#30";
            }
        }
        else if(count31 == highestNumberOfOccurrences){
            if(!alreadyPrinted31)
            {
                alreadyPrinted31 = true;
                outFile << "#31";
            }
        }
        else if(count32 == highestNumberOfOccurrences){
            if(!alreadyPrinted32)
            {
                alreadyPrinted32 = true;
                outFile << "#32";
            }
        }
        else if(count33 == highestNumberOfOccurrences){
            if(!alreadyPrinted33)
            {
                alreadyPrinted33 = true;
                outFile << "#33";
            }
        }
        else if(count34 == highestNumberOfOccurrences){
            if(!alreadyPrinted34)
            {
                alreadyPrinted34 = true;
                outFile << "#34";
            }
        }
        else if(count35 == highestNumberOfOccurrences){
            if(!alreadyPrinted35)
            {
                alreadyPrinted35 = true;
                outFile << "#35";
            }
        }
        else if(count36 == highestNumberOfOccurrences){
            if(!alreadyPrinted36)
            {
                alreadyPrinted36 = true;
                outFile << "#36";
            }
        }
        else if(count37 == highestNumberOfOccurrences){
            if(!alreadyPrinted37)
            {
                alreadyPrinted37 = true;
                outFile << "#37";
            }
        }
        else if(count38 == highestNumberOfOccurrences){
            if(!alreadyPrinted38)
            {
                alreadyPrinted38 = true;
                outFile << "#38";
            }
        }
        else if(count39 == highestNumberOfOccurrences){
            if(!alreadyPrinted39)
            {
                alreadyPrinted39 = true;
                outFile << "#39";
            }
        }
        else if(count40 == highestNumberOfOccurrences){
            if(!alreadyPrinted40)
            {
                alreadyPrinted40 = true;
                outFile << "#40";
            }
        }
        else if(count41 == highestNumberOfOccurrences){
            if(!alreadyPrinted41)
            {
                alreadyPrinted41 = true;
                outFile << "#41";
            }
        }
        else if(count42 == highestNumberOfOccurrences){
            if(!alreadyPrinted42)
            {
                alreadyPrinted42 = true;
                outFile << "#42";
            }
        }
        else if(count43 == highestNumberOfOccurrences){
            if(!alreadyPrinted43)
            {
                alreadyPrinted43 = true;
                outFile << "#43";
            }
        }
        else if(count44 == highestNumberOfOccurrences){
            if(!alreadyPrinted44)
            {
                alreadyPrinted44 = true;
                outFile << "#44";
            }
        }
        else if(count45 == highestNumberOfOccurrences){
            if(!alreadyPrinted45)
            {
                alreadyPrinted45 = true;
                outFile << "#45";
            }
        }
        else if(count46 == highestNumberOfOccurrences){
            if(!alreadyPrinted46)
            {
                alreadyPrinted46 = true;
                outFile << "#46";
            }
        }
        else if(count47 == highestNumberOfOccurrences){
            if(!alreadyPrinted47)
            {
                alreadyPrinted47 = true;
                outFile << "#47";
            }
        }
        else if(count48 == highestNumberOfOccurrences){
            if(!alreadyPrinted48)
            {
                alreadyPrinted48 = true;
                outFile << "#48";
            }
        }
        else if(count49 == highestNumberOfOccurrences){
            if(!alreadyPrinted49)
            {
                alreadyPrinted49 = true;
                outFile << "#49";
            }
        }
        else if(count50 == highestNumberOfOccurrences){
            if(!alreadyPrinted50)
            {
                alreadyPrinted50 = true;
                outFile << "#50";
            }
        }
        else{
            outFile << "garbage indication text" << endl;
        }

        if(numberOfMaxOccurrences == 1)
        {
            // Format: #x occurs the most.
            outFile << " occurs the most." << endl;
        }
        else if(numberOfMaxOccurrences == 2)
        {
            // Format: #x and #y occur the most
            outFile << " and ";
            if(count1 == highestNumberOfOccurrences)
                if(!alreadyPrinted1)
                {
                    alreadyPrinted1 = true;
                    outFile << "#1";
                }

            if(count2 == highestNumberOfOccurrences)
                if(!alreadyPrinted2)
                {
                    alreadyPrinted2 = true;
                    outFile << "#2";
                }

            if(count3 == highestNumberOfOccurrences)
                if(!alreadyPrinted3)
                {
                    alreadyPrinted3 = true;
                    outFile << "#3";
                }

            if(count4 == highestNumberOfOccurrences)
                if(!alreadyPrinted4)
                {
                    alreadyPrinted4 = true;
                    outFile << "#4";
                }

            if(count5 == highestNumberOfOccurrences)
                if(!alreadyPrinted5)
                {
                    alreadyPrinted5 = true;
                    outFile << "#5";
                }

            if(count6 == highestNumberOfOccurrences)
                if(!alreadyPrinted6)
                {
                    alreadyPrinted6 = true;
                    outFile << "#6";
                }

            if(count7 == highestNumberOfOccurrences)
                if(!alreadyPrinted7)
                {
                    alreadyPrinted7 = true;
                    outFile << "#7";
                }

            if(count8 == highestNumberOfOccurrences)
                if(!alreadyPrinted8)
                {
                    alreadyPrinted8 = true;
                    outFile << "#8";
                }

            if(count9 == highestNumberOfOccurrences)
                if(!alreadyPrinted9)
                {
                    alreadyPrinted9 = true;
                    outFile << "#9";
                }

            if(count10 == highestNumberOfOccurrences)
                if(!alreadyPrinted10)
                {
                    alreadyPrinted10 = true;
                    outFile << "#10";
                }

            if(count11 == highestNumberOfOccurrences)
                if(!alreadyPrinted11)
                {
                    alreadyPrinted11 = true;
                    outFile << "#11";
                }

            if(count12 == highestNumberOfOccurrences)
                if(!alreadyPrinted12)
                {
                    alreadyPrinted12 = true;
                    outFile << "#12";
                }

            if(count13 == highestNumberOfOccurrences)
                if(!alreadyPrinted13)
                {
                    alreadyPrinted13 = true;
                    outFile << "#13";
                }

            if(count14 == highestNumberOfOccurrences)
                if(!alreadyPrinted14)
                {
                    alreadyPrinted14 = true;
                    outFile << "#14";
                }

            if(count15 == highestNumberOfOccurrences)
                if(!alreadyPrinted15)
                {
                    alreadyPrinted15 = true;
                    outFile << "#15";
                }

            if(count16 == highestNumberOfOccurrences)
                if(!alreadyPrinted16)
                {
                    alreadyPrinted16 = true;
                    outFile << "#16";
                }

            if(count17 == highestNumberOfOccurrences)
                if(!alreadyPrinted17)
                {
                    alreadyPrinted17 = true;
                    outFile << "#17";
                }

            if(count18 == highestNumberOfOccurrences)
                if(!alreadyPrinted18)
                {
                    alreadyPrinted18 = true;
                    outFile << "#18";
                }

            if(count19 == highestNumberOfOccurrences)
                if(!alreadyPrinted19)
                {
                    alreadyPrinted19 = true;
                    outFile << "#19";
                }

            if(count20 == highestNumberOfOccurrences)
                if(!alreadyPrinted20)
                {
                    alreadyPrinted20 = true;
                    outFile << "#20";
                }

            if(count21 == highestNumberOfOccurrences)
                if(!alreadyPrinted21)
                {
                    alreadyPrinted21 = true;
                    outFile << "#21";
                }

            if(count22 == highestNumberOfOccurrences)
                if(!alreadyPrinted22)
                {
                    alreadyPrinted22 = true;
                    outFile << "#22";
                }

            if(count23 == highestNumberOfOccurrences)
                if(!alreadyPrinted23)
                {
                    alreadyPrinted23 = true;
                    outFile << "#23";
                }

            if(count24 == highestNumberOfOccurrences)
                if(!alreadyPrinted24)
                {
                    alreadyPrinted24 = true;
                    outFile << "#24";
                }

            if(count25 == highestNumberOfOccurrences)
                if(!alreadyPrinted25)
                {
                    alreadyPrinted25 = true;
                    outFile << "#25";
                }

            if(count26 == highestNumberOfOccurrences)
                if(!alreadyPrinted26)
                {
                    alreadyPrinted26 = true;
                    outFile << "#26";
                }

            if(count27 == highestNumberOfOccurrences)
                if(!alreadyPrinted27)
                {
                    alreadyPrinted27 = true;
                    outFile << "#27";
                }

            if(count28 == highestNumberOfOccurrences)
                if(!alreadyPrinted28)
                {
                    alreadyPrinted28 = true;
                    outFile << "#28";
                }

            if(count29 == highestNumberOfOccurrences)
                if(!alreadyPrinted29)
                {
                    alreadyPrinted29 = true;
                    outFile << "#29";
                }

            if(count30 == highestNumberOfOccurrences)
                if(!alreadyPrinted30)
                {
                    alreadyPrinted30 = true;
                    outFile << "#30";
                }

            if(count31 == highestNumberOfOccurrences)
                if(!alreadyPrinted31)
                {
                    alreadyPrinted31 = true;
                    outFile << "#31";
                }

            if(count32 == highestNumberOfOccurrences)
                if(!alreadyPrinted32)
                {
                    alreadyPrinted32 = true;
                    outFile << "#32";
                }

            if(count33 == highestNumberOfOccurrences)
                if(!alreadyPrinted33)
                {
                    alreadyPrinted33 = true;
                    outFile << "#33";
                }

            if(count34 == highestNumberOfOccurrences)
                if(!alreadyPrinted34)
                {
                    alreadyPrinted34 = true;
                    outFile << "#34";
                }

            if(count35 == highestNumberOfOccurrences)
                if(!alreadyPrinted35)
                {
                    alreadyPrinted35 = true;
                    outFile << "#35";
                }

            if(count36 == highestNumberOfOccurrences)
                if(!alreadyPrinted36)
                {
                    alreadyPrinted36 = true;
                    outFile << "#36";
                }

            if(count37 == highestNumberOfOccurrences)
                if(!alreadyPrinted37)
                {
                    alreadyPrinted37 = true;
                    outFile << "#37";
                }

            if(count38 == highestNumberOfOccurrences)
                if(!alreadyPrinted38)
                {
                    alreadyPrinted38 = true;
                    outFile << "#38";
                }

            if(count39 == highestNumberOfOccurrences)
                if(!alreadyPrinted39)
                {
                    alreadyPrinted39 = true;
                    outFile << "#39";
                }

            if(count40 == highestNumberOfOccurrences)
                if(!alreadyPrinted40)
                {
                    alreadyPrinted40 = true;
                    outFile << "#40";
                }

            if(count41 == highestNumberOfOccurrences)
                if(!alreadyPrinted41)
                {
                    alreadyPrinted41 = true;
                    outFile << "#41";
                }

            if(count42 == highestNumberOfOccurrences)
                if(!alreadyPrinted42)
                {
                    alreadyPrinted42 = true;
                    outFile << "#42";
                }

            if(count43 == highestNumberOfOccurrences)
                if(!alreadyPrinted43)
                {
                    alreadyPrinted43 = true;
                    outFile << "#43";
                }

            if(count44 == highestNumberOfOccurrences)
                if(!alreadyPrinted44)
                {
                    alreadyPrinted44 = true;
                    outFile << "#44";
                }

            if(count45 == highestNumberOfOccurrences)
                if(!alreadyPrinted45)
                {
                    alreadyPrinted45 = true;
                    outFile << "#45";
                }

            if(count46 == highestNumberOfOccurrences)
                if(!alreadyPrinted46)
                {
                    alreadyPrinted46 = true;
                    outFile << "#46";
                }

            if(count47 == highestNumberOfOccurrences)
                if(!alreadyPrinted47)
                {
                    alreadyPrinted47 = true;
                    outFile << "#47";
                }

            if(count48 == highestNumberOfOccurrences)
                if(!alreadyPrinted48)
                {
                    alreadyPrinted48 = true;
                    outFile << "#48";
                }

            if(count49 == highestNumberOfOccurrences)
                if(!alreadyPrinted49)
                {
                    alreadyPrinted49 = true;
                    outFile << "#49";
                }

            if(count50 == highestNumberOfOccurrences)
                if(!alreadyPrinted50)
                {
                    alreadyPrinted50 = true;
                    outFile << "#50";
                }

            outFile << " occur the most." << endl;
        }
        else // if numberOfMaxOccurrences >= 3
        {
            // Format: #x, #y, and #z occur the most.
            for(int i = 0; i < numberOfMaxOccurrences - 1; i++)
            // -1 because the first one is already printed.
            {
                outFile << ", ";

                // The last iteration needs "and"
                if(i == numberOfMaxOccurrences - 2)
                    outFile << "and ";

                if(count1 == highestNumberOfOccurrences)
                    if(!alreadyPrinted1)
                    {
                        alreadyPrinted1 = true;
                        outFile << "#1";
                        continue;
                    }

                if(count2 == highestNumberOfOccurrences)
                    if(!alreadyPrinted2)
                    {
                        alreadyPrinted2 = true;
                        outFile << "#2";
                        continue;
                    }

                if(count3 == highestNumberOfOccurrences)
                    if(!alreadyPrinted3)
                    {
                        alreadyPrinted3 = true;
                        outFile << "#3";
                        continue;
                    }

                if(count4 == highestNumberOfOccurrences)
                    if(!alreadyPrinted4)
                    {
                        alreadyPrinted4 = true;
                        outFile << "#4";
                        continue;
                    }

                if(count5 == highestNumberOfOccurrences)
                    if(!alreadyPrinted5)
                    {
                        alreadyPrinted5 = true;
                        outFile << "#5";
                        continue;
                    }

                if(count6 == highestNumberOfOccurrences)
                    if(!alreadyPrinted6)
                    {
                        alreadyPrinted6 = true;
                        outFile << "#6";
                        continue;
                    }

                if(count7 == highestNumberOfOccurrences)
                    if(!alreadyPrinted7)
                    {
                        alreadyPrinted7 = true;
                        outFile << "#7";
                        continue;
                    }

                if(count8 == highestNumberOfOccurrences)
                    if(!alreadyPrinted8)
                    {
                        alreadyPrinted8 = true;
                        outFile << "#8";
                        continue;
                    }

                if(count9 == highestNumberOfOccurrences)
                    if(!alreadyPrinted9)
                    {
                        alreadyPrinted9 = true;
                        outFile << "#9";
                        continue;
                    }

                if(count10 == highestNumberOfOccurrences)
                    if(!alreadyPrinted10)
                    {
                        alreadyPrinted10 = true;
                        outFile << "#10";
                        continue;
                    }

                if(count11 == highestNumberOfOccurrences)
                    if(!alreadyPrinted11)
                    {
                        alreadyPrinted11 = true;
                        outFile << "#11";
                        continue;
                    }

                if(count12 == highestNumberOfOccurrences)
                    if(!alreadyPrinted12)
                    {
                        alreadyPrinted12 = true;
                        outFile << "#12";
                        continue;
                    }

                if(count13 == highestNumberOfOccurrences)
                    if(!alreadyPrinted13)
                    {
                        alreadyPrinted13 = true;
                        outFile << "#13";
                        continue;
                    }

                if(count14 == highestNumberOfOccurrences)
                    if(!alreadyPrinted14)
                    {
                        alreadyPrinted14 = true;
                        outFile << "#14";
                        continue;
                    }

                if(count15 == highestNumberOfOccurrences)
                    if(!alreadyPrinted15)
                    {
                        alreadyPrinted15 = true;
                        outFile << "#15";
                        continue;
                    }

                if(count16 == highestNumberOfOccurrences)
                    if(!alreadyPrinted16)
                    {
                        alreadyPrinted16 = true;
                        outFile << "#16";
                        continue;
                    }

                if(count17 == highestNumberOfOccurrences)
                    if(!alreadyPrinted17)
                    {
                        alreadyPrinted17 = true;
                        outFile << "#17";
                        continue;
                    }

                if(count18 == highestNumberOfOccurrences)
                    if(!alreadyPrinted18)
                    {
                        alreadyPrinted18 = true;
                        outFile << "#18";
                        continue;
                    }

                if(count19 == highestNumberOfOccurrences)
                    if(!alreadyPrinted19)
                    {
                        alreadyPrinted19 = true;
                        outFile << "#19";
                        continue;
                    }

                if(count20 == highestNumberOfOccurrences)
                    if(!alreadyPrinted20)
                    {
                        alreadyPrinted20 = true;
                        outFile << "#20";
                        continue;
                    }

                if(count21 == highestNumberOfOccurrences)
                    if(!alreadyPrinted21)
                    {
                        alreadyPrinted21 = true;
                        outFile << "#21";
                        continue;
                    }

                if(count22 == highestNumberOfOccurrences)
                    if(!alreadyPrinted22)
                    {
                        alreadyPrinted22 = true;
                        outFile << "#22";
                        continue;
                    }

                if(count23 == highestNumberOfOccurrences)
                    if(!alreadyPrinted23)
                    {
                        alreadyPrinted23 = true;
                        outFile << "#23";
                        continue;
                    }

                if(count24 == highestNumberOfOccurrences)
                    if(!alreadyPrinted24)
                    {
                        alreadyPrinted24 = true;
                        outFile << "#24";
                        continue;
                    }

                if(count25 == highestNumberOfOccurrences)
                    if(!alreadyPrinted25)
                    {
                        alreadyPrinted25 = true;
                        outFile << "#25";
                        continue;
                    }

                if(count26 == highestNumberOfOccurrences)
                    if(!alreadyPrinted26)
                    {
                        alreadyPrinted26 = true;
                        outFile << "#26";
                        continue;
                    }

                if(count27 == highestNumberOfOccurrences)
                    if(!alreadyPrinted27)
                    {
                        alreadyPrinted27 = true;
                        outFile << "#27";
                        continue;
                    }

                if(count28 == highestNumberOfOccurrences)
                    if(!alreadyPrinted28)
                    {
                        alreadyPrinted28 = true;
                        outFile << "#28";
                        continue;
                    }

                if(count29 == highestNumberOfOccurrences)
                    if(!alreadyPrinted29)
                    {
                        alreadyPrinted29 = true;
                        outFile << "#29";
                        continue;
                    }

                if(count30 == highestNumberOfOccurrences)
                    if(!alreadyPrinted30)
                    {
                        alreadyPrinted30 = true;
                        outFile << "#30";
                        continue;
                    }

                if(count31 == highestNumberOfOccurrences)
                    if(!alreadyPrinted31)
                    {
                        alreadyPrinted31 = true;
                        outFile << "#31";
                        continue;
                    }

                if(count32 == highestNumberOfOccurrences)
                    if(!alreadyPrinted32)
                    {
                        alreadyPrinted32 = true;
                        outFile << "#32";
                        continue;
                    }

                if(count33 == highestNumberOfOccurrences)
                    if(!alreadyPrinted33)
                    {
                        alreadyPrinted33 = true;
                        outFile << "#33";
                        continue;
                    }

                if(count34 == highestNumberOfOccurrences)
                    if(!alreadyPrinted34)
                    {
                        alreadyPrinted34 = true;
                        outFile << "#34";
                        continue;
                    }

                if(count35 == highestNumberOfOccurrences)
                    if(!alreadyPrinted35)
                    {
                        alreadyPrinted35 = true;
                        outFile << "#35";
                        continue;
                    }

                if(count36 == highestNumberOfOccurrences)
                    if(!alreadyPrinted36)
                    {
                        alreadyPrinted36 = true;
                        outFile << "#36";
                        continue;
                    }

                if(count37 == highestNumberOfOccurrences)
                    if(!alreadyPrinted37)
                    {
                        alreadyPrinted37 = true;
                        outFile << "#37";
                        continue;
                    }

                if(count38 == highestNumberOfOccurrences)
                    if(!alreadyPrinted38)
                    {
                        alreadyPrinted38 = true;
                        outFile << "#38";
                        continue;
                    }

                if(count39 == highestNumberOfOccurrences)
                    if(!alreadyPrinted39)
                    {
                        alreadyPrinted39 = true;
                        outFile << "#39";
                        continue;
                    }

                if(count40 == highestNumberOfOccurrences)
                    if(!alreadyPrinted40)
                    {
                        alreadyPrinted40 = true;
                        outFile << "#40";
                        continue;
                    }

                if(count41 == highestNumberOfOccurrences)
                    if(!alreadyPrinted41)
                    {
                        alreadyPrinted41 = true;
                        outFile << "#41";
                        continue;
                    }

                if(count42 == highestNumberOfOccurrences)
                    if(!alreadyPrinted42)
                    {
                        alreadyPrinted42 = true;
                        outFile << "#42";
                        continue;
                    }

                if(count43 == highestNumberOfOccurrences)
                    if(!alreadyPrinted43)
                    {
                        alreadyPrinted43 = true;
                        outFile << "#43";
                        continue;
                    }

                if(count44 == highestNumberOfOccurrences)
                    if(!alreadyPrinted44)
                    {
                        alreadyPrinted44 = true;
                        outFile << "#44";
                        continue;
                    }

                if(count45 == highestNumberOfOccurrences)
                    if(!alreadyPrinted45)
                    {
                        alreadyPrinted45 = true;
                        outFile << "#45";
                        continue;
                    }

                if(count46 == highestNumberOfOccurrences)
                    if(!alreadyPrinted46)
                    {
                        alreadyPrinted46 = true;
                        outFile << "#46";
                        continue;
                    }

                if(count47 == highestNumberOfOccurrences)
                    if(!alreadyPrinted47)
                    {
                        alreadyPrinted47 = true;
                        outFile << "#47";
                        continue;
                    }

                if(count48 == highestNumberOfOccurrences)
                    if(!alreadyPrinted48)
                    {
                        alreadyPrinted48 = true;
                        outFile << "#48";
                        continue;
                    }

                if(count49 == highestNumberOfOccurrences)
                    if(!alreadyPrinted49)
                    {
                        alreadyPrinted49 = true;
                        outFile << "#49";
                        continue;
                    }

                if(count50 == highestNumberOfOccurrences)
                    if(!alreadyPrinted50)
                    {
                        alreadyPrinted50 = true;
                        outFile << "#50";
                        continue;
                    }
            }

            outFile << " occur the most." << endl;
        }

        if(iterCount > 1){
            outFile << "There are " << iterCount << " numbers." << endl;
        }
        else{
            outFile << "There is 1 number." << endl;
        }

        outFile << "The average is " << setprecision(2) << fixed << average << "." << endl;

        outFile.close();
    }
    else{
        cout << "Error: Could not find file." << endl;
        cout << "Please ensure the file \"data.txt\" is located in this program's directory." << endl;
    }

    return 0;
}
