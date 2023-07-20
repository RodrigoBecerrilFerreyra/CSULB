ui = input("Enter a string consisting of alphabetic characters with \"$\":\n")

while True:
	if len(ui) > 0:
		if ui[0] == "$":
			ui = ui[1:]
		else:
			break
	else:
		break

print(ui)
