# Eric Bachmeier
# This program allows users to input their height and weight and it tells them their BMI and an appropriate response.
# Date Completed: September 21, 2011

import math
print "BMI Calculator"

print
w = float (raw_input ("Enter your Weight in Kg: "))
h = float (raw_input ("Enter your height in m: "))

BMI = w / (h * h)
print
print "Your BMI is ", BMI, " Kg/m squared."
print

if BMI < 15:
    print "You are Starvation."
elif BMI < 18.5:
    print "You are Underweight."
elif BMI <= 25:
    print "You are Ideal."
elif BMI <= 30:
    print "You are Overweight."
elif BMI <= 40:
    print "You are Obese."
else:
    print "You are Morbidly Obese."
    
