# Eric Bachmeier
#      The purpose of this program is to promt the user for side a, angle A,
# and angle B; and then solve for the remaining two sides and angle.
# Feb. 6, 2013

print "Sine's Law"
print
print "This program will promt you for side a, angle A, and angle B of a"
print "triangle and solve for sides b and c, as well as angle C."
print
print "The law is as follows: "
print
print "   a     b     c"
print "  --- = --- = ---"
print " Sin A Sin B Sin C"
print
print "a, b, and c are the sides while A, B, and C are the angles, respectively."
print
import math
repeat = True
valid = False
while repeat:
    # Validate side a input
    valid = False
    while valid == False:
        # Promt user for side a
        a = raw_input("Please enter side a: ")
        for x in range(0,len(a)):
            if a[x] not in('0','1','2','3','4','5','6','7','8','9','.'):
                valid = False
                print "Invalid input."
                break
            else:
                try:
                    if float(a)>0:
                        valid = True
                    else:
                        valid = False
                        print "Invalid input."
                        break
                except:
                    valid = False
                    print"Invalid input."
                    break
    # Validate angle A input
    valid = False
    while valid == False:
        # Promt user for angle A
        A = raw_input("Please enter angle A: ")
        for x in range(0,len(A)):
            if A[x] not in('0','1','2','3','4','5','6','7','8','9','.'):
                valid = False
                print"Invalid input."
                break
            else:
                if float(A)<=180 and float(A)>0:
                    valid = True
    # Validate angle B input
    valid = False
    while valid == False:
        # Promt user for angle B
        B = raw_input("Please enter angle B: ")
        for x in range(0,len(B)):
            if B[x] not in('0','1','2','3','4','5','6','7','8','9','.'):
                valid = False
                print"Invalid input."
                break
            else:
                valid = True
    # Validate triangle
    if float(A) + float(B)>=180:
        print
        print"These angles dont make a proper triangle, please try again."
        print
        continue
    # Assign variables
    a = float(a)
    A = float(A)
    B = float(B)
    # Make radians
    Ar= math.radians(A)
    Br= math.radians(B)
    C = 180-(A+B)
    b = (a*math.sin(Br))/math.sin(Ar)
    c = (b*math.sin(math.radians(C)))/math.sin(Br)
    # Print answer
    print
    print "The calculated values for your triangle are: "
    print
    print "Angle C =",round(C,2)
    print "Side  b =",round(b,2)
    print "Side  c =",round(c,2)
    # Repeat loop yes or no
    response = raw_input("Would you calculate another triangles angle and sides? (Y/N): ")
    if response == "N" or response == "n":
        repeat = False
        print
        print"Thanks for using this program for Sine's Law!"
        print
        print "Eric Bachmeier - 2013"        
    print
