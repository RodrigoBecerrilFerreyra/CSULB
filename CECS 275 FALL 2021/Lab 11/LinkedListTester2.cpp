/**
 * LinkedList class tester file.
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include "LinkedList.h"
#include "LinkedList.cpp" // necessary because of the template class

int main()
{
    // create a new linked list
    LinkedList<int> thelist;

    // add a few values to the list
    thelist.insertNode(1);
    thelist.insertNode(2);
    thelist.insertNode(4);
    thelist.insertNode(5);

    int arrayToInsert[] = {8, 9, 10};

    std::cout << "Initial list: \n";

    thelist.displayList();

    std::cout << "Merged list: \n";

    thelist.mergeArray(arrayToInsert,3);

    thelist.displayList();

    int locData = thelist.search(9);

    std::cout << "Found integer 9 at list position " << locData << "\n";

    LinkedList<double> secondList;

    secondList.insertNode(2.814);
    secondList.insertNode(3.452);
    secondList.insertNode(1.363);
    secondList.insertNode(6.356);
    secondList.insertNode(7.824);

    double newInsert[] = {9.241, 7.132, 5.612};

    std::cout << "Initial list: \n";

    secondList.displayList();

    std::cout << "Merged list: \n";

    secondList.mergeArray(newInsert,3);

    secondList.displayList();

    double dataAt = secondList.search(7.824);

    std:: cout << "Found double 7.824 at list position " << dataAt << "\n";
    
    return 0;
}
