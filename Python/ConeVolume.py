# Eric Bachmeier
# This program is to input the dimensions of a cone and calculate the volume.
# Date Completed: September 12, 2011

import math
print "Volume of a Cone"
print
radius = float (raw_input ("Enter the Radius of the Cone: "))
height = float (raw_input ("Enter the Height of the Cone: "))
print
V = 1.0 / 3.0 * 3.14159 * radius ** 2 * height
print "The Volume of the Cone is ", V, " cubed units."
