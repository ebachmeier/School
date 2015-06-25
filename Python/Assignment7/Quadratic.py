# Eric Bachmeier
#      The purpose of this program is to calculate the roots for a quadratic equation.
# Apr. 25, 2013

import math # Import math library

def findRoots(a,b,c): # Define calculate roots function
    x1,x2 = 0,0 # Assign x1 and x2 to 0
    d = b**2-4*a*c # Calclate the discriminant
    if d < 0:
        return False,x1,x2 # If less than zero, no roots
    else:
        x1 = ((b*-1)+(math.sqrt(b**2-4*a*c)))/(2*a) # Calculate root
        x2 = ((b*-1)-(math.sqrt(b**2-4*a*c)))/(2*a) # Calculate next root
        return True,x1,x2 

def isnum(num,valid): # Define number input validation
    try:
        num = float(num)
    except:
        print "Invalid input."
        valid = False
    else:
        valid = True
    return num,valid

print "Solving Quadratic Equations"
print "---------------------------"
print # Print introduction
print "This program solves for the roots of a quadratic equation."
print "The user is prompted for the values of a, b, and c."

run = True
while run:
    print
    valid = False
    while not (valid): # Prompt user for side length
        a = raw_input("Enter the value for a: ")
        a,valid = isnum(a,valid) # Validate input
    valid = False
    while not (valid):
        b = raw_input("Enter the value for b: ")
        b,valid = isnum(b,valid)
    valid = False
    while not (valid):
        c = raw_input("Enter the value for c: ")
        c,valid = isnum(c,valid)
    print
    roots = False
    roots,x1,x2 = findRoots(a,b,c)
    if x1 == x2 and roots == True: # One root equation
        print "The one root that solves the equation is:"
        print "x =",x1
    elif roots == True: # Two root equation
        print "The two roots that solve the equation are:"
        print "x1 =",x1
        print "x2 =",x2
    else:
        print "This quadratic equation does not have any real roots."
    repeat = True # No root equation
    while repeat:
        print # Promt user to repeat
        response = raw_input("Would you like to try again?(Y/N): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using the Quadratic Formula Program!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
