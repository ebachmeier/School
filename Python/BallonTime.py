# Eric Bachmeier
# The purpose of this program is to have the user input the humidity factor and
# the maximum amount of time Principle Thomas is willing to wait. The program
# will output when the balloon touches the ground if it does at all.
# Date Completed: November 3, 2011

print "Balloon Time Program"
print "--------------------"
print
print "This program will have users enter the humidity and maximum amount of"
print "time Principle Thomas as willing to wait. The program will tell the user"
print "if the balloon will hit the ground and if it does, what hour it will."
print
repeat = True
while repeat == True:
    h = int(raw_input ("Enter the humidity: "))
    if h > 100 or h < 0:
        int (raw_input ("Please enter another number for humidity between 0 and 100. ")) 
    Max = int (raw_input ("Enter the maximum amount of time Principle Thomas is willing to wait: "))
    if Max > 240 or Max < 0:
        int (raw_input ("Please enter another amount of time between 0 and 240 hours. "))
    t= 1
    A = (-6*(t**4))+ (h*(t**3))+ (2*(t**2))+ t
    while A > 0 and Max <> t:
        t = t+ 1
        A = (-6*(t**4))+ (h*(t**3))+ (2*(t**2))+ t
        if Max==t:
            print "The balloon does not touch ground in the given time."
            print
        if A<=0:
            print "The balloon first touches ground at hour", t
            print
    response = raw_input ("Would you like to enter more information? (Y/N) ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
            
