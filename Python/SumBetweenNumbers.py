# Eric Bachmeier
#      The purpose of this program is to promt the user for lower and higher
# numbers and calculate the sum between the two numbers.
# Feb. 21, 2013

print "Sum Between Numbers"
print # Print opening sequence information
print "This program will calculate the sum between two numbers."
print "You will be prompted to enter the lower and upper limit of the numbers"
print "and the program will display all of the numbers between those numbers as a sum."
print
# Validation code
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print"Invalid input."
        valid = False
    else:
        valid = True
    return num,valid
# Promt user for lower and upper limits
run = True
while run:
    print # Validate
    valid = False
    while not(valid):
        lower = raw_input("Enter the lower number: ")
        lower,valid = isnumber(lower,valid)
    valid = False
    while not(valid):
        higher = raw_input("Enter the higher number: ")
        higher,valid = isnumber(higher,valid)
    if higher < lower:
        print "The higher number must be greater or equal to the lower number."
        continue
    print
    # Set total sum variable
    total = 0
    for x in range (lower,higher+1):
        # Print number and plus sign if not equal to higher number
        if x != higher:
            print x,"+",
        # Print just the number if last number in limits
        else:
            print x,
        # Running total (counter)
        total = total + x
    print "=",total # Print equals sign and total
    print
    # Ask user to repeat program
    response = raw_input("Would you like to try again with different limits?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print"Thankyou for using Sum Between Numbers Program!"
