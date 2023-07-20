/**
 * Sort a list of names located in names.txt and print them out
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include <fstream>
#include <vector>

// function prototypes
void selectionSort(std::string[], int);
void selectionSort(std::vector<std::string>&);

int main()
{
    std::vector<std::string> names;
    std::string inData;
    std::ifstream inFile("names.txt"); // open names.txt

    // only proceed if names.txt is open
    if(inFile.is_open())
    {
        // loop through names.txt and store all content in names
        while(inFile >> inData) names.push_back(inData);
        inFile.close();

        // print unsorted list
        std::cout << "Below are the contents of the names.txt file:" << std::endl;
        for(int i = 0; i < names.size(); ++i) std::cout << names[i] << std::endl;

        selectionSort(names);

        // print sorted list
        std::cout << "\nHere is the same list of names, sorted:" << std::endl;
        for(int i = 0; i < names.size(); ++i) std::cout << names[i] << std::endl;
    }
    else std::cout << "Unable to open file \"names.txt\".";
    return 0;
}

/**
 * Sorts the array input in-place (it modifies the original array) 
 * using the selection sort algorithm.  
 * To avoid this behavior, please make a copy of the original array before 
 * calling this function.
 * @param arrayToSort the array to sort
 * @param sizeOfArray the number of elements in the array
*/
void selectionSort(std::string arrayToSort[], int sizeOfArray)
{
    /*
    Basic operation of selection sort: the algorithm goes through
    all elements in the vector to find the smallest one. When it finds it,
    that item is swapped to the front of the vector. The next iteration
    skips this element and continues until all elements are sorted.
    */

    int minIndex; // index of lowest value
    std::string minValue; // the lowest value
    std::string temp; // required for swap

    // it is not necessary to go through the last element
    for (int start = 0; start < (sizeOfArray - 1); start++)
    {
        minIndex = start;
        minValue = arrayToSort[start];

        // index = start + 1 ignores portion of array already sorted
        for (int index = start + 1; index < sizeOfArray; index++)
        {
            // if a new lower value is found...
            if (arrayToSort[index] < minValue)
            {
                // then remember that lowest value and index
                minValue = arrayToSort[index];
                minIndex = index;
            }
        }

        // swaps vecToSort[minIndex] and vecToSort[start]
        // if minIndex == start then no change
        temp = arrayToSort[minIndex];
        arrayToSort[minIndex] = arrayToSort[start];
        arrayToSort[start] = temp;
    }
}

/**
 * Sorts the vector input in-place (it modifies the original vector) 
 * using the selection sort algorithm.  
 * To avoid this behavior, please make a copy of the original vector before 
 * calling this function.
 * @param vecToSort the vector to sort
*/
void selectionSort(std::vector<std::string> &vecToSort)
{
    /*
    Basic operation of selection sort: the algorithm goes through
    all elements in the vector to find the smallest one. When it finds it,
    that item is swapped to the front of the vector. The next iteration
    skips this element and continues until all elements are sorted.
    */

    int minIndex; // the index of the lowest value
    std::string minValue; // the lowest value
    std::string temp; // required for swap

    // it is not necessary to go through the last element
    for (int start = 0; start < (vecToSort.size() - 1); start++)
    {
        minIndex = start;
        minValue = vecToSort[start];

        // index = start + 1 ignores portion of vector already sorted
        for (int index = start + 1; index < vecToSort.size(); index++)
        {
            // if a new lower value is found...
            if (vecToSort[index] < minValue)
            {
                // then remember that lowest value and index
                minValue = vecToSort[index];
                minIndex = index;
            }
        }

        // swaps vecToSort[minIndex] and vecToSort[start]
        // if minIndex == start then no change
        temp = vecToSort[minIndex];
        vecToSort[minIndex] = vecToSort[start];
        vecToSort[start] = temp;
    }
}
