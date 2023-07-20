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
 * Account class testing file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "Account.h"

int main()
{
    // create an Account object
    int accnum; double money;
    Account* acc = nullptr;
    while(true)
    {
        try
        {
            std::cout << "Create a new account: enter your account number and "
              << "balance:\nAccount number (8 digit number): ";
            std::cin >> accnum;
            std::cout << "Balance (non-negative): ";
            std::cin >> money;
            acc = new Account(accnum, money);
            break;
        }
        catch(Account::NumOutOfBounds &e)
        {
            std::cerr << e.getErrorMessage() << "\n";
        }
        catch(Account::NumNegative &e)
        {
            std::cerr << "Money must be a non-negative number.\n";
        }
    }

    // add the result of a game
    acc->inputGameResults(500, 0);
    std::cout << *acc << std::endl;
    acc->inputGameResults(0, 1000);
    std::cout << *acc << std::endl;

    delete acc; acc = nullptr;
    return 0;
}
