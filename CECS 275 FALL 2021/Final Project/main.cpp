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
 * Main function file; game logic goes here.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "CardList.h"
#include "Player.h"

int main()
{
    int useroption; bool splitflag;
    int hand1val, hand2val, dealval;
    double userBet;
    int validBet = 0;
    // build deck
    CardList deck;
    // create 52 cards
    for(int i = 1; i <= 13; ++i)
    {
        deck.createCard(CardList::CLUBS, i);
        deck.createCard(CardList::DIAMONDS, i);
        deck.createCard(CardList::HEARTS, i);
        deck.createCard(CardList::SPADES, i);
    }

    std::cout << "************************************************\n";
    std::cout << "Welcome to Ethan's and Rodrigo's Blackjack game.\n";
    std::cout << "************************************************\n";

    std::cout << "Please enter your ID number (if you do not have one, input"
        << " any number): ";
    std::cin >> useroption;

    Player player(useroption);
    Player dealer;

    std::cout << "************************************************\n";
    player.showAccount();
    std::cout << "************************************************\n";

    // do-while loops until user decides to exit program
    do
    {
        splitflag = false;
        deck.shuffle();
        std::cout << "Please input your bet now.\n";
        std::cin >> userBet;
        try
        {
            player.setBet(userBet);
        }
        catch(Player::InsufficientBalance &e)
        {
            std::cerr << e.getErrorMessage() << "\n";
            do 
            {
                std::cout << "Please input a valid bet.\n";
                std::cin >> userBet;
                try
                {
                    player.setBet(userBet);
                    validBet = 1;
                }
                catch(Player::InsufficientBalance &e)
                {
                    std::cerr << e.getErrorMessage() << "\n";
                }
                catch(Player::NoBet &e)
                {
                    std::cerr << e.getErrorMessage() << "\n";
                }
            } while(validBet == 0);
        }
        catch(Player::NoBet &e)
        {
            std::cerr << e.getErrorMessage() << "\n";
            do 
            {
                std::cout << "Please input a valid bet.\n";
                std::cin >> userBet;
                try
                {
                    player.setBet(userBet);
                    validBet = 1;
                }
                catch(Player::InsufficientBalance &e)
                {
                    std::cerr << e.getErrorMessage() << "\n";
                }
                catch(Player::NoBet &e)
                {
                    std::cerr << e.getErrorMessage() << "\n";
                }
            } while(validBet == 0);
        }
        std::cout << "************************************************\n";

        // deals two cards to each
        std::cout << "Dealer's cards:\n";
        dealer.drawCard(0, deck, 2);
        std::cout << "************************************************\n";
        std::cout << "Your cards:\n";
        player.drawCard(0, deck, 2);

        if(player.checkMoney() >= player.getBet()*2)
        {
            if(player.splitCondition())
            {
                std::cout << "You received two of the same card. Would you like to"
                    << " split? 0 for no, 1 for yes: ";
                std::cin >> useroption;
                if(useroption)
                {
                    splitflag = true;
                    try
                    {
                        player.setBet();
                    }
                    catch(Player::InsufficientBalance &e)
                    {
                        std::cerr << e.getErrorMessage() << "\n";
                    }
                    player.split();
                }
            }
        }

        std::cout << "************************************************\n";
        // hand 1
        std::cout << "Now playing: hand 1.\n";
        std::cout << player.outputPrettyWrapper(0) << "\n";
        std::cout << "Value: " << player.getValue(0) << "\n";
        while(true)
        {
            if(player.getValue(0) >= 21)
                break;

            std::cout << "Enter 0 for hit, 1 for stand: ";
            std::cin >> useroption;
            if(useroption == 0) // hit
            {
                player.drawCard(0, deck, 1);
                std::cout << "Value: " << player.getValue(0) << "\n";
            }
            else // stand
                break;
        }

        // hand 2
        if(splitflag)
        {
            std::cout << "Now playing: hand 2.\n";
            std::cout << player.outputPrettyWrapper(1) << "\n";
            std::cout << "Value: " << player.getValue(1) << "\n";
            while(true)
            {
                if(player.getValue(1) >= 21)
                    break;

                std::cout << "Enter 0 for hit, 1 for stand: ";
                std::cin >> useroption;
                if(useroption == 0) // hit
                {
                    player.drawCard(1, deck, 1);
                    std::cout << "Value: " << player.getValue(1) << "\n";
                }
                else // stand
                    break;
            }
        }

        hand1val = player.getValue(0);
        hand2val = player.getValue(1);
        dealval  = dealer.getValue(0);

        std::cout << "Dealer's hand:\n";
        std::cout << dealer.outputPrettyWrapper(0) << "\n";
        std::cout << "Value: " << dealval << "\n";

        std::cout << "Results for Game 1:\n";
        if(hand1val > 21)
        {
            std::cout << "Bust! You lose.\n";
            player.updateAccount(0,userBet);
            std::cout << "************************************************\n";
            player.showAccount();
        }
        else if(hand1val > dealval)
        {
            std::cout << "You win!\n";
            player.updateAccount(userBet*2,0);
            std::cout << "************************************************\n";
            player.showAccount();
        }
        else if(hand1val < dealval)
        {
            std::cout << "You lose.\n";
            player.updateAccount(0,userBet);
            std::cout << "************************************************\n";
            player.showAccount();
        }
        else // tie
        {
            std::cout << "It's a tie!\n";
            player.updateAccount(0,userBet/2);
            std::cout << "************************************************\n";
            player.showAccount();
        }
        if(splitflag)
        {
            std::cout << "************************************************\n";
            std::cout << "Results for Game 2:\n";
            if(hand2val > 21)
            {
                std::cout << "Bust! You lose.\n";
                player.updateAccount(0,userBet);
                std::cout << "************************************************\n";
                player.showAccount();
            }
            else if(hand2val > dealval)
            {
                std::cout << "You win!\n";
                player.updateAccount(userBet*2,0);
                std::cout << "************************************************\n";
                player.showAccount();
            }
            else if(hand2val < dealval)
            {
                std::cout << "You lose.\n";
                player.updateAccount(0,userBet);
                std::cout << "************************************************\n";
                player.showAccount();
            }
            else // tie
            {
                std::cout << "It's a tie!\n";
                player.updateAccount(0,userBet/2);
                std::cout << "************************************************\n";
                player.showAccount();
            }
        }
        player.returnCards(deck,0);
        player.returnCards(deck,1);
        dealer.returnCards(deck,0);
        std::cout << "************************************************\n";
        std::cout << "Enter 0 to quit or 1 to continue: ";
        std::cin >> useroption;
    } while(useroption);

    return 0;
}
