# Eric Bachmeier
#      The purpose of this program is to show the numbers that add together to
# approach, but never reach, two.
# Feb. 27, 2013

print "Closer To 2"
print # Print opening sequence information
print "This program uses a loop to demonstrate that the result of adding"
print "the numbers 1/1, 1/2, 1/4, 1/8, 1/16, ... and so on gets closer and"
print "closer to 2 without becoming 2."
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
run = True
while run:
    print
    valid = False
    while not(valid):
        # Promt user for number of loops they wish to see
        fraction = raw_input("Enter the number of fractions you would like to see: ")
        fraction,valid = isnumber(fraction,valid) # Validate with defined isnumber
        if fraction < 1:
            valid = False
            print "Invalid input."
    number = 1 # Start fraction at 1/1
    total = 0 # Running total of the fractions
    add = 0 # Sum of previous 
    for x in range(0,fraction): # Loop to run until the number entered
        print total,"+", # Print previous total plus the next fraction
        add = (1./number) # Add the fraction    
        print "1/"+str(int(number))+" =", # Show the fraction being added to string
        total = total + add # Update running total
        print total # Print running total
        number = number*2 # Double the dnominator of fraction for next addition
    print
    # Ask user to repeat program
    response = raw_input("Would you like to see a different number of loops?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print"Thankyou for using Closer To 2!"
