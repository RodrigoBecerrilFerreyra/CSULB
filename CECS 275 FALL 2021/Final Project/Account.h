/*
 * Copyright (C) Rodrigo Becerril Ferreyra, Ethan Hua 2021
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * Account class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <exception>
#include <fstream>
#include <ostream>

/**
 * The Account class handles subjects such as account number and records
 * such as total money and money lost. The Account class also handles saving
 * all these values in a file.
 */
class Account
{
    public:
// *****************************************************************************
// Exception handling classes
// *****************************************************************************
        /**
         * Class for exception handling of account number in constructor.
         */
        class NumOutOfBounds : public std::exception
        {
            public:
                /**
                 * Initializes the class to hold the expected lower and upper
                 * bounds of the value.
                 * @param errval The value that caused the error.
                 * @param lower The lower bound of the expected value
                 * (inclusive).
                 * @param upper The upper bound of the expected value
                 * (inclusive).
                 */
                NumOutOfBounds(int errval, int lower, int upper);

                int getLowerBounds() const {return lowerbounds;}
                int getUpperBounds() const {return upperbounds;}

                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                int errorvalue;
                int lowerbounds;
                int upperbounds;
        };

        /**
         * Class for exception handling of balance in constructor.
         */
        class NumNegative : public std::exception{};

        /**
         * Class for exception handling of file not existing.
         */
        class FileNotFoundError : public std::exception
        {
            public:
                /**
                 * Sets the name of the file.
                 * @param name The filename.
                 */
                FileNotFoundError(std::string name);

                /**
                 * Builds and returns an error message.
                 * @return An error message.
                 */
                std::string getErrorMessage();
            private:
                std::string filename;
        };

// *****************************************************************************
// constructors
// *****************************************************************************
        /**
         * Default constructor.
         */
        Account();

        /**
         * This overloaded constructor allows the user to set the value for
         * one of the class's members. Uses a known Account Number to 
         * attempt to load value from a .txt file.
         * @param accountNumber The account number of the new account.
         * @throws ParameterOutOfBounds if the account number is not a
         * positive eight-digit number.
         */
        Account(int accountNumber);

        /**
         * This overloaded constructor allows the user to set the value for
         * two of the class's members.
         * @param accountNumber The account number of the new account.
         * @param balance The new account's balance.
         * @throws ParameterOutOfBounds if the account number is not a
         * positive eight-digit number.
         * @throws ParameterOutOfBounds if the balance is 
         */
        Account(int accountNumber, int balance);

// *****************************************************************************
// destructors
// *****************************************************************************

        /**
         * Automatically saves all data when object is destroyed.
         */
        ~Account();

// *****************************************************************************
// load and save functions
// *****************************************************************************

        /**
         * Reads the account data from the file acc_{accountNumber}.txt.
         * @throws FileNotFoundError if the file does not exist.
         */
        void load();

        /**
         * Writes the account data to the file acc_{accountNumber}.txt.
         * Overwrites the file if it exists, and creates a new file if it
         * does not.
         */
        void save();

// *****************************************************************************
// other functions
// *****************************************************************************

        /**
         * Stream extraction operator overload. Extracts the contents of the
         * object (in the same format as the file) and feeds it into the
         * std::ostream operator used to call it. Can be chained.
         */
        friend std::ostream& operator<< (std::ostream& os, const Account& acc);

// *****************************************************************************
// setter and getter functions
// *****************************************************************************

        // setter functions
        /**
         * Use this function to input the results of a game of blackjack.
         * @param moneyWon The amount of money won from the game.
         * @param moneyLost The amount of money lost from the game.
         */
        void inputGameResults(double moneyWon, double moneyLost);

        /**
         * Attempts to set accountNumber independently of other members. 
         * Use to update empty Account to attempt loading file.
         * @param accSet  Attempted overwrite of accountNumber.
         * @throws ParameterOutOfBounds if the account number is not a
         * positive eight-digit number.
         */
        void setAccountNumber(unsigned int accSet);

        // getter functions
        /**
         * Getter function for accountNumber.
         * @return accountNumber
         */
        int getAccountNumber() const {return accountNumber;}

        /**
         * Getter function for gamesPlayed.
         * @return gamesPlayed
         */
        int getGamesPlayed() const {return gamesPlayed;}

        /**
         * Getter function for balance.
         * @return balance
         */
        double getBalance() const {return balance;}

        /**
         * Getter function for amountWon.
         * @return amountWon
         */
        double getAmountWon() const {return amountWon;}

        /**
         * Getter function for amountLost.
         * @return amountLost
         */
        double getAmountLost() const {return amountLost;}

    private:
        int accountNumber;
        int gamesPlayed;
        double balance;
        double amountWon;
        double amountLost;

        /**
         * Gets the filename of the filename according to the account number.
         * @return The filename of the file where the account is saved.
         */
        std::string getFilename();
};

#endif//ACCOUNT_H
