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
 * Player class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "CardList.h"
#include "Account.h"
#include <iostream>

/**
 * The Player class is responsible for all operations having to do with a Player
 * in the game of Blackjack: holding one (or two) hands with different values,
 * having an Account, etc.
 */
class Player
{
    public:
// *****************************************************************************
// Exception handling classes
// *****************************************************************************
        /**
         * Class for exception handling of betting more than the playerRef 
         * Account's balance.
         */
        class InsufficientBalance : public std::exception
        {
            public:
                InsufficientBalance(double userBet, double accBal);
                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                double balance;
                double bet;
        };
        /**
         * Class for exception handling of invalid action.
         */
        class NoBet : public std::exception
        {
            public:
                NoBet(double userBet);
                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                double bet;
        };
// *****************************************************************************
// constructors
// *****************************************************************************
        /**
         * Initialization constructor to create a new Player. Defaults to a 
         * "dealer"-type Player, which disables the ability to save or 
         * load an Account.
         */
        Player();

        /**
         * Constructor specific to a "player"-type Player. Similar 
         * implementation to default constructor but specifically 
         * activates ability to set up Account.
         * @param ID  Positive integer to attempt accessing account. 
         * @throws FileNotFound if no text file but valid account. 
         * @throws NumOutOfBounds if player ID not 8-digit positive integer. 
         */
        Player(int ID);

// *****************************************************************************
// destructors
// *****************************************************************************
        /**
         * Deletes dynamically allocated Account pointer.
         */
        ~Player();
// *****************************************************************************
// setter and getter functions
// *****************************************************************************
        /**
         * Overloaded function acepts a user's bet to begin the game.
         * @param newBet  Desired sum to bet for new game.
         * @throws InsufficientBalance if user bets more than account holds.
         */
        void setBet(double newBet);
        /**
         * Overloaded function copies the value of bet1 over to bet2. 
         * Used when splitting.
         * @throws InsufficientBalance if user bets more than account holds.
         */
        void setBet();

        /**
         * Account wrapper function that takes the user's earnings 
         * and updates their associated Account parameters.
         * @param win  How much money was won in the game.
         * @param loss How much money was lost in the game.
         */
        void updateAccount(double win, double loss)
            { playerRef->inputGameResults(win, loss); }

        /**
         * Getter function for hand/value.
         * @param corrVal  The hand to retrieve the value for.
         * @return         Value of the hand.
         */
        int getValue(int corrVal) const;

        /**
         * Getter function for user's initial bet.
         * Used to ensure that the user can split.
         * @return     User's current bet.
         */
        double getBet() const
            { return bet1; }

        /**
         * Getter function for player's account.
         * @return    Account parameters.
         */ 
        Account getAccount() const
            { return *playerRef; }

        /**
         * Outputs the Player object's associated Account.
         */
        void showAccount() const
            { std::cout << *playerRef << "\n"; }

        /**
         * Wrapper function to retrieve the user's current balance in 
         * their account to verify that they are making a legal bet.
         * @return     The user's current balance of funds.
         */
        double checkMoney()
            { return playerRef->getBalance(); }
// *****************************************************************************
// other functions
// *****************************************************************************        
        /**
         * Gives the designated Player's hand the top cards from 
         * another CardList. 
         * @param hand  Player hand to draw cards into. 
         * @param deck  Base CardList to take cards from.
         * @param count How many cards from the target CardList to take.
         */
        void drawCard(int hand, CardList &deck, int count);

        /**
         * Returns the designated Player's hand to a larger pool.
         * @param deck   Card pool to place Player's cards back into. 
         * @param hand   Player's hand to remove cards from.
         */
        void returnCards(CardList &deck, int hand);
        
        /**
         * Wrapper for CardList::compareFirstTwoCards. Only works on hand1.
         * @return True if the first two cards have the same value,
         * false if they do not (or if there are less than two cards).
         */
        bool splitCondition()
            {return hand1.compareFirstTwoCards();}

        /**
         * Wrapper function to update the value of Player's hand. 
         * @param corrVal  Flag used to differentiate which value to update.
         */
        void updateVal(int corrVal);
        
        /**
         * Wrapper for CardList::outputPretty()
         * @param corrVal Flag used to differentiate between the CardLists.
         * @return A formatted string.
         */
        std::string outputPrettyWrapper(int corrVal)
        {
            if(corrVal == 0)
                return hand1.outputPretty();
            return hand2.outputPretty();
        }

        /**
         * Removes one card from hand1 and gives it to hand2.
         * @return True if successful, false otherwise (for example
         * if there are more or less than two cards).
         */
        bool split();

    private:
        CardList hand1, hand2;    // the hands to hold the CardLists
        int value1, value2;       // the values of each hand
        int playerType;           // 0 for "Dealer" or 1 for "Player"
        Account *playerRef;       // Defines Player's statistics
        double bet1, bet2;        // Player's current bets
};

#endif//PLAYER_H
