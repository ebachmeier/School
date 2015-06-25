# Eric Bachmeier
# Palindrome.py - This program uses recursion to determine if a sentence or
# phrase is a palindrome.
# May 22, 2013

def reverse(p): # Define reverse function
    if len(p) == 0 or len(p) == 1:
        return True # Palindrome if one letter or less
    else:
        if p[0] != p[-1]:
            return False # Not a palindrome if first and last character are different
        else:
            p = p[1:-1] # Take off end letters for recheck
            return reverse(p)

print "Palindromes"
print "-----------"
print # Print introduction
print "A palindrome is a string whose letters read the same forward as backwards."
print
print "This program uses recursion to determine if a word or phrase is a palindrome."
repeat = True
while repeat:
    print
    word = raw_input("Enter a word or phrase: ") # Promt user for word or phrase
    new = word.upper() # Make user input all upper case
    new = new.replace(" ","") # Take out spaces
    palindrome = reverse(new) # Call reverse function to check for palindrome
    if palindrome == True: # If True is returned, input is a palindrome
        print "'"+word+"' is a palindrome."
    else:
        print "'"+word+"' is not a palindrome."
    print # Promt user to repeat 
    r = raw_input("Would you like to try again (Y/N): ")
    if r.upper() == "N" or r.upper() == "NO":
        repeat = False
