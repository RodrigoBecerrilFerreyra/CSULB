def findLongestWord(a_str):
    # this is where your function goes
    word = ""
    for i in a_str.split():
        if len(i) >= len(word):
            word = i
    
    return word

def main():
    print(findLongestWord("lmao lol rofl"))

main()
