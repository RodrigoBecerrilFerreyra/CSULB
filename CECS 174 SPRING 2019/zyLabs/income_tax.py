# 1 percent on the first $50,000.
# 2 percent on the amount over $50,000 up to $75,000.
# 3 percent on the amount over $75,000 up to $100,000.
# 4 percent on the amount over $100,000 up to $250,000.
# 5 percent on the amount over $250,000. 

# 80000 taxed -> (50000 * 0.01) + (25000 * 0.02) + (5000 * 0.03) = 1150

ui = float(input("Enter the income:\n"))
tax = 0.0

flag2, flag3, flag4, flag5 = False, False, False, False
if ui <= 50000.0:
    tax += (ui * 0.01)
else:
    if (ui - 50000.0) > 0:
        flag2 = True
    if (ui - 75000.0) > 0:
        flag3 = True
    if (ui - 100000.0) > 0:
        flag4 = True
    if (ui - 250000.0) > 0:
        flag5 = True

if flag2:
    tax += 500.0 #50000 * 0.01
    ui -= 50000.0
if flag3:
    tax += 500.0 #25000 * 0.02
    ui -= 25000.0
if flag4:
    tax += 750.0 #25000 * 0.03
    ui -= 25000.0
if flag5:
    tax += 6000 #150000 * 0.04
    ui -= 150000.0

if flag2 and flag2 and flag4 and flag5:
    tax += (ui * 0.05)
elif flag2 and flag3 and flag4:
    tax += (ui * 0.04)
elif flag2 and flag3:
    tax += (ui * 0.03)
else:
    tax += (ui * 0.02)

print("The tax payable would be $ {}".format(tax))
