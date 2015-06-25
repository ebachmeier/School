# Eric Bachmeier
# Jumble.py - This program shows all the letter combinations of the entered word.
# May 27, 2013

import math # Import math library
def var(w,n,c): # Define the functipn to jumble the letters
    if not w:
        if c < 1: # Print new word without comma if last one
            print n
        else:
            print n+",", # Print new word followed by a comma
    for x in range(0,len(w)):
        var(w[:x]+w[x+1:],n+w[x],c) # Re-arrange and add to 'n'
        c -= 2
        
print "Jumble"
print "------"
# Print introduction
repeat = True
while repeat:
    print
    word = raw_input("Enter a string of characters: ") # Prompt user for word
    print
    print "All possible combinations of the letters are:"
    fact = math.factorial(len(word)) # Factorial of word length to 'fact'
    var(word,"",fact) # Call the function with word, blank 'n', and number of possibilities
    print
    r = raw_input("Would you like to try again? (Y/N): ") # Prompt user to repeat
    if r.upper() == "N" or r.upper() == "NO":
        repeat = False
