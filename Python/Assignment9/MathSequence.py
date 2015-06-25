# Eric Bachmeier
# MathSequence.py - This program displays the nth term of the defined pattern
# May 23, 2013

def math(n): # Define math function to find term
    if n == 1:
        return 2 # Term is 2 when n == 1
    else:
        return (3 * math(n-1) - 1) # Use sequence formula with previous term
    
print "Math Sequence"
print "-------------"
print # Print introduction
print "The following sequence is defined as follows:"
print "\t t(1) = 2"
print "\t t(n) = 3 * t(n-1) – 1"
print
print "This program uses recursion to find the nth term of the sequence."
print
repeat = True
while repeat:
    try: # Promt user for value
        n = int(raw_input("Enter a value for n (0 to quit the program): "))
    except BaseException: # Validate integer
        print "Please enter a valid integer number."
        continue
    if n < 0: # Validate positive integer
        print "Please enter a valid integer number."
        continue
    elif n == 0: # Quit program if '0' is entered
        repeat = False
    else:
        s = math(n) # Set s to the term called by math
        print "t("+str(n)+") = "+str(s) # Print answer
