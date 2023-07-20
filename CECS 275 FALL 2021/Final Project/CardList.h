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
 * CardList class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef CARDLIST_H
#define CARDLIST_H

#include <string>
#include <ostream>

/**
 * CardList is a singly-linked list class that can store all of the cards in a
 * standard French 52-card deck. It implements several functions including
 * shuffle, which randomizes the order of the deck.
 */
class CardList
{
    public:
        enum listOfSuits {SPADES, CLUBS, DIAMONDS, HEARTS};

    private:
        struct Card
        {
            listOfSuits suit;
            // note that 1 is A, 11 is J, 12 is Q, and 13 is K
            unsigned int value;
            Card* nextCard;
        };
        Card* headPtr;

        unsigned int numCards;

        /**
         * Adds an existing card to the front of the list. This function does
         * not create a new card. THIS FUNCTION DOES NOT CHECK FOR THE EXISTENCE
         * OF A Card OBJECT THAT IS POINTED TO BY cardPtr!!!
         * This is very important, because many things can go
         * wrong if a random pointer is put into this function.
         * However, if cardPtr is nullptr, nothing is put onto the list.
         * @param cardPtr The pointer to the Card object to add to the list.
         */
        void addCard(Card* cardPtr);

        /**
         * Removes the Card at the top of the list and returns a pointer to it.
         * Note that this function does not destroy the Card nor free the memory
         * taken by it.
         * @return The pointer to the first Card in the list. If the list is
         * empty, return nullptr.
         */
        Card* pop();

    public:
        /**
         * The constructor simply initializes an empty list.
         */
        CardList() {headPtr = nullptr; numCards = 0;}

        /**
         * The copy constructor traverses the list of the original object and
         * creates new nodes that are copies of the original object's nodes.
         * This is to avoid having two objects pointing to the same list.
         * @param copyFromMe The object to be copied from.
        */
       CardList(const CardList &copyFromMe);

        /**
         * Assignment operator overload. Deletes all Cards in the source list
         * and creates new ones that are copies of copyFromMe.
         * @param copyFromMe The object to copy from.
         * @return A reference to itself.
         */
        CardList& operator= (const CardList &copyFromMe);

        /**
         * The destructor deletes all cards in the list and frees all memory.
         */
        ~CardList();

        /**
         * Deletes all cards that are inside the list.
         */
        void deleteAllCards();

        /**
         * Creates a card and adds it to the front of the list. Checks if an
         * identical card exists; if so, no card is created.
         * @param cardSuit The suit of the card (CLUBS, DIAMONDS, HEARTS, or
         * SPADES).
         * @param cardValue The value of the card (between 1 and 13 inclusive).
         * @return True if a card was created, false otherwise. Note that if
         * either of the parameters are out of range.
         */
        bool createCard(enum listOfSuits cardSuit, unsigned int cardValue);

        /**
         * Transfers cards in the card list to another card list. This
         * function simply removes the desired amount of cards in the list that
         * calls this function and transfers them to other. No new cards
         * are created.
         * @param other The list to transfer all cards to.
         * @param amount The number of cards to transfer.
         * @return True if the transfer was successful, false if it was not
         * successful (for example, if there were no cards to transfer to
         * begin with).
         */
        bool transferTo(CardList &other, unsigned int amount);

        /**
         * Transfers all the cards in the list to the CardList other.
         * @param other The CardList to transfer all cards to.
         * @return True if the transfer was successful, false otherwise.
         */
        bool transferTo(CardList &other) {return transferTo(other, numCards);}

        /**
         * Shuffles the list in place.
         */
        void shuffle();

        /**
         * Traverses through the list and counts the number of cards that match
         * the parameter given.
         * @param suitToFind The suit that the function will look for.
         * @return The number of cards that match the description.
         */
        unsigned int countCards(listOfSuits suitToFind) const;

        /**
         * Traverses through the list and counts the number of cards that match
         * the parameter given.
         * @param valueToFind The value that the function will look for.
         * @return The number of cards that match the description.
         */
        unsigned int countCards(unsigned int valueToFind) const;

        /**
         * Calculates the total value of all the cards in the list.
         * @return The sum of the values of the cards in the list.
         */
        unsigned int listValue() const;

        /**
         * Creates and returns a string that has the basic information of
         * all Cards in the List.
         * @return A formatted std::string.
         */
        std::string outputBasic() const;

        /**
         * Creates and returns a string that is nicely formatted to show the
         * cards in the list. Each card will be 7x5 characters in size. Only
         * 10 cards will be able to be printed onto one line; any further cards
         * will be printed on more lines. Note that if the amount parameter
         * is not greater than 0 or the list is empty, the function will return
         * an empty string.
         * @param amount The amount of cards to print out.
         * @return A formatted std::string.
         */
        std::string outputPretty(unsigned int amount) const;

        /**
         * This overloaded function prints out all cards in the list nicely
         * according to the specifications of
         * CardList::outputPretty(unsigned int).
         * @return A formatted std::string/
         */
        std::string outputPretty() const {return outputPretty(numCards);}

        /**
         * Outputs the first card in the list along with a blank card. This
         * function can be used in order to begin a game of Blackjack, which
         * displays one of the dealer's cards and hides the second.
         * @return A formatted std::string. If the list holds no cards,
         * the function returns an empty string.
         */
        std::string outputBlackjack() const;

        /**
         * Stream extraction operator overload that calls CardList::outputBasic
         * and displays the same information.
         * @return The same std::ostream operator that was used to call
         * the function.
         */
        friend std::ostream& operator<<(std::ostream& os, const CardList &list);

        /**
         * Getter function for numCards.
         * @return The length of the list; the amount of cards currently
         * held by the list.
         */
        unsigned int size() const {return numCards;}

        /**
         * Compares the values (not the suits) of the first two cards.
         * @return True if the value of the first two cards are the same,
         * false if they are different (or there are less than two cards).
         */
        bool compareFirstTwoCards();
};

#endif//CARDLIST_H
