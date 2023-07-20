# input and validation
time1str = input("\nEnter the first time as hours:minutes in 24 hour format:\n")
time2str = input("\nEnter the second time as hours:minutes in 24 hour format:\n")

# parsing and input validation
# correct checks if it was entered correctly
correct1 = True
correct2 = True
time1 = time1str.split(":")
if len(time1) != 2:
    correct1 = False



time2 = time2str.split(":")
if len(time2) != 2:
    correct2 = False



# isnum checks if input is numeric
isnum1 = True
isnum2 = True
if correct1 and correct2:
    if time1[0].isdigit() and time1[1].isdigit():
        isnum1 = True
    else:
        isnum1 = False
    if time2[0].isdigit() and time2[1].isdigit():
        isnum2 = True
    else:
        isnum2 = False

if correct1 and isnum1:
    for i in range(len(time1)):
        time1[i] = int(time1[i])
if correct2 and isnum2:
    for i in range(len(time2)):
        time2[i] = int(time2[i])

# inrange checks if input is within range (hr 0-23, min 0-59)
inrange1 = True
inrange2 = True

if correct1 and correct2 and isnum1 and isnum2:
    if (time1[0] > 23) or (time1[1] > 59):
        inrange1 = False
    if (time2[0] > 23) or (time2[1] > 59):
        inrange2 = False

# logic

if (not correct1) or (not correct2):
    print("Invalid format !!!")
if (not isnum1) or (not isnum2):
    print("Invalid entry - input should be numbers only.")
if (not inrange1) or (not inrange2):
    print("Invalid time range.")

if correct1 and correct2 and isnum1 and isnum2 and inrange1 and inrange2:
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

