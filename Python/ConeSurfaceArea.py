# Eric Bachmeier
# This program is to input the dimensions of a cone and calculate the surface area.
# Date Completed: September 12, 2011

import math
print "Surface Area of a Cone"
print
radius = float (raw_input ("Enter the Radius of the Cone: "))
side = float (raw_input ("Enter the Side Length of the Cone: "))
print
SA = (3.14159 * radius * side) + (3.14159 * (radius ** 2))
print "The Surface Area of the Cone is ", SA, " square units."
