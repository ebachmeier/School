# Eric Bachmeier
# Fibonacci.py - This program finds the Fibonacci number at the position
# specified by the user.
# May 21, 2013

def fib(n): # Define fibonacci function
    if n == 0 or n == 1: # Fibonacci number for 0 and 1st term is 1
        return 1
    else:
        return fib(n-1) + fib(n-2) # Add the previous two fibonacci numbers

print "Fibonacci Numbers"
print "-----------------"
print # Print introduction
print "Fibonacci numbers are listed as follows:"
print "\t"+"1, 1, 2, 3, 5, 8, 13, 21, 34 ..."
print "\t"+"where: F(0) = 1"
print "\t"+"       F(1) = 1"
print "\t"+"       F(n) = F(n-1) + F(n-2) for all n>=2"
print
print "This program uses recursion to find the nth Fibonacci number"
repeat = True
while repeat:
    print
    try: # Promt user for the value of n
        n = int(raw_input("Enter a value for n (negative number to quit the program): "))
    except BaseException: # Validate for integer
        print "Invalid input."
        continue
    if n < 0:
        repeat = False # Quit program if negative integer
    else:
        fibnum = fib(n) # Call fibonacci function to fibnum
        print "F("+str(n)+") = "+str(fibnum) # Print fibonacci number for nth term
        
