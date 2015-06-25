# Eric Bachmeier
# Date Completed: October 17, 2011

import math 

print "Pattern"
print "-------"
print
number = 0
pattern = 0
change = 0
max_number = 0
minus_number = -1
for number in range(1,10,1):
    if (max_number == 5):
        for pattern in range(0,max_number + minus_number,1):
            if (pattern == 0):
                print
                print str(number),
            else:
                print str(number),
        minus_number = minus_number - 1
    else:
        for pattern in range(0,number,1):
            if (pattern == 0):
                print
                print str(number),
            else:
                print str(number),
        max_number = number
