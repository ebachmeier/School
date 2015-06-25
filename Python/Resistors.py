# Eric Bachmeier
# This program tells you the ohms from the threee coour bands given.
# Date Completed: January 10, 2012

import math
print "Resistors"
print "---------"
print
print "Electronic resistors have their values marked by three painted colour bands (a colour code)."
print
print "The values of the colours are: "
print
print "BLACK – 0    BROWN – 1   RED – 2"
print "ORANGE – 3   YELLOW – 4  GREEN – 5"
print "BLUE – 6     VIOLET – 7  GREY – 8"
print "WHITE – 9"
print
print "The first two colours are combined to create a two-digit number."
print "The third colour is a power of 10."
print
repeat = True
while repeat == True:
    band=raw_input("Enter the colour bands seperated by a hyphen: ")
    band=band.upper()
    ph1=band.index("-")
    ph2=band.index("-",ph1+1)
    c1=band[0:ph1]
    c2=band[ph1+1:ph2]
    c3=band[ph2+1:]
    colours=["BLACK","BROWN","RED","ORANGE","YELLOW","GREEN","BLUE","VIOLET","GREY","WHITE"]
    digit1=colours.index(c1)
    digit2=colours.index(c2)
    tensvalue=digit1*10+digit2
    digit3=colours.index(c3)
    ohms=tensvalue* math.pow(10,digit3)
    print
    print "A",band,"resistor has the value",tensvalue,"* 10^"+str(digit3),"ohms=",ohms,"ohms."
    print
    response = raw_input("Would you like to enter another colour band? (Y/N) :  ")
    if response == "N" or response == "n":
        repeat = False
print
print "Good bye!"
