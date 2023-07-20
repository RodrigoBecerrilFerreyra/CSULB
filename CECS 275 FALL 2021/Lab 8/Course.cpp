/**
 * Course class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "Course.h"

Course::Course()
{
    quizScores = new int[COURSEARRAYSIZE];
}

Course::Course(std::string ID, std::string firstName, std::string lastName)
: Course()
{
    this->ID = ID;
    this->firstName = firstName;
    this->lastName = lastName;
}

std::string Course::getInitial() const
{
    // define an ASCIIZ string, turn it into an std::string, and return.
    char asciiz[3] = {firstName[0], lastName[0], '\0'};
    std::string cppstr(asciiz);
    return cppstr;
}

std::string Course::getID() const
{
    return ID;
}

std::string Course::getName() const
{
    return firstName + " " + lastName;
}

int* Course::getQuizScores() const
{
    return quizScores;
}

void Course::toString() const
{
    std::cout << "ID"         << std::setw(18) << ": " << ID        << "\n";
    std::cout << "First Name" << std::setw(10) << ": " << firstName << "\n";
    std::cout << "Last Name"  << std::setw(11) << ": " << lastName  << "\n";
    std::cout << "Quiz Score" << std::setw(10) << ": ";
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
       std::cout << quizScores[i] << " ";
    }

    // specifications say 2 places after decimal point
    std::cout << "\nAverage Quiz Score: "
      << std::fixed << std::setprecision(2) << getQuizAverage() << "\n";
}

double Course::getQuizAverage() const
{
    double total = 0.0;
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
        total += quizScores[i];
    }
    return total / COURSEARRAYSIZE;
}

void Course::updateQuizScore(int quizNumber, int quizScore)
{
    if(quizNumber > COURSEARRAYSIZE || quizNumber < 1) {return;}
    quizScores[quizNumber - 1] = quizScore;
}

void Course::changeName(std::string newName)
{
    int spacePosition = newName.find(" ");
    if(spacePosition == std::string::npos) {return;}  // if no space was found

    // substring up to but excluding the space
    firstName = newName.substr(0, spacePosition);
    // substring starting from the character after the space
    lastName = newName.substr(spacePosition + 1);
}

Course::~Course()
{
    delete [] quizScores;
    quizScores = nullptr;
}
