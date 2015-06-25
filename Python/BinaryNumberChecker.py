# ERic Bachmeier
# The purpose of this program is to dusplay an inputted binary number
# Date Compleeted: November 25, 2011

print "Binary Number Checker!"
print "----------------------"
print
print "This program has users enter a binary number and the program displays"
print "the number and amkes sure it was entered properly."
print
repeat = True
while repeat == True:
    binary = True
    number = raw_input("Please enter a one byte binary number: ")
    if len(number)!= 9 or number.isdigit == True:
        binary = False
        print "This is not a valid number because the binary number does not contain 8 numbers."
    else:
        if number[0]!= "%":
            binary = False
            print "This is not a valid number because the binary number does not begin with a \"%\"."
        else:
            for x in range(1,9):
                if not(number[x] == "0" or number[x] == "1"):
                    binary = False
            if binary == False:
                print "This is not a valid number because it does not contain only 1's or 0's."
    if binary == True:
        print number[0:5], number[5:9], "is a valid one byte binary number."
    print
    response = raw_input("Would you like to enter another binary number? (Y/N): ")
    if response == "n" or response == "N":
        repeat = False
    print
print "Good bye!"
