# Eric Bachmeier
# Date Completed: October 18, 2011

import math
print "D-A-O-D"
print "-I-M-N-"
print
num = 0
patt = 0
change = 0
max_num = 0
drop_num = -1
for num in range(1,10,1):
    if (max_num == 5):
        for patt in range(0,max_num + drop_num +((max_num+drop_num) - 1),1):
            if (patt == 0):
                print
                print "".rjust(num * 2),
                print str(num),
            else:
                print str(num),
        drop_num = drop_num - 1
    else:
        for patt in range(0,num + (num - 1),1):
            if (patt == 0):
                print
                print "".rjust((10-num)*2),
                print str(num),
            else:
                print str(num),
        max_num = num
print
