# Eric Bachmeier
# Date Completed: October 17, 2011

import math # Import the math library
# Print Introduction
print "Ounces to Grams Convertor"
print "-------------------------"
print "This program has users enter a range in ounces and it gives the grams conversions in a chart."
print

repeat = True
while repeat == True:
    low = int(raw_input("Enter the lower range in Ounces: "))
    high = int(raw_input("Enter the upper range in Ounces: "))
    ounces = low # counter for number of ounces
    print "Ounces".rjust(6),"Grams".rjust(10)
    print "------".rjust(6),"-----".rjust(10)
    for ounces in range (low, high + 1, 1):
        grams = (ounces * 28.35)
        print str(ounces).rjust(6),str(round(grams,2)).rjust(10)
        ounces = ounces + 1
        
    print
    response = raw_input("Would you like to enter another range?(Y/N): ")
    print
    if response == "N" or response == "n":
        repeat = False

print "Good bye!"
