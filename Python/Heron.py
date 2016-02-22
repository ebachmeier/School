# Eric Bachmeier
#      The purpose of this program is to prompt the user for the three sides of
# the triangle, and use Heron's formula to calculate the area.
# Feb. 4, 2013

print "Heron's Formula"
print
print "     This program will prompt you for the lengths of the three sides of"
print "the triangle. It will then calculate the area using Heron's formula."
print
print "The formula is as follows:"
print
print "A="+u"\u221A"+"s(s-a)(s-b)(s-c)"
print
import math
repeat = True
while repeat:
    # Validate side A input
    valid = True
    while valid == True:
        a = raw_input("Enter the side length of A: ")
        for x in range(0,len(a)):
            if a[x] not in('0','1','2','3','4','5','6','7','8','9','.','+'):
                valid = True
                break
            else:
                valid = False
        if valid == False:
            if float(a)<0:
                valid = True
        else:
            print "Invalid input."
    # Validate side B input
    valid = True
    while valid == True:
        b = raw_input("Enter the side length of B: ")
        for x in range(0,len(a)):
            if b[x] not in('0','1','2','3','4','5','6','7','8','9','.','+'):
                valid = True
                break
            else:
                valid = False
        if valid == False:
            if float(b)<0:
                valid = True
        else:
                print "Invalid input."
    # Validate side C input
    valid = True
    while valid == True:
        c = raw_input("Enter the side length of C: ")
        for x in range(0,len(c)):
            if c[x] not in('0','1','2','3','4','5','6','7','8','9','.','+'):
                valid = True
                break
            else:
                valid = False
        if valid == False:
            if float(c)<0:
                valid = True
        else:
                print "Invalid input."
    # Assign variables
    a = float (a)
    b = float (b)
    c = float (c)
    # Ensure proper triangle
    if not(c<(a+b) and a<(b+c) and b<(a+c)):
        print
        print"Those side lengths do not make a proper triangle."
        print"Please try again."
        print
        continue
    # Make s perimeter variable
    print"Where the variable s is the perimeter of the triangle."
    print
    print"s = "+str(a)+"+"+str(b)+"+"+str(c)
    print"    -----------"
    print"         2"
    s = (a+b+c)/2
    # Make A the area variable for the answer
    A = math.sqrt(s*(s-a)*(s-b)*(s-c))
    print
    # Print the answer rounded to 2 decimal places
    print "The area of the triangle is ",round(A,2)
    print
    # Repeat loop yes or no
    response = raw_input("Would you like to find the area for another triangle? (Y/N): ")
    if response == "N" or response == "n":
        repeat = False
        print
        print"Thanks for using this program for Heron's Formula!"
        print
        print "Eric Bachmeier - 2013"        
    print
