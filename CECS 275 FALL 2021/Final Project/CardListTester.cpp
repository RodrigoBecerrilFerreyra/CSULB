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
 * CardList class tester file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "CardList.h"

int main()
{
    std::cout << "First, test the createCard function, copy constructor, "
        << "assignment operator, and destructor.\n";
    CardList* smallHand1 = new CardList;
    smallHand1->createCard(CardList::HEARTS, 12);
    smallHand1->createCard(CardList::SPADES, 1);
    CardList smallHand2 = *smallHand1;
    std::cout << "smallHand1 contents:\n" << *smallHand1 << "\n";
    // delete smallHand1 to verify that the contents of smallHand2 do not
    // rely on it
    delete smallHand1; smallHand1 = nullptr;
    std::cout << "smallHand2 contents (should be the same as "
        << "smallHand1 contents):\n" << smallHand2 << "\n";

    // create two card lists
    CardList hand, deck;

    std::cout << "Creating a full deck of cards...\n";
    // create 52 cards and shuffle them
    for(int i = 1; i <= 13; ++i)
    {
        deck.createCard(CardList::CLUBS, i);
        deck.createCard(CardList::DIAMONDS, i);
        deck.createCard(CardList::HEARTS, i);
        deck.createCard(CardList::SPADES, i);
    }
    // attempt to create a card that is already in the deck
    deck.createCard(CardList::SPADES, 1);
    // attempt to create a card with an invalid value
    deck.createCard(CardList::CLUBS, 20);
    std::cout << "The deck contains " << deck.size() << " cards "
        << "(should be 52 cards).\n";

    std::cout << "Here's the deck before shuffling:\n" << deck << "\n";
    deck.shuffle();
    std::cout << "Here's the deck after shuffling:\n" << deck << "\n";

    std::cout << "Dealing two cards from the deck to a player's hand:\n";
    deck.transferTo(hand, 2);
    std::cout << "The deck contains " << deck.size() << " cards.\n";
    std::cout << "The hand contains " << hand.size() << " cards.\n";

    // test output
    std::cout << "Here's the player's hand:\n" << hand.outputPretty() << "\n";
    std::cout << "Dealing 10 more cards to the player's hand:\n";
    deck.transferTo(hand, 10);
    std::cout << "Here's the player's new hand:\n";
    std::cout << hand.outputPretty() << "\n";
    std::cout << "Here's the same information in a different format:\n"
        << hand << "\n";

    // test dealer functionality
    std::cout << "Here's the first card in the player's hand, "
        << "and a blank card:\n" << hand.outputBlackjack();

    return 0;
}
