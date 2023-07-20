# CECS 100 Project 3
# "Graphing a line using matplotlib and pyplot"
# Start date: 06 November 2018
# End date: 08 November 2018
# Name: Rodrigo Becerril Ferreyra
# ID: 017584071

'''
This program is intended to graph the line defined either by two points
or by a slope and a y-intercept. The required parameters will be inputed by the user.
'''

# pyplot is the necessary library for this program
import matplotlib.pyplot as plt

# plot a line using two user-defined points
def twopoints():
	print("\nEnter the coordinates of your two points as prompted.")
	while True:
		try:
			# User input
			x1 = float(input("X₁ = "))
			y1 = float(input("Y₁ = "))
			x2 = float(input("X₂ = "))
			y2 = float(input("Y₂ = "))
			# If the user does not input a valid number, make him start all over again
			# If the user does input a valid number, proceed with the program
			error = False
			break
		except ValueError:
			error = True
			print("You didn't enter an integer. Please try again.")

	# if no error occured during user input
	if(not error):
		# calculate slope
		m = (y2 - y1)/(x2 - x1)

		# y = m(x - x1) + y1

		# Plot these points
		x = [-10, 0, 10, x1, x2]
		y = []

		for i in x:
			# this calculates f(x) for x = 10, -10, 0, and the x values that the user inputed
			y.append( (m * (i - x1) ) + y1 )

		# plot all points on a line (no visible dots)
		plt.plot(x, y, "r")

		# if the user inputted something greater than 10 or less than -10 for any x value
		if(x1 > 10) or (x2 > 10) or (x1 < -10) or (x2 < -10):
			# don't graph x = 10 and x = -10
			plt.plot([x[3], x[4]], [y[3], y[4]], "ro")
		else:
			# graph x = 10 and x = -10
			plt.plot([x[0], x[2], x[3], x[4]], [y[0], y[2], y[3], y[4]], "ro")
		plt.grid()
		plt.show()

# plot a line using a user-defined slope and y-intercept
def slopeint():
	print("\nEnter the slope and y-intercept of your function as prompted.")

	while True:
		try:
			# user input
			m = float(input("m = "))
			b = float(input("y = "))
			# if anything goes wrong, the user must try again
			# if not, proceed with the program
			error = False
			break
		except ValueError:
			error = True
			print("You didn't enter an integer. Please try again.")

	if(not error):
		# plot these x values
		x = [-10, 0, 10]
		# calculate y values dependant on x values
		y = [m*x[0]+b, b, m*x[2]+b]
		#for i in x:
		#	y.append(b + (m * i))

		# plot the graph
		plt.plot(x, y, "ro")
		plt.plot(x, y, "r")
		plt.grid()
		plt.show()

def main():
	print("Plot a graph using pyplot!")
	print("\nEnter a 1 or a 2\n1: Plot a line using two points\n2: Plot a line using a slope and a y-intercept.")
	
	# menu for user selection
	try:
		ui = int(input("\n"))

		if ui == 1:
			twopoints()
		elif ui == 2:
			slopeint()
		else:
			raise(ValueError)

	except ValueError:
		print("Please enter a 1 or a 2!")

main()	
