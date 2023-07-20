customers = []
amount = []

while True:
    # Logic:
    # Have user input name then amount
    # If most recent name == "", then break out of loop
    # If two names are the same, append amount to current amount
    # If amount is NaN, re-ask from beginning

    user_name = input("What is the name of the customer ?\n")

    if user_name == "":
        break
    
    while True:
        try:
            # Below line will throw ValueError if input is NaN.
            user_value = int(input("What is the purchase amount (numbers only) ?\n"))
            break
        except ValueError as e:
            pass

    if user_name in customers: #if name already exists, add to existing value
        amount[customers.index(user_name)] += user_value #shouldn't throw ValueError (but can)
    else:
        customers.append(user_name)
        amount.append(user_value)    

# Display top customer
maxindex = amount.index(max(amount))
print("{customer} spent ${value}".format(customer=customers[maxindex], value=amount[maxindex]))
