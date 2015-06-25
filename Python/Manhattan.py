# Eric Bachmeier
# Date Completed: October 3, 2011

import math # Import the math library
# Print Introduction
print "Manhattan Island"
print "----------------"
# This program has users enter an interest rate and it will say how much the
# Island is worth after so many years since the American Indians sold it.

print "In 1634, the American Indians sold Manhattan Island for $24.00. If the"
print "money had been invested, it would have grown to a very large amount by"
print "the year 2011."
print

repeat = True
while repeat == True:
    interest = float(raw_input("Enter the interest rate: "))
    print "Year".rjust(6),"Amount".rjust(10)
    print "----".rjust(6),"------".rjust(10)
    amount = 24
    year = 1634
    while year <= 2011:
        amount = amount + amount * interest / 100
        year = year + 1
        if year == 1700:
            print str (year).rjust(6), str(round (amount, 2)).rjust(10)
        elif year == 1800:
            print str (year).rjust(6), str(round (amount, 2)).rjust(10)
        elif year == 1900:
            print str (year).rjust(6), str(round (amount, 2)).rjust(10)
        elif year == 2000:
            print str (year).rjust(6), str(round (amount, 2)).rjust(10)
        elif year == 2011:
            print str (year).rjust(6), str(round (amount, 2)).rjust(10)

    print
    response = raw_input("Would you like to enter another range?(Y/N): ")
    print
    if response == "N" or response == "n":
        repeat = False

print "Good bye!"
