# Eric Bachmeier
# This purpose of this program is to find the value of a word.
# Date Completed: November 24, 2011

print "Word Value Program"
print "------------------"
print
print "This program has users enter a phone number without brackets and dahes"
print "and the program adds the formatting and outputs it."
print
repeat = True
while repeat == True:
    number = raw_input("Enter a phone number without brackets and dashes: ")
    print "("+number[0:3]+")", number[3:6],"-", number[6:10]
    print number[0:3]
    response = raw_input("Would you like to try again? (Y/N) : ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
