# logic
#If hour1 < hour2
#    time1 comes first
#else if hour1 and hour2 are the same
#    if minute1 < minute2 
#        time1 comes first
#    else if minute1 and minute2 are the same
#        time1 and time2 are the same
#    else 
#        time2 comes first
#else
#    time2 comes first

# Validation Format:
#   Invalid format !!!
#   Invalid entry - input should be numbers only.
#   Invalid time range.

while True:
    time1str = input("\nEnter the first time as hours:minutes in 24 hour format:\n")
    time2str = input("\nEnter the second time as hours:minutes in 24 hour format:\n")
    
    time1 = time1str.split(":")
    time2 = time2str.split(":")

    # invalid format check
    if (len(time1) != 2) or (len(time2) != 2):
        print("\nInvalid format !!!")
        continue

    # invalid content check
    if not time1[0].isdigit() or not time1[1].isdigit() or not time2[0].isdigit() or not time2[1].isdigit():
        print("\nInvalid entry - input should be numbers only.")
        continue
    
    # only change input to integers after content check
    # (ie avoiding ValueError)
    for i in [0, 1]:
        time1[i] = int(time1[i])
    for i in [0, 1]:
        time2[i] = int(time2[i])

    # invalid range check
    if time1[0] > 23 or time1[1] > 59 or time2[0] > 23 or time2[1] > 59:
        print("Invalid time range.")
        continue

    #break
    # logic
    if time1[0] < time2[0]:
        print("time1 comes first")
    elif time1[0] > time2[0]:
        print("time2 comes first")
    else:
        if time1[1] < time2[1]:
            print("time1 comes first")
        elif time1[1] > time2[1]:
            print("time2 comes first")
        else:
            print("time1 and time2 are the same")
    
    cont = input("Would you like to try again, 'Yes' for continue, quit otherwise:\n").upper()
    if cont == "YES":
        continue
    else:
        break

print("Goodbye")
