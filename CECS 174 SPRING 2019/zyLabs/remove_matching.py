user_input = input("\nEnter a string:\n").split()

print("Original list is", user_input)

index = 0
while True:
    if index >= len(user_input):
        break
    if len(user_input[index]) < 4:
        del user_input[index]
        index = 0
    else:
        index += 1

print("Final list is", user_input)
