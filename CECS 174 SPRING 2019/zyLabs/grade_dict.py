grades = {}

# using functions to make everything neater
def add():
    student_name = input("Enter the name of the student:\n")
    if student_name in grades:
        print("Sorry, that student is already present.")
    else:
        student_grade = input("Enter the student's grade:\n")
        grades[student_name] = student_grade

def remove():
    student_name = input("What student do you want to remove?\n")
    if student_name not in grades:
        print("Sorry, that student doesn't exist and couldn't be removed.")
    else:
        del grades[student_name]

def modify():
    student_name = input("Enter the name of the student to modify:\n")
    if student_name not in grades:
        print("Sorry, that student doesn't exist and couldn't be modified.")
    else:
        print("The old grade is", grades[student_name])
        grades[student_name] = input("Enter the new grade:\n")
        

def printall():
    if len(grades) == 0:
        print("No record found!")
    else:
        for i in sorted(grades):
            print(i, grades[i])

def main():
    # Menu:
    #   Add
    #   Remove
    #   Modify
    #   Print all
    #   Quit
    while True:
        user_input = input("(A)dd, (R)emove, (M)odify, (P)rint all, or (Q)uit?\n").upper()
        if user_input == "A":
            add()
        elif user_input == "R":
            remove()
        elif user_input == "M":
            modify()
        elif user_input == "P":
            printall()
        elif user_input == "Q":
            print("Goodbye!")
            break
        else:
            print("Sorry, that wasn't a valid choice.")

main()
