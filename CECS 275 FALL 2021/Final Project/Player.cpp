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
 * Player class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include "CardList.h"
#include "Account.h"
#include "Player.h"
#include <iostream>
#include <string>

Player::InsufficientBalance::InsufficientBalance(double userBet, double accBal)
{
    bet = userBet;
    balance = accBal;
}

std::string Player::InsufficientBalance::getErrorMessage()
{
    return "InsufficientBalance; Player bet " + std::to_string(bet - balance) 
    + " over maximum possible Account balance.\n";
}

Player::NoBet::NoBet(double userBet)
{
    bet = userBet;
}

std::string Player::NoBet::getErrorMessage()
{
    return "Cannot bet $" + std::to_string(bet) + "\n";
}

Player::Player()
{
    value1 = value2 = 0;
    playerType = 0;
    bet1 = 0;
    bet2 = 0;
    playerRef = nullptr;
}

Player::Player(int ID)
{
    playerRef = nullptr;
    value1 = value2 = 0;
    // If ID is a positive value, attempt to load/save account.
    if (ID > 0)
    {
        playerType = ID;
        // Attempt to load account using ID value.
        try
        {
            playerRef = new Account(ID);
        }
        catch(Account::FileNotFoundError &e)
        {
            // File did not already exist, so make a new one.
            std::cerr << e.getErrorMessage() << "\n";
            std::cout << "Generating new account with provided ID.\n";
            playerRef = new Account(ID,1000);
        }
        catch(Account::NumOutOfBounds &e)
        {
            // File input is not valid.
            std::cerr << e.getErrorMessage() << "\n";
            std::cout << "Generating new account with truncated ID.\n";
            playerRef = new Account(ID%99999999,1000);
        }
    } 
    else
    {   
        // Default to playerType of dealer.
        playerType = 0;
    } 
    bet1 = 0;
    bet2 = 0;
}

Player::~Player()
{
  delete playerRef;
  playerRef = nullptr;
}

void Player::setBet(double newBet)
{
    double money = checkMoney();
    if (money < newBet)
        throw Player::InsufficientBalance(newBet,money);
    else if (newBet == 0)
        throw Player::NoBet(newBet);
    else
        bet1 = newBet;
}

int Player::getValue(int corrVal) const
{
    if (corrVal == 0)
        return value1;
    else 
        return value2;
}

void Player::setBet()
{
    // Verify once more that this is a possible bet.
    double money = checkMoney();
    if(money < bet1*2)
        throw Player::InsufficientBalance(bet1,money);
    else
        bet2 = bet1;
}

void Player::drawCard(int hand, CardList &deck, int count)
{
    // sets the hand to hand1 or hand2
    CardList* chosenHand = (hand % 2 == 0) ? &hand1 : &hand2;

    deck.transferTo(*chosenHand, count);
    if (playerType)
        std::cout << chosenHand->outputPretty();
    else
        std::cout << chosenHand->outputBlackjack();
    updateVal(hand % 2);
}

void Player::returnCards(CardList &deck, int hand)
{
    if (hand%2 == 0)
        hand1.transferTo(deck);
    else
        hand2.transferTo(deck);
}

void Player::updateVal(int corrVal)
{
    int numAces = 0;
    // Input is 0, 2, 4, etc. Ideally the input is 0 for hand1.
    if (corrVal % 2 == 0)
    {
        value1 = hand1.listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand1.countCards(1);
        if (numAces)
        {
            value1 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value1 > 21)
            {   
                do {
                    value1 -= 10;
                    numAces--;
                } while (numAces && value1 > 21);
            }
        }
    } else {
        value2 = hand2.listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand2.countCards(1);
        if (numAces)
        {
            value2 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value2 > 21)
            {   
                do {
                    value2 -= 10;
                    numAces--;
                } while (numAces && value2 > 21);
            }
        }
    }
}

bool Player::split()
{
    if(hand1.size() != 2)
        return false;
    hand1.transferTo(hand2, 1);
    updateVal(0);
    updateVal(1);
    return true;
}
