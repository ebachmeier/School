# Eric Bachmeier
# This program allows users to input the initial velocity, angle, and time and the program will output the following:
#      Initial Horizontal Velocity
#      Initial Vertical Velocity
#      Horizontal Distance Moved
#      Vertical Distance Moved
#      Final Horizontal Velocity
#      Final Vertical Velocity
# Date Completed: September 13, 2011

import math
print "Projectile Motion"
print "-----------------"
print
print "This program allows the user to input the initial velocity, angle, and time and the program will output the following:"
print
print "\tInitial Horizontal Velocity \tInitial Vertical Velocity"
print "\tHorizontal Distance Moved \tVertical Distance Moved"
print "\tFinal Horizontal Velocity \tFinal Vertical Velocity"
print

# u = Initial Velocity
# a = Angle in Degrees
# t = Time
# AR = Angle in Radians

u = float (raw_input ("Enter the Initial Velocity in m/s: "))
a = float (raw_input ("Enter the Angle Above the Horizontal in degrees: "))
t = float (raw_input ("Enter the Time in seconds: "))
print

# Initial Horizontal Velocity
IHV = u * math.cos (math.radians (a))
print "The Initial Horizontal Velocity is ", IHV, " m/s."

# Initial Vertical Velocity
IVV = u * math.sin (math.radians (a))
print "The Initial Vertical Velocity is ", IVV, " m/s."

# Horizontal Distance Moved
HDM = u * t * math.cos (math.radians (a))
print "The Horizontal Distance Moved is ", HDM, " m."

# Vertical Distance Moved
VDM = u * t * math.sin (math.radians (a)) + (0.5 * (-9.81) * t * t)
print "The Vertical Distance Moved is ", VDM, " m."

# Final Horizontal Velocity
FHV = u * math.cos (math.radians (a))
print "The Final Horizontal Velocity is ", FHV, " m/s."

# Final Vertical Velocity
FVV = u * math.sin (math.radians (a)) + (-9.81 * t)
print "The Final Verticle Velocity is ", FVV, " m/s."
