# Eric Bachmeier
#      This program promts the user for an amount of change under 100 cents
# and makes change with the least amount of coins.
# Feb. 7, 2013

print "Change Maker"
print # Print introduction information
print "You will enter an amount of change under 100 cents, and this program will"
print "make change for it. It will do so using the least amount of coins possible."
print
# Validate number of cents 
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print "Invalid input."
    else:
        if num <= 0 or num > 100:
            print "Invalid input."
        else:
            valid = True
    return num,valid
run = True
while run:
    print
    valid = False
    while not(valid):
        # Promt user for amount of cents
        a = raw_input ("Please enter an amount of cents less than 100: ")
        a,valid = isnumber(a,valid)
    # Calculate number of each coin needed
    q = a/25
    d = (a-(q*25))/10
    n = (a-(q*25+d*10))/5
    p = (a-(q*25+d*10+n*5))/1
    print a,
    # Print statenments
    if a == 1:
        print "cent",
    else:
        print "cents",
    print "requires:"
    print
    if q == 1:
        print q,
        print "quarter"
    elif q > 1:
        print q,
        print "quarters"
    if d == 1:
        print d,
        print"dime"
    elif d > 1:
        print d,
        print"dimes"
    if n == 1:
        print n,
        print"nickel"
    elif n > 1:
        print n,
        print"nickels"
    if p == 1:
        print p,
        print"penny"
    elif p > 1:
        print p,
        print"pennies"
    print
    # Ask to repeat
    response = raw_input("Would you like to enter a new amount?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print "Thankyou for using Change Maker!"
    
    
        
