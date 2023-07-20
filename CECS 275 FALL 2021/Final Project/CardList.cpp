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
 * CardList class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <chrono>    // for std::chrono
#include <string>    // for std::string and std::to_string
#include <ostream>   // for std::ostream
#include "CardList.h"

// *****************************************************************************
// node functions
// *****************************************************************************

CardList::Card* CardList::pop()
{
    // do nothing if list is empty
    if(!headPtr)
        return nullptr;

    // else pop the head and return it
    Card* oldhead = headPtr;
    headPtr = headPtr->nextCard;
    --numCards;
    return oldhead;
}

void CardList::addCard(Card* cardPtr)
{
    cardPtr->nextCard = headPtr;
    headPtr = cardPtr;
    ++numCards;
}

bool CardList::transferTo(CardList &other, unsigned int amount)
{
    if(!headPtr)
        return false;

    Card* cardBeingTransferred = nullptr;

    // do not remove more cards than there are in the CardList
    if(amount > numCards) amount = numCards;

    // this loop transfers the number of cards requested
    for(int i = 0; i < amount; ++i)
    {
        cardBeingTransferred = pop();
        if(!cardBeingTransferred) // if the list is empty for any reason
            return false; // this prevents nullptr being added to other
        other.addCard(cardBeingTransferred);
    }

    return true;
}

bool CardList::createCard(CardList::listOfSuits cardSuit,unsigned int cardValue)
{
    // the function does not do anything if the value is out of range
    if(cardValue > 13 || cardValue < 1)
        return false;

    // next, look through the list and see if any cards match requested card
    Card* traversePtr = headPtr;
    while(traversePtr) // iterate until end of list
    {
        // if there is a match, return false
        if(traversePtr->suit == cardSuit && traversePtr->value == cardValue)
            return false;
        traversePtr = traversePtr->nextCard;
    }

    // if there is no match, create a new card and add it
    traversePtr = new Card;
    traversePtr->suit = cardSuit;
    traversePtr->value = cardValue;
    addCard(traversePtr);

    return true;
}

unsigned int CardList::countCards(CardList::listOfSuits suitToFind) const
{
    unsigned int count = 0;
    Card* traversePtr = headPtr;

    // loop until traversePtr == nullptr
    while(traversePtr)
    {
        if(traversePtr->suit == suitToFind)
            ++count;
        traversePtr = traversePtr->nextCard;
    }

    return count;
}

unsigned int CardList::countCards(unsigned int valueToFind) const
{
    unsigned int count = 0;
    Card* traversePtr = headPtr;

    // loop until traversePtr == nullptr
    while(traversePtr)
    {
        if(traversePtr->value == valueToFind)
            ++count;
        traversePtr = traversePtr->nextCard;
    }

    return count;
}

unsigned int CardList::listValue() const
{
    unsigned int total = 0;
    Card* traversePtr = headPtr;

    // loop until traversePtr == nullptr
    while(traversePtr)
    {
        // Truncate Jack/Queen/King
        if (traversePtr->value > 10)
            total += 10;
        else 
            total += traversePtr->value;

        traversePtr = traversePtr->nextCard;
    }

    return total;
}

bool CardList::compareFirstTwoCards()
{
    if(numCards < 2) return false;

    if(headPtr->value == (headPtr->nextCard)->value)
        return true;
    return false;
}

CardList::CardList(const CardList &copyFromMe)
{
    headPtr = nullptr; numCards = 0;
    *this = copyFromMe;
}

CardList& CardList::operator= (const CardList &copyFromMe)
{
    deleteAllCards();
    const Card* otherPtr = copyFromMe.headPtr;
    Card* currPtr = nullptr, *prevPtr = nullptr;

    // while otherPtr != nullptr
    // Note that this is skipped if the other list is empty.
    while(otherPtr)
    {
        // create new card and copy values
        currPtr = new Card; ++numCards;
        currPtr->value = otherPtr->value;
        currPtr->suit = otherPtr->suit;
        currPtr->nextCard = nullptr;

        // if headPtr == nullptr then have currPtr be the start of the list
        if(!headPtr)
            headPtr = currPtr;
        // if prevPtr != null then link the previous card to the new card
        if(prevPtr)
            prevPtr->nextCard = currPtr;

        // make sure we can link this card to the next card on the
        // next iteration
        prevPtr = currPtr;

        // move to next card in other list
        otherPtr = otherPtr->nextCard;
    }

    return *this;
}

CardList::~CardList()
{
    deleteAllCards();
}

void CardList::deleteAllCards()
{
    Card* currPtr = headPtr;
    Card* nextPtr = nullptr;

    // loop until currPtr is at the end of the list
    while(currPtr)
    {
        nextPtr = currPtr->nextCard;
        delete currPtr; --numCards;
        currPtr = nextPtr;
    }
    headPtr = nullptr;
}

// *****************************************************************************
// display functions
// *****************************************************************************

std::string CardList::outputBasic() const
{
    std::string outstring = "VALUE | SUIT\n------|---------\n";

    // traverse through the list and add data to the string
    Card* traversePtr = headPtr;
    while(traversePtr) // while not nullptr
    {
        // pick the value
        switch(traversePtr->value)
        {
            case 1: // ace
                outstring += "A    ";
                break;
            case 11: // j
                outstring += "J    ";
                break;
            case 12: // q
                outstring += "Q    ";
                break;
            case 13: // k
                outstring += "K    ";
                break;
            case 10:
                outstring += "10   ";
                break;
            default: // anything else in between
                outstring += std::to_string(traversePtr->value) + "    ";
                break;
        }
        outstring += " | ";

        // pick the suit
        switch(traversePtr->suit)
        {
            case CardList::CLUBS:
                outstring += "CLUBS";
                break;
            case CardList::DIAMONDS:
                outstring += "DIAMONDS";
                break;
            case CardList::HEARTS:
                outstring += "HEARTS";
                break;
            case CardList::SPADES:
                outstring += "SPADES";
        }

        outstring += "\n";
        traversePtr = traversePtr->nextCard;
    }

    return outstring;
}

std::string CardList::outputPretty(unsigned int amount) const
{
    // The way this works is that the function must print one line at a time.
    // Each piece is one line. The function makes sure to only print 10
    // cards at a time, then moves to the next line of cards.

    // do not print more cards than there are
    if(amount > numCards) amount = numCards;

    int oldAmount, i;
    std::string outstring;
    Card* traversePtr = headPtr;
    Card* oldPtr = nullptr;

    // loop until there are no more cards to print
    // Note that this is skipped if there are no Cards in the list.
    while(amount > 0)
    {
        oldAmount = amount;
        oldPtr = traversePtr;
        // print the top lines
        // run 10 times (the amount of cards that fit on one line) or
        // until the amount of cards is reached
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "------- ";
            --amount;
        }
        outstring += "\n";

        // print the first line with the value
        amount = oldAmount;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "|";
            switch(traversePtr->value)
            {
                case 13: // K
                    outstring += "K    ";
                    break;
                case 12: // Q
                    outstring += "Q    ";
                    break;
                case 11: // J
                    outstring += "J    ";
                    break;
                case 10: // 10 needs a special case because it's 2 digits long
                    outstring += "10   ";
                    break;
                case 1: // A
                    outstring += "A    ";
                    break;
                default:
                    outstring += std::to_string(traversePtr->value) + "    ";
            }
            outstring += "| ";
            --amount;
            traversePtr = traversePtr->nextCard;
        }
        outstring += "\n";

        // empty line
        amount = oldAmount;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "|     | ";
            --amount;
        }
        outstring += "\n";

        // print suit info
        amount = oldAmount;
        traversePtr = oldPtr;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "|";

            switch(traversePtr->suit)
            {
                case CardList::CLUBS:
                    outstring += "CLUBS";
                    break;
                case CardList::DIAMONDS:
                    outstring += "DIAMD";
                    break;
                case CardList::HEARTS:
                    outstring += "HEART";
                    break;
                case CardList::SPADES:
                    outstring += "SPADE";
                    break;
            }

            traversePtr = traversePtr->nextCard;
            --amount;
            outstring += "| ";
        }
        outstring += "\n";

        // empty line
        amount = oldAmount;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "|     | ";
            --amount;
        }
        outstring += "\n";

        // print value info again
        amount = oldAmount;
        traversePtr = oldPtr;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "|";

            switch(traversePtr->value)
            {
                case 13: // K
                    outstring += "    K";
                    break;
                case 12: // Q
                    outstring += "    Q";
                    break;
                case 11: // J
                    outstring += "    J";
                    break;
                case 10: // 10 needs a special case because it's 2 digits long
                    outstring += "   10";
                    break;
                case 1: // A
                    outstring += "    A";
                    break;
                default:
                    outstring += "    " + std::to_string(traversePtr->value);
                    break;
            }

            traversePtr = traversePtr->nextCard;
            --amount;
            outstring += "| ";
        }
        outstring += "\n";

        amount = oldAmount;
        for(i = 0; i < 10 && amount > 0; ++i)
        {
            outstring += "------- ";
            --amount;
        }
        outstring += "\n";
    }

    return outstring;
}

std::string CardList::outputBlackjack() const
{
    std::string outstring;
    // if the list is not empty
    if(headPtr)
    {
        // print top of card
        outstring += "------- -------\n";

        // print value
        switch(headPtr->value)
        {
            case 13: // K
                outstring += "|K    | ";
                break;
            case 12: // Q
                outstring += "|Q    | ";
                break;
            case 11: // J
                outstring += "|J    | ";
                break;
            case 10: // 10 has two digits so it needs a special case
                outstring += "|10   | ";
                break;
            case 1: // A
                outstring += "|A    | ";
                break;
            default:
                outstring += "|" + std::to_string(headPtr->value) +"    | ";
                break;
        }
        outstring += "|     |\n";

        // print empty line
        outstring += "|     | |     |\n";

        // print suit
        switch(headPtr->suit)
        {
            case CardList::CLUBS:
                outstring += "|CLUBS| ";
                break;
            case CardList::DIAMONDS:
                outstring += "|DIAMD| ";
                break;
            case CardList::HEARTS:
                outstring += "|HEART| ";
                break;
            case CardList::SPADES:
                outstring += "|SPADE| ";
                break;
        }
        outstring += "|     |\n";

        // print empty line
        outstring += "|     | |     |\n";

        // print value
        switch(headPtr->value)
        {
            case 13: // K
                outstring += "|    K| ";
                break;
            case 12: // Q
                outstring += "|    Q| ";
                break;
            case 11: // J
                outstring += "|    J| ";
                break;
            case 10: // 10 has two digits so it needs a special case
                outstring += "|   10| ";
                break;
            case 1: // A
                outstring += "|    A| ";
                break;
            default:
                outstring += "|    " + std::to_string(headPtr->value) +"| ";
                break;
        }
        outstring += "|     |\n";

        // print bottom of card
        outstring += "------- -------\n";
    }

    return outstring;
}

std::ostream& operator<< (std::ostream& os, const CardList &list)
{
    os << list.outputBasic();
    return os;
}

// *****************************************************************************
// misc functions
// *****************************************************************************

void CardList::shuffle()
{
    // if list is empty, do nothing
    if(!headPtr)
        return;

    // create an array of all the addresses of all nodes in the list
    int i = 0;
    Card** addressArray = new Card*[numCards];

    // start at head; loop until you reach the end of the list; go to next card
    for(Card* nodePtr = headPtr; nodePtr; nodePtr = nodePtr->nextCard)
        addressArray[i++] = nodePtr;
        // note that the array avoids putting nullptr into the array

    // shuffle the array of addresses
    // shuffle implementation taken from https://stackoverflow.com/a/26682712
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(&addressArray[0], &addressArray[numCards], rng);
    // std::shuffle takes the address of the first element and the address of
    //   the element after the last element. The last element is
    //   addressArray[numCards-1], so the element after it is
    //   addressArray[numCards].

    // re-link all nodes according to the new order of addressArray
    // start from the back and work your way up to the front
    addressArray[numCards-1]->nextCard = nullptr;
    for(i = numCards - 2; i >= 0; --i)
        addressArray[i]->nextCard = addressArray[i+1];
    headPtr = addressArray[0];

    // free array memory
    delete[] addressArray;
}
