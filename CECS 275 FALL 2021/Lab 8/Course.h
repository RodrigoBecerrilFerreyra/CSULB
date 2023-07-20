/**
 * Course class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */
#ifndef COURSE_H
#define COURSE_H

#include <string>

// quizScores has 10 elements per specifications
#define COURSEARRAYSIZE 10

class Course
{
public:
    /**
     * Course constructor initializes the dynamically-allocated array.
     */
    Course();

    /**
     * Course constructor that initializes ID and name.
     * Calls Course().
     * @param ID The Course ID.
     * @param firstName The Course first name.
     * @param lastName The Course last name.
     */
    Course(std::string ID, std::string firstName, std::string lastName);
    
    /**
     * Gets the course's initals (the first letter of the first
     * name and the first letter of the last name).
     * @return The Initials of the Course.
     */
    std::string getInitial() const;
    
    /**
     * Gets the ID of the Course.
     * @return The ID of the Course.
     */
    std::string getID() const;
    
    /**
     * Gets the whole (first and last) name of the Course.
     * @return The name of the Course.
     */
    std::string getName() const;
    
    /**
     * Returns a pointer to a dynamically-allocated array of ints.
     * The array always has a length of 10 per specifications.
     * @return A pointer to the first element of an array.
     */
    int* getQuizScores() const;
    
    /**
     * Displays the contents of the course in a neat manner using std::cout.
     */
    void toString() const;
    
    /**
     * Averages the quiz scores in the Course.
     * Average uses arithmetic mean.
     * @return The average of all quiz scores.
     */
    double getQuizAverage() const;
    
    /**
     * Setter function to change a quiz score.
     * @param quizNumber Which quiz you want to update (number from 1 to 10).
     * @param quizScore The score that will replace the old score.
     */
    void updateQuizScore(int quizNumber, int quizScore);
    
    /**
     * Setter function to change the name.
     * @param newName The name that replaces the old name.
     * The first name is defined as the substring from the beginning of newName
     * up to the first space, and the last name is defined as the first
     * character after the space until the end of the newName.
     */
    void changeName(std::string newName);
    
    /**
     * Frees up the space taken by quizScores.
     */
    ~Course();
private:
    std::string ID;
    std::string firstName;
    std::string lastName;
    int *quizScores;
};

#endif // Course.h
