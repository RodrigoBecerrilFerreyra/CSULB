# Rodrigo Becerril Ferreyra
# 017584071
# CECS 100 Autumn 2018
# 2018-09-18
# Project 1
# "Compound Interest"

# Corresponds to pp. 106 + 107 in text
# Objective: calculate compound interest given rate, number of times compounded, and time
# -----------------------------------------------------------

#Formula:
    # A = P(1 + (r/n))^(nt)
        # A = final amount
        # P = principle
        # r = interest rate
        # n = number of times interest is compounded per year
        # t = time (years)

# init variables
P = 0.0
r = 0.0
n = 0.0
t = 0.0

print("""\nWelcome to the compound interest calculator. You can calculate how much money you will have in a
bank account using a few values: the amount you put in, the annual interest rate (as a decimal), the
amount of times your bank compounds your money (you can figure this out by calling your bank), and the
number of years you plan to have your money in your account.\n""")
print("Please enter the values on screen and press Enter.\nDo not use any symbols such as commas or percent signs. A decimal point is acceptable.\n")

while(1):
    try:
        P = float(input("Principle (introductory balance) (in USD) (how much money you put into the account): "))
        r = float(input("Interest  rate (per year (APY)) (decimal number) (found on your account terms): "))
        
        # This is quality control: if the user accidentally puts in a percent, the program
        # automatically divides by 100
        if(r > 1):
            r /= 100
        n = float(input("Number of times interest is calculated per year (found on your account terms): "))
        
        #the function calls for n^-1, so n cannot equal 0.
        if(n==0):
            raise ZeroDivisionError()
        
        t = float(input("Account age (in years) (how long the account has been/will be open): "))
        break #out of the infinite loop
    except ValueError:
        print("\nNot a valid number. Please try again.\n")
    except ZeroDivisionError:
        print("\nIt is not possible to compound zero times a year. Please try again.\n")

# Main calculation
A = P * ((1 + (r/n)) ** (n*t))

# prints out Amount rounded off to two decimal places
print("\nYour account balance will be ${0}.".format(round(A, 2)))
