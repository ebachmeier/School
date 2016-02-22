# Eric Bachmeier
#      The purpose of this program is to return the smallest prime factor of a number.
# Apr. 26, 2013

def Factor(Number): # Define find smallest factor functions
    factors = [] # Create blank factors list
    for x in range(2,abs(int(Number))+1): 
        if int(Number)%(x) == 0: # Prime if no remainder
            prime = True
            for i in range(2,x):
                if x%i == 0:
                    prime = False # False if not a factor AND prime
                    break
            if prime == True:
                factors.append(x) # Append factors to factors list
    return factors

def isnum(num,valid): # Define number input validation
    try:
        num = int(num) # True for integer
    except:
        print "Invalid input."
        valid = False
    else:
        valid = True
    return num,valid

print "Smallest Factor"
print "---------------"
print # Print introduction
print "This program finds the smallest prime factor of a number."
run = True
while run:
    print
    valid = False
    while not (valid): # Prompt user for side length
        Number = raw_input("Enter the number that you wish to find the smallest prime factor for: ")
        Number,valid = isnum(Number,valid) # Validate input
    low = Factor(Number) # Lowest prime factor set to low
    print "The smallest prime factor of "+str(Number)+" is "+str(low[0]) # Print smallest prime factor
    print
    repeat = True
    while repeat: # Promt user to repeat
        response = raw_input("Would you like to try again?(Y/N): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Smallest Factor Program!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
