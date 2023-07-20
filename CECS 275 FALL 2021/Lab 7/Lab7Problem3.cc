/**
 * Program to manage student quiz scores using structs
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 2
 */

#include <iostream>
#include <string>
#include <iomanip>

#define COURSEARRAYSIZE 10

// Course definition
struct Course
{
    std::string ID;
    std::string firstName;
    std::string lastName;
    int *quizScores;
};

// function definitions
std::string getInitial(const Course &);
std::string getID(const Course &);
std::string getName(const Course &);
int* getQuizScores(const Course &);
void toString(const Course &);
double getQuizAverage(const Course &);
void updateQuizScore(Course &, int, int);
void changeName(Course &, std::string);

int main()
{
    // instantiate and populate Course course
    Course course = {"A107VER", "Veronica", "Sanchez", new int[COURSEARRAYSIZE]};
    for(int i = 1; i <= COURSEARRAYSIZE; ++i)
    {
        updateQuizScore(course, i, 90 + i);
    }

    std::cout << "The initials are " << getInitial(course) << ".\n";
    std::cout << "The ID is "        << getID(course)      << ".\n";
    std::cout << "The name is "      << getName(course)    << ".\n";

    // print all the quiz scores
    std::cout << "The quiz scores are ";
    int *scores = getQuizScores(course);
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
        std::cout << scores[i] << " ";
    }

    std::cout << "\nThe following is a summary of the course:\n";
    toString(course);

    changeName(course, "Veronica Fuentes");
    std::cout << "The name was changed to "
        << course.firstName << " " << course.lastName << ".\n";

    delete [] course.quizScores; course.quizScores = nullptr;
    delete [] scores; scores = nullptr;
    return 0;
}

/**
 * Gets the initials of the course.
 * @param c The course to get the initials from.
 * @return The initials (first letter of first and last names).
 */
std::string getInitial(const Course &c)
{
    char initials[3] = {c.firstName[0], c.lastName[0], '\0'};
    std::string retstr(initials); // convert to std::string
    return retstr;
}

/**
 * Getter method to return ID.
 * @param c The course to get the ID from.
 * @return The ID.
 */
std::string getID(const Course &c)
{
    return c.ID;
}

/**
 * Concatenates the first and last names of the Course.
 * @param c The course to get the name from.
 * @return The first and last names concatinated.
 */
std::string getName(const Course &c)
{
    std::string retstr = c.firstName + " " + c.lastName;
    return retstr;
}

/**
 * Getter method to return quiz scores.
 * @param c The course to get the quiz scores from.
 * @return The pointer to the first int in quizScores.
 */
int* getQuizScores(const Course &c)
{
    return c.quizScores;
}

/**
 * Displays the contents of the course in a neat manner.
 * @param c The course to display.
 */
void toString(const Course &c)
{
    std::cout << "ID"         << std::setw(18) << ": " << c.ID        << "\n";
    std::cout << "First Name" << std::setw(10) << ": " << c.firstName << "\n";
    std::cout << "Last Name"  << std::setw(11) << ": " << c.lastName  << "\n";
    std::cout << "Quiz Score" << std::setw(10) << ": ";
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
       std::cout << c.quizScores[i] << " ";
    }

    // specifications say 2 places after decimal point
    std::cout << "\nAverage Quiz Score: "
        << std::fixed << std::setprecision(2) << getQuizAverage(c) << "\n";
}

/**
 * Returns the average of the quiz scores in the Course.
 * @param c The course to get the average from.
 * @return The average of all the quiz scores.
 */
double getQuizAverage(const Course &c)
{
    double total = 0.0;
    for(int i = 0; i < COURSEARRAYSIZE; ++i)
    {
        total += c.quizScores[i];
    }
    return total / COURSEARRAYSIZE;
}

/**
 * Updates a quiz score in specified Course.
 * @param c The Course to modify.
 * @param quizNumber Which quiz score to change (one-indexed).
 * @param quizScore The new score that will replace the old one.
 */
void updateQuizScore(Course &c, int quizNumber, int quizScore)
{
    c.quizScores[quizNumber - 1] = quizScore;
}

/**
 * Replaces both first name and last name of the Course 
 * with a single string.
 * @param c The Course to modify.
 * @param newName The new name. The first name is the substring before the
 * first whitespace, and the last name is after that.
 */
void changeName(Course &c, std::string newName)
{
    int spacePosition = newName.find(" ");
    if(spacePosition == std::string::npos) {return;}  // if no space was found

    // substring up to but excluding the space
    c.firstName = newName.substr(0, spacePosition);
    // substring starting from the character after the space
    c.lastName = newName.substr(spacePosition + 1);
}
