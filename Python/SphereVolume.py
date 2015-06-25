# Eric Bachmeier
# This program is to input the dimensions of a sphere and calculate the volume.
# Date Completed: September 12, 2011

import math
print "Volume of a Sphere"
print
radius = float (raw_input ("Enter the Radius of the Sphere: "))
print
V = 4.0 / 3.0 * 3.14159 * (radius ** 3)
print "The Volume of the Sphere is ", V, " cubed units."
