# Eric Bachmeier
# This program is to input the dimensions of a triangle and calculate the area.
# Date Completed: September 13, 2011

import math
print "Area of a Triangle"
print
a = float (raw_input ("Enter the Length of Side A: "))
b = float (raw_input ("Enter the Length of Side B: "))
c = float (raw_input ("Enter the Length of Side C: "))
s = (a + b + c) / 2
print
print "The Perimeter of the Triangle is ", s * 2, " units."
A = math.sqrt (s * (s - a) * (s - b) * (s - c))
print
print "The Area of the Triangle is ", A, " square units."
