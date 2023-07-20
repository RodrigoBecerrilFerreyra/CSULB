/**
 * Course class tester file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include <string>
#include "Course.h"

int main()
{
    // instantiates student
    // allocates 10 spaces for quizzes
    Course student("ABC123", "Veronica", "Langley");

    // initialize quizScores
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
        student.updateQuizScore(i + 1, i + 90.5);
    }

    int* quizlist = student.getQuizScores();
    // test quizlist
    std::cout << "Here are the quiz scores: ";
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
        std::cout << quizlist[i] << " ";
    }
    std::cout << "\n";
    
    // test getID, getName, and getInitial
    std::cout << "The student's name is " << student.getName() << ".\n";
    std::cout << "The student's initials are " << student.getInitial()
        << ".\n";
    std::cout << "The student's ID is " << student.getID() << ".\n";

    // test name change
    student.changeName("Veronica Matsushita");
    std::cout << "The student's new name is " << student.getName() << ".\n";

    // test invalid name change (name should not change)
    student.changeName("Veronica");

    // test getQuizAverage
    std::cout << "This student's quiz average is " << student.getQuizAverage()
        << ".\n";

    std::cout << "Here's a quick summary of this student's statistics:\n";
    student.toString();

    // student destructor automatically called
    return 0;
}
