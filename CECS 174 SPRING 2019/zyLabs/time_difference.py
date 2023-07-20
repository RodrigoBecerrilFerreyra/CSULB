# input
time1str = input("\nEnter the first time as hours:minutes in 24 hour format:\n")
time2str = input("\nEnter the second time as hours:minutes in 24 hour format:\n")

# parsing
time1 = time1str.split(":")
for i in range(len(time1)):
    time1[i] = int(time1[i])
time2 = time2str.split(":")
for i in range(len(time2)):
    time2[i] = int(time2[i])

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

