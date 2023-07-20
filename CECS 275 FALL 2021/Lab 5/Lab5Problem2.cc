/**
 * Asks user for data and calculates the arithmetic mean, median, and mode(s).
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include <vector>

double calculateMean(const int *, int);
double calculateMedian(const int *, int);
std::vector<int> calculateMode(const int *, int);
int* sortArray(const int *, int);

/*
Quick note about the program: I am using many dynamically-allocated arrays
only because the Programming Challenge is asking me to. I would
avoid using them (because you have to delete [] them later) and
instead I would make sure to return a pointer to an array that
already exists in the program.
*/

int main()
{
    // ask how many students were surveyed
    int numStudents;
    while(true)
    {
        std::cout << "Please enter the number of students surveyed: "
                  << std::flush;
        std::cin >> numStudents;

        if(numStudents > 0) break; // does not allow non-positive numbers
        std::cout << "There cannot be zero or a negative amount of students. "
                  << "Please try again.\n";
    }

    // dynamically allocate this array(problem specifications)
    int *moviesWatched = new int[numStudents];

    // ask user to populate array
    int studentID = 0;
    int numMovies;
    while(studentID < numStudents)
    {
        std::cout << "How many movies did Student " << studentID + 1 << " watch? "
                  << std::flush;
        std::cin >> numMovies;

        if(numMovies >= 0) // disallows negative numbers
        {
            *(moviesWatched + studentID) = numMovies;
            ++studentID;
            continue;
        }

        std::cout << "A student cannot watch a negative amount of movies. "
                  << "Please try again.\n";
    }
    
    std::cout << "\nThe following are statistics based on the data you entered:\n";

    // sort array
    int *sortedArray = sortArray(moviesWatched, numStudents);
    delete [] moviesWatched; moviesWatched = nullptr; // not going to need this
    
    double           mean   = calculateMean  (sortedArray, numStudents);
    double           median = calculateMedian(sortedArray, numStudents);
    std::vector<int> mode   = calculateMode  (sortedArray, numStudents);
    delete [] sortedArray; sortedArray = nullptr; // not going to need this

    std::cout << "The arithmetic mean of the data is " << mean << ".\n";
    std::cout << "The median of the data is " << median << ".\n";
    if(mode.size() > 1)
    {
        std::cout << "The modes of the data are ";
        for(int i = 0; i < mode.size(); ++i)
        {
            std::cout << mode[i] << ((i == mode.size() - 1) ? "." : ", ");
            // the above ternary operator is just fancy comma/period handling.

            if(i == mode.size() - 2)
                std::cout << "and ";
        }
    }
    else
    {
        std::cout << "The mode of this data is " << mode[0] << ".";
    }

    return 0;
}

/**
 * Sorts a copy of arrayToSort using the bubble sort algorithm.
 * @param arrayToSort the array to sort
 * @param numOfElements the length of arrayToSort
 * @return a dynamically-allocated int array
*/
int* sortArray(const int *arrayToSort, int numOfElements)
{
    // create a copy of array
    int *copyOfArray = new int[numOfElements];
    for(int i = 0; i < numOfElements; ++i)
    {
        *(copyOfArray + i) = *(arrayToSort + i);
    }

    // sorting algorithm(bubble sort)
    bool swapped;
    do
    {
        // if no swaps are made, break out of loop(array is sorted)
        swapped = false;

        // loops through entire array(minus last element)
        for(int i = 0; i < numOfElements - 1; ++i)
        {
            if(*(copyOfArray + i) > *(copyOfArray + i + 1))
            // if the values are out of order...
            {
                // ...then swap them
                swapped = true;
                *(copyOfArray + i)     = *(copyOfArray + i) + *(copyOfArray + i + 1);
                *(copyOfArray + i + 1) = *(copyOfArray + i) - *(copyOfArray + i + 1);
                *(copyOfArray + i)     = *(copyOfArray + i) - *(copyOfArray + i + 1);
            }
        }
    } while(swapped);
    return copyOfArray;
}

/**
 * Calculates the arithmetic mean (average) of the given array.
 * @param inputArray the array to find the average of
 * @param numOfElements the length of inputArray
 * @return the average of inputArray
*/
double calculateMean(const int *inputArray, int numOfElements)
{
    double total = 0;
    for(int i = 0; i < numOfElements; ++i)
    {
        total += *(inputArray + i);
    }
    return total / numOfElements;
}

/**
 * Calculates the median of the given array. 
 * Assumes that inputArray is already sorted.
 * @param inputArray the array to find the median of
 * @param numOfElements the length of inputArray
 * @return the median of inputArray
*/
double calculateMedian(const int *inputArray, int numOfElements)
{
    // median calculation
    if(numOfElements % 2) // if even
    {
        return *(inputArray +(numOfElements / 2));
    }
    else // if odd
    {
        int valueToTheRight = *(inputArray +(numOfElements / 2));
        int valueToTheLeft  = *(inputArray +(numOfElements / 2) - 1);
        return static_cast<double>(valueToTheLeft + valueToTheRight) / 2;
    }
}

/**
 * Returns a vector of the numbers that 
 * appear the most in inputArray. This function assumes that 
 * inputArray is already sorted.
 * @param inputArray an integer array of values to find the mode for
 * @param numOfElements the length of inputArray
 * @return a vector
*/
std::vector<int> calculateMode(const int *inputArray, int numOfElements)
{
    // Algorithm: go through each unique entry in the array in order to
    // count them (store the count in an array with the number as the index).
    // Then go through the store array to see how often said number pops up.
    // Find the highest frequency. Go through store again, and add to a vector
    // the index of the highest frequencies.
    // Note that an element can be zero or positive, but cannot be negative.

    // find min and max values for copiedArray
    int minval = *(inputArray); int maxval = *(inputArray);
    for(int i = 0; i < numOfElements; ++i)
    {
        if(*(inputArray + i) > maxval)
            maxval = *(inputArray + i);
        if(*(inputArray + i) < minval)
            minval = *(inputArray + i);
    }

    // array has a length of range (example: {2, 3} has a range of
    // (3 - 2 + 1) = 2)
    const int range = maxval - minval + 1;
    int store[range] = {}; // zero-initialized array

    // loop through array and count the instances of each number
    for(int i = 0; i < numOfElements; ++i)
    {
        // add one to the element in store that corresponds to
        // the element in inputArray

        *(store + (*(inputArray + i) - minval)) += 1;
        // the above is equivalent to:      store[inputArray[i] - minval] += 1;
        // the minval offset is necessary so that the values are zero-indexed
        // for example, in {2, 3}, if *(inputArray + i) is 2, then
        // *(inputArray + i) - minval = 0.
    }

    // find the highest (max) number of occurrences in the store array
    int numOccur = *(store);
    for(int i = 0; i < range; ++i)
    {
        if(*(store + i) > numOccur)
            numOccur = *(store + i);
    }

    // find all the numbers that have the same number of occurrences as
    // the highest and push them into a vector
    std::vector<int> modes;
    for(int i = 0; i < range; ++i)
    {
        if(*(store + i) == numOccur)
            modes.push_back(i + minval);
            // minval offset required because i is simply an index;
            // we need to add the minval we subtracted when we first
            // counted the instances of each number.
    }

    return modes;
}
