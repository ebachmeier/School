# Eric Bachmeier
# This program is to input the value of Hectares and it will output the conversion in acres, square metres, and square feet.
# Date Completed: September 13, 2011

import math
print "Hectare Converter"
print
H = float (raw_input ("Enter the amount of Hectares: "))

A = H * 2.47
F = H * 107600
M = H * 10000

print
print H, "Hectares is equal to ", A, " acres."
print H, "Hectares is equal to ", F, " square feet."
print H, "Hectares is equal to ", M, " square metres."
