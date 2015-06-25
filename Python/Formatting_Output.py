print "Inches".rjust(10),"Centimetres".center(20),"Feet".ljust(10)
print "------".rjust(10),"-----------".center(20),"----".ljust(10)
inches = 0.0   # counter for number of sales
while inches <= 30:
    cm = inches * 2.54
    feet = inches / 12.0
    print str(inches).rjust(10),str(round(cm,2)).center(20),str(round(feet,2)).ljust(10)
    inches = inches + 1
