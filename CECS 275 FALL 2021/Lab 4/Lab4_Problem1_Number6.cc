/**
 * Group of functions implementing the selection sort algorithm (with tests)
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 4
 */

#include <iostream>
#include <vector>

// function prototypes
void selectionSort(std::string[], int);
void selectionSort(std::vector<std::string>&);

int main()
{
    // test on array

    std::string names[] = {"Samantha", "Ashley", "Victoria"};
    int sizeOfNames = sizeof(names)/sizeof(names[0]);

    // prints unsorted names
    std::cout << "Below is a list of names before sorting (array):" << std::endl;
    for(int i = 0; i < sizeOfNames; ++i)
    {
        std::cout << names[i] << std::endl;
    }

    selectionSort(names, sizeOfNames);

    // prints sorted names
    std::cout << "\nBelow is the same list of names after sorting (array):" << std::endl;
    for(int i = 0; i < sizeOfNames; ++i)
    {
        std::cout << names[i] << std::endl;
    }

    // end test
    // ************************************************************************
    std::cout
        << "\n************************************************************************"
        << std::endl;

    // test on vector

    std::vector<std::string> names_vec = {"Veronica", "Elaine", "Ashley"};
    int numberOfNames = names_vec.size();

    // prints unsorted names
    std::cout << "\nBelow is a list of names before sorting (vector):" << std::endl;
    for(int i = 0; i < numberOfNames; ++i)
    {
        std::cout << names_vec[i] << std::endl;
    }

    selectionSort(names_vec);

    // prints sorted names
    std::cout << "\nBelow is the same list of names after sorting (vector):" << std::endl;
    for(int i = 0; i < numberOfNames; ++i)
    {
        std::cout << names_vec[i] << std::endl;
    }

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
