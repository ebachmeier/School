# Eric Bachmeier
#      The purpose of this program is to promt the user for the lower and upper
# limits and display the squares, square roots, and cubes of the numbers between
# those two limits.
# Feb. 20, 2013

print "Squres Cubes"
print # Print opening sequence information
print "This program will display the squares, square roots, and cubes of the"
print "numbers requested by you. You will be promted for the lower and upper limits"
print "of the numbers to be displayed."
print
# Import math library
import math
# Validation code
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print"Invalid input."
        valid = False
    else:
        valid = True
    return num,valid
# Promt user for lower and upper limits
run = True
while run:
    print # Validate
    valid = False
    while not(valid):
        lower = raw_input("Enter the lower number: ")
        lower,valid = isnumber(lower,valid)
    valid = False
    while not(valid):
        upper = raw_input("Enter the higher number: ")
        upper,valid = isnumber(upper,valid)
    print
    if upper < lower:
        print "The higher number must be greater or equal to the lower number."
        continue
    else:
        # Print table headers
        print "Number ","Square ","Square Root ","Cube"
        print "------ ","------ ","----------- ","----"
        for x in range (lower, upper+1):
            print str(x).rjust(6), # Print numbers in limits
            print str(int(math.pow(x,2))).rjust(6), # Squared
            if x >= 0:
                print str(round(math.sqrt(x),3)).rjust(12), # Square Root if above zero
            else:
                print " ".rjust(12), # Blank print space if can't be square root
            print str(int(math.pow(x,3))).rjust(6) # Cubed
    print
    # Ask user to repeat program
    response = raw_input("Would you like to try again with different limits?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print"Thankyou for using Squares Cubes Program!"
