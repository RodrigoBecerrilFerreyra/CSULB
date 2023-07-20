/*
 * Purpose: solve Chapter 4 Question 15 (Shipping Calculator Problem)
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 3
 *
 */
#include <iostream>

using namespace std;

int main()
{
    double weight_of_package, distance_of_travel;
    // The following are shipping rates per mile for packages weighing
    // <2kg, 2kg-6kg, 6kg-10kg, and 10kg-20kg, respectively.
    double rate_of_shipping[] = {0.002, 0.0044, 0.0074, 0.0096};

    cout << "Welcome to the Fast Freight Shipping Company." << endl;

    // The following while loop runs until the user enters a valid input
    // (a number more than 0 and no more than 20 kg).
    while(true)
    {
        cout << "Please enter the weight of the package (in kilograms) "
             << "you wish to send: ";
        cin >> weight_of_package;
        if(weight_of_package <= 0.0)
            cout << "The package must weigh more than 0.0 kg. "
                 << "Please try again." << endl;
        else if(weight_of_package > 20.0)
            cout << "The maximum package weight the Company is willing "
                 << "to ship is 20.0 kg." << endl;
        else
            break;
    }

    // The following while loop runs until the user enters a valid input
    // (a number between 10 and 3000 (inclusive)).
    while(true)
    {
        cout << "Now, please enter the distance (in miles) you wish your "
             << "package to travel: ";
        cin >> distance_of_travel;
        if(distance_of_travel > 3000.0)
            cout << "The maximum distance the Company is willing to ship your "
                 << "package is 3000.0 miles." << endl;
        else if(distance_of_travel < 10.0)
            cout << "The minimum distance the Company is willing to ship your "
                 << "package is 10.0 miles." << endl;
        else
            break;
    }

    double total_cost;
    if(weight_of_package < 2.0)
        total_cost = rate_of_shipping[0] * distance_of_travel;
    else if(weight_of_package < 6.0)
        total_cost = rate_of_shipping[1] * distance_of_travel;
    else if(weight_of_package < 10.0)
        total_cost = rate_of_shipping[2] * distance_of_travel;
    else // package cannot be more than 20 kg
        total_cost = rate_of_shipping[3] * distance_of_travel;
    
    cout << "Your total cost to ship the package will be " << total_cost
         << " USD." << endl;

    return 0;
}
