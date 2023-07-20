def reverseString(a_str):
    # this is where your function goes
    reversedStr = []

    for index, value in enumerate(a_str.split()):
        if index % 2 == 0:
            reversedStr.append(value[::-1])
        else:
            reversedStr.append(value)

    return " ".join(reversedStr)

def main():
    print("Enter a sentence: ")
    print(reverseString(input()))

main()
