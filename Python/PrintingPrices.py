# Eric Bachmeier
# This program allows users to input the number of copies they want and it will output the price per copy and the total cost.
# Date Completed: September 21, 2011

import math
print "Printing Price Calculator"

print
copies = int (raw_input("Enter the number of copies you would like: "))
print

c30 = copies * 0.30
c28 = copies * 0.28
c27 = copies * 0.27
c25 = copies * 0.25

if copies < 500:
    print "You will be charged $0.30 per copy. The total cost for ", copies, "copies is $" + str(round (c30,2)) + "."
elif copies < 750:
    print "You will be charged $0.28 per copy. The total cost for ", copies, "copies is $" + str(round (c28,2)) + "."
elif copies < 1000:
    print "You will be charged $0.27 per copy. The total cost for ", copies, "copies is $" + str(round (c27,2)) + "."
else:
    print "You will be charged $0.25 per copy. The total cost for ", copies, "copies is $" + str(round (c25,2)) + "."
