def countWords(string):
    splitstring = string.replace("-", " ")
    splitstring = splitstring.split()

    return len(splitstring)

def main():
    print(countWords("Strawberry-banana smoothie")) #should this count as three?

main()
