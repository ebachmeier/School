# Eric Bachmeier
# Date Completed: October 17, 2011

print "Character Display"
print "-----------------"
print
print "Each character in Python is represented by a number between 0 and 255."
print "For example, the character represented by the number 57 is the digit 9."
print "The characters with values from 0 to 31 are non-printing characters"
print "and will not display anything on the screen."
print

repeat = True
while repeat == True:
    low = int (raw_input ("Enter the lower range: "))
    high = int (raw_input ("Enter the higher range: "))
    print
    print "Value".rjust(5), "Character".rjust(9)
    print "-----".rjust(5), "---------".rjust(9)
    value = low
    for value in range (low, high + 1, 1):
        print str (value).rjust(5), chr(value).rjust(9)
        value = value + 1
        print
    response = raw_input ("Would you like to display another set of characters (Y/N)? ")
    if response == "n" or response == "N":
        repeat = False
    
print "Good bye!"
