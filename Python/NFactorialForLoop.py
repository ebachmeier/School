# Eric Bachmeier
# Date Compleetd: October 7, 2011

print "N Factorial (N!) Calculator"
print "---------------------------"
print
repeat = True

while repeat == True:
    print
    number = int (raw_input ("Enter a positive integer: "))
    print
    count = 2
    fact = 1
    outstr = str (number)
    outstr =  outstr + "! = 1"
    for Integer in range (1,number,1):
        fact = fact * count
        outstr = outstr + " x " + str(count)
        count = count + 1
    outstr = outstr + " = " + str(fact)    
    print outstr
    print
    loop = 1
    while loop == 1:
        response = raw_input ("Would you calculate another factorial? (Y/N): ")
        if response == "n" or response == "N":
            repeat = False
            loop = 0
        elif response == "y" or response == "Y":
            repeat = True
            loop = 0
        else:
            print "please enter a valid response (Y/N)"
print
print "Good bye!"
