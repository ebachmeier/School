# Eric Bachmeier
# This program allows users to input the values of a, b, and c and the program will output the roots.
# Date Completed: September 19, 2011

import math
print "Quadratic Roots Formula"
print
a = float (raw_input ("Enter the Value of A: "))
b = float (raw_input ("Enter the Value of B: "))
c = float (raw_input ("Enter the Value of C: "))
print
# d = discriminant

d = (b ** 2) - (4 * a * c)

if d >= 0:
    print "The discriminant is positive."
    x1 = ((-b) + math.sqrt (b ** 2 - 4 * a * c)) / (2 * a)
    print
    print "The first root is ", x1, " units."
    x2 = ((-b) - math.sqrt (b ** 2 - 4 * a * c)) / (2 * a)
    print
    print "The second root is ", x2, " units."
else:
    print "The discriminant is negative. There are no real roots."

