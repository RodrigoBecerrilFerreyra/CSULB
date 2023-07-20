/*
* This C++ program generates an array of 5 integers at random 
* that the user attempts to guess.
* CECS 275 - Fall 2021
* @author Ethan Hua
* @author Rodrigo Becerril Ferreyra
* @version 1.12
*
*/

#include <iostream>  // Used for simple I/O
#include <cstdlib>   // Used for pseudorandom number generation functions
#include <ctime>     // Used for seeding pseudorandom number generation

using namespace std;

// Function prototypes
void greeter();
void ranLots(int[],int);
void useLots(int[],int);
void lottoPrint(int[],int,int[],int);
void lottoRead(int[],int,int[],int);

int main(){

    // Initializes both lottery array and user array, as well as sizes.
    // Specifications indicate that the sizes should be 5 elements.
    const int lottoSize = 5;
    int lottery[5] = {0,0,0,0,0};

    const int useSize = 5;
    int user[5] = {0,0,0,0,0};

    greeter();

    ranLots(lottery,lottoSize);

    useLots(user,useSize);

    lottoPrint(lottery,lottoSize,user,useSize);
    
    lottoRead(lottery,lottoSize,user,useSize);

    return 0;

}

/**
 * Text output function that contextualizes the program for the end user.
 * 
*/
void greeter(){

    cout << "***********" << endl;
    cout << endl;
    cout << "Welcome to the Lottery!!" << endl;
    cout << endl;
    cout << "***********" << endl;

}

/** 
 * Pseudorandom number generator used to place numbers into lottery array.
 * Each indexed value MUST be a single-digit according to specifications.
 * @param lotteryList The array in which to save the "randomized" values.
 * @param listSize    The size of the array being used to save the
 *                    pseudorandom values.
 *
*/
void ranLots(int lotteryList[], int listSize){

    // Prepare pseudorandom output for every test independent of machine.
    int seed = time(0);
    srand(seed);

    for(int populate = 0; populate < listSize; populate++){
        lotteryList[populate] = (rand() % (9));
        // Must modulus rand() output by 9 to maintain single-digit int.

        //cout << lotteryList[populate] << endl;
        // Output test line used to print 5 values for array.
    }

}

/** 
 * Function used to prompt inputs from user to populate personal numbers array.
 * Contextualizes desired inputs for end user.
 * Each indexed value MUST be a single-digit according to specifications.
 * @param userList The array that will contain the user's inputted values.
 * @param userSize The size of the aforementioned array.
 *
*/
void useLots(int userList[], int userSize){

    int valid = userSize;
    int newNum = 0;
    int useIndex = 0;

    cout << "Please input positive integers 0 to 9." << endl;
    cout << "Characters are considered a 0 input." << endl;
    cout << "Separate inputs with spaces or new lines." << endl;

    // Continuously prompt for input until array is filled.
    do{
        cout << "You have " << valid << " numbers left to input." << endl;
        cin >> newNum;

        // Number must be a positive single-digit
        if ((newNum >= 0) && (newNum <= 9)) {
            userList[useIndex] = newNum;
            cout << "You have input: " << userList[useIndex] << endl;

            // Loop & array index control, respectively
            valid -= 1;
            useIndex += 1;
        } else if (newNum < 0){
            cout << "Do not enter negative integers. " << endl; 
        } else if (newNum > 9){
            cout << "Integer is too large." << endl;
        } else {
            cout << "Could not recognize input." << endl;
        } // Catch-all case as edge guard against unknown characters.

    }while(valid>0);

}

/** 
 * Function used to print both pseudorandom lottery array and user's input
 * array. Forcibly differentiates print-out by mass dump of dashes at both
 * top of print-out and bottom of print-out.
 * @param first      The pseudorandomized lottery array goes here.
 * @param firstSize  The size of that lottery array is stored here.
 * @param second     The user's input array of numbers goes here.
 * @param secondSize The size of that user input array is stored here.
 *
*/
void lottoPrint(int first[], int firstSize, int second[], int secondSize){

    cout << "--------------------------" << endl;

    cout << "LOTTO: ";
    for(int lots = 0; lots<firstSize; lots++){
        cout << first[lots];
    }

    cout << endl;

    cout << "USER : ";
    for(int useIns = 0; useIns<secondSize; useIns++){
        cout << second[useIns];
    }

    cout << endl;

    cout << "--------------------------" << endl;

}

/** 
 * Function used to compare pseudorandom lottery array and user's input array.
 * Numbers AND indexes must match. Prints out the count of matches found. If 
 * all 5 numbers match, function then outputs a special text print-out.
 * @param master      The array whose values must be matched.
 * @param masterSize  The size of this original array.
 * @param check       The array whose values are to be tested.
 * @param checkSize   The size of this tested array.
 *
*/
void lottoRead(int master[],int masterSize,int check[],int checkSize){

    int correct = 0;

    for(int index = 0; index < masterSize; index++){
        if (master[index] == check[index]) {
            correct++; // Increment counter for every match.
        }
    }

    cout << "You matched " << correct << " digits. " << endl;

    if (correct == checkSize) {
        cout << "You are the grand prize winner!!" << endl;
    }

}
