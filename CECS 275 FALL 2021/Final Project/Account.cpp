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
 * Account class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <string>
#include <iomanip>
#include <fstream>
#include <ostream>
#include "Account.h"

Account::NumOutOfBounds::NumOutOfBounds(int errval, int lower, int upper)
{
    errorvalue = errval;
    lowerbounds = lower;
    upperbounds = upper;
}

std::string Account::NumOutOfBounds::getErrorMessage()
{
    return "NumOutOfBounds; Value received: " + std::to_string(errorvalue)
      + "; expected value between " + std::to_string(lowerbounds)
      + " and " + std::to_string(upperbounds) + " (inclusive).";
}

Account::FileNotFoundError::FileNotFoundError(std::string name)
{
    filename = name;
}

std::string Account::FileNotFoundError::getErrorMessage()
{
    return "FileNotFoundError; The file " + filename + " could not be found.";
}

Account::Account()
{
    this->accountNumber = 0;
    this->balance = 0;
    this->gamesPlayed = 0;
    this->amountWon = 0;
    this->amountLost = 0;
}

Account::Account(int accountNumber)
{
    // account number must be a positive eight-digit number
    if(accountNumber < 1 || accountNumber > 99999999)
        throw NumOutOfBounds(accountNumber, 1, 99999999);
    this->accountNumber = accountNumber;
    load();
}

Account::Account(int accountNumber, int balance)
{
    // account number must be a positive eight-digit number
    if(accountNumber < 1 || accountNumber > 99999999)
        throw NumOutOfBounds(accountNumber, 1, 99999999);
    
    // balance must be non-negative
    if(balance < 0)
        throw NumNegative();
    
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->gamesPlayed = 0;
    this->amountWon = 0;
    this->amountLost = 0;
    save();
}

void Account::load()
{
    // open file
    std::fstream infile(getFilename().c_str(), std::ios::in);
    if(infile.fail())
        throw FileNotFoundError(getFilename());
    
    // load all values into variables
    std::string lines[5] = {};

    for(int i = 0; i < 5; ++i)
        std::getline(infile, lines[i]);
    
    // cast string into appropriate type
    accountNumber = std::stoi(lines[0].substr(16));
    balance       = std::stod(lines[1].substr(18));
    gamesPlayed   = std::stoi(lines[2].substr(13));
    amountWon     = std::stod(lines[3].substr(19));
    amountLost    = std::stod(lines[4].substr(20));

    infile.close();
}

void Account::save()
{
    // open file
    std::fstream outfile(getFilename().c_str(), std::ios::out);

    // populate file
    outfile << *this << "\n";

    outfile.close();
}

void Account::inputGameResults(double moneyWon, double moneyLost)
{
    ++gamesPlayed;
    amountWon += moneyWon;
    amountLost += moneyLost;
    balance += (moneyWon - moneyLost);
    save();
}

void Account::setAccountNumber(unsigned int accSet)
{
    if(accSet < 1 || accSet > 99999999)
        throw NumOutOfBounds(accSet, 1, 99999999);
    accountNumber = accSet;
}

Account::~Account()
{
    save();
}

std::string Account::getFilename()
{
    // 8-digit account
    int maxNum = 8;
    // Take the current accountNumber's length after casting to string.
    std::string tempAcc = std::to_string(accountNumber);
    int str_length = tempAcc.length();
    // Append leading zeroes until 8 digits
    for(int i = 0; i < maxNum - str_length; i++)
    {
        tempAcc = "0" + tempAcc;
    }
    // Generate file name
    std::string filename = "acc_";
    filename += tempAcc;
    filename += ".txt";
    return filename;
}

std::ostream& operator<< (std::ostream& os, const Account& acc)
{
    os << "Account Number: " << std::setfill('0') << std::setw(8) 
       << acc.accountNumber << "\n";
    os << "Current Balance: $" << std::fixed << std::setprecision(2) 
       << acc.balance << "\n";
    os << "Game Played: " << acc.gamesPlayed << "\n";
    os << "Total Amount Won: $" << std::fixed << std::setprecision(2) 
       << acc.amountWon << "\n";
    os << "Total Amount Lost: $" << std::fixed << std::setprecision(2) 
       << acc.amountLost;
    return os;
}
