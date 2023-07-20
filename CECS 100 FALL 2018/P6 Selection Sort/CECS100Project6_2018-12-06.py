# Selection Sort
# Project 6
# CECS 100
# Name: Rodrigo Becerril Ferreyra
# ID: 017584071
def selection(oldlist, start=0):

    # Base case: list is already sorted
    if (start >= len(oldlist) - 1) or (len(oldlist) == 0):
        return oldlist
    # Recursive case: Continue with swap
    else:
        # Find the index of the smallest integer
        swap = oldlist.index(min(oldlist[start:]))
        # If the smallest integer is not in the start index
        if oldlist[swap] < oldlist[start]:
            # swap
            oldlist[start] = oldlist[start] + oldlist[swap]
            oldlist[swap] = oldlist[start] - oldlist[swap]
            oldlist[start] = oldlist[start] - oldlist[swap]
        return selection(oldlist, start+1) #recursive function

def main():
	list1 = []

	print("Please input a series of integers.\n"
	      "When you are finished, press enter again.\n")

	while True:
		try:
			list1.append(int(input()))
		except (ValueError, EOFError) as e:
			break

	print("Your sorted list is " + str(selection(list1)))

main()
