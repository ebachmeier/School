# Eric Bachmeier
#      The purpose of this program is to determine if the number entered by the
# user is a prime number or not.
# Feb. 25, 2013

print "Prime Number Calculator"
print # Print opening sequence information
print "This program will determine if a number entered by the user is a"
print "prime number or not. Recall that a number is prime if it cannot"
print "be evenly divisible by any number from 2 to one less than the number,"
print "otherwise it is composite."
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
        if num <= 0:
            print"Invalid input."
        else:
            valid = True
    return num,valid
run = True
while run:
    print
    even = [] # Make list for even divided numbers
    valid = False
    while not(valid): # Promt user for number (int)
        prime = raw_input("Enter the number to determine if it is prime: ")
        prime,valid = isnumber(prime,valid)    
    divide = False
    if prime == 1:
        divide = True # Prime number if input is 1
    else:
        divide = False
        for x in range(2,prime):
            if prime % x == 0: # Divide by all numbers in between 1 and that number
                divide = True
                even.append(x) # Append even divisors to list (even)
    if divide == False:
        print str(prime)+" is a prime number."
    elif divide:
        if prime == 1:
            print str(prime)+" is not a prime number."
        else:
            print str(prime)+" is not a prime number. It is evenly divisible by",
            for i in range(0,len(even)): # Print all even divisors from list (even)
                a = len(even)
                if even[i] != even[a-1]:
                    print str(even[i])+",",
                else:
                    print "and "+str(even[i])+"."
    print
    # Ask user to repeat program
    response = raw_input("Would you like to try again with a different number?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print"Thankyou for using Prime Number Calculator!"
