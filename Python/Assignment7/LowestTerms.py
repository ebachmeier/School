# Eric Bachmeier
#      The purpose of this program is to find the greatest common factor
# between two integers and return the lowest mixed terms fraction.
# Apr. 30, 2013

def GCD(n,d): # Define day number function
    fact = 0
    for x in range(2,n+1):
        if d%x == 0 and n%x == 0: # Factor works if both remainders are 0
            fact = x # Fact is the great common factor
    return fact
    
def isnum(num,valid): # Define number input validation
    try:
        num = int(num) # True for integer
    except:
        print "Invalid input."
        valid = False
    else:
        if num < 1:
            print "Invalid input."
            valid = False
        else:
            valid = True
    return num,valid

print "Lowest Terms"
print "------------"
print # Print introduction
print "This program reduces a fraction into its lowest mixed terms."
run = True
while run:
    print
    valid = False
    while not (valid): # Prompt user for numerator
        n = raw_input("Enter the numerator of the fraction: ")
        n,valid = isnum(n,valid) # Validate input
    valid = False
    while not (valid): # Prompt user for denominator
        d = raw_input("Enter the denominator of the fraction: ")
        d,valid = isnum(d,valid) # Validate input
    print
    print "The fraction "+str(n)+"/"+str(d)+" reduces to", # Print original fraction
    div = GCD(n,d) # Call GCD to div
    if div != 0:
        n /= div # Reduce the fraction with divisor
        d /= div
    if n > d:
        w = n/d # Find whole number if numerator is greater
        n = n%d
        if n > 0:
            print str(w)+" "+str(n)+"/"+str(d) # Print mixed fraction
        else:
            print w # Print whole number if it divides with no remainder
    else:
        if n == d:
            print n # Print numerstor if same as denominator
        else:
            print str(n)+"/"+str(d) # Print fraction if denominator greater
    print # Promt user to repeat
    response = raw_input("Would you like to try again?(Y/N): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
    
