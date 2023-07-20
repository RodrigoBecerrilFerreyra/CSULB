# CECS 100 Fall 2018
# Project 5
# "Bubble Sort"
# Start date: 2018-11-27
# Turn-in date: 2018-12-04
# Name: Rodrigo Becerril Ferreyra
# ID Number: 017584071
# Description:
# 	Manual bubble sort algorithm

def bubble(oldlist, end=-1):
	"""Usage: newlist = bubble(oldlist)

	Returns a list sorted from least to greatest.
	"""

	# Make end equal to the length of the list if function is called outside of function
	if end==-1:
		end = len(oldlist)
	
	# Base case: the function is finished, and should be returned
	if end <= 1:
		return oldlist
	# Recursive case: calculate list and try again	
	else:
		for i in range(end-1):
			if oldlist[i] > oldlist[i+1]:
				# swap oldlist[i] with oldlist[i+1]
				oldlist[i] = oldlist[i] + oldlist[i+1]
				oldlist[i+1] = oldlist[i] - oldlist[i+1]
				oldlist[i] = oldlist[i] - oldlist[i+1]

		return bubble(oldlist, end-1) #recursive (calls itself)

def main():
	
	list1 = []

	print("Please input a series of integers.\n"
	      "When you are finished, press enter again.\n")

	while True:
		try:
			list1.append(int(input()))
		except (ValueError, EOFError) as e:
			break

	print("Your sorted list is " + str(bubble(list1)))

main()
