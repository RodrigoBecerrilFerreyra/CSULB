total = 0
while True:
    
    flag1 = False
    flag2 = False

    try:
        input1 = input("Enter a number, or 2 non-numbers to quit:\n")
        int1 = float(input1)
        total += int1
        continue
    # if input1 is NaN 
    except ValueError as e1:
        flag1 = True
        try:
            input2 = input("Enter a number, or another non-number to quit:\n")
            int2 = float(input2)
            total += int2
        # if input2 is NaN
        except ValueError as e2:
            flag2 = True
    
    if flag1 and flag2:
        break

print("The total is", total)
