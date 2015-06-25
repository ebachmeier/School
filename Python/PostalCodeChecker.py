# Eric Bachmeier
# The purpose of this program is to determine if the user entered a properly
# formatted postal code
# Date Compleeted: December 12, 2011

print "Postal Code Checker"
print "-------------------"
print
print "This program has users enter a postal code, and the program will ensure"
print "it is porperly formatted. This means that the first, third and sixth"
print "characters are capital, and the second, fifth and seventh characters"
print "are numbers."
print
repeat = True
while repeat == True:
    valid = True
    # ask user to input postal code
    code = raw_input("Please enter a valid postal code: ")
    if len(code)!= 7:
        valid = False
        # wrong length
        print "This is not a valid postal code becuase it is not the correct length."
    else:
        # check if 2, 5, 7 are numbers
        if not ord(code[2]) >= 49 or not ord(code[2]) <= 57:
            valid = False
            print "This is not a valid postal code becuase the second character is not a number."
        elif ord(code[5]) < 49 or ord(code[5]) > 57:
            valid = False
            print "This is not a valid postal code becuase the fifth character is not a number."
        elif ord(code[7]) < 49 or ord(code[7]) > 57:
            valid = False
            print "This is not a valid postal code becuase the seventh character uis not a number."
            # check if 1, 3, 6 are letters
        elif ord(code[1]) < 65 or ord(code[1]) > 90:
            valid = False
            print "This is not a valid postal code becuase the first character is not a capital letter."
        elif ord(code[3]) < 65 or ord(code[3]) > 90:
            valid = False
            print "This is not a valid postal code becuase the third character is not a capital letter."
        elif ord(code[6]) < 65 or ord(code[6]) > 90:
            valid = False
            print "This is not a valid postal code becuase the sixth character is not a capital letter."
        elif code[3] != " ":
            # make sure space in middle
            valid = False
        else:
            valid = True
        
    if valid == True:
        # postal code is valid
        print code, "is a properly formatted postal code."
    print
    response = raw_input("Would you like to enter another binary number? (Y/N): ")
    if response == "n" or response == "N":
        repeat = False
    print
print "Good bye!"
