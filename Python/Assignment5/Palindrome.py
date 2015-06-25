# Eric Bachmeier
#      The purpose of this program is to determine if a word or phrase entered
# by the user is a palindrome or not.
# Mar. 18, 2013

print"Palindrome Checker"
print # Print title sequence and intro
print"A palindrome is a word or phrase that is spelled the same backwards"
print"and forwards, such as madam, Dad, or Race car. This program determines"
print"if a word or phrase entered by the user is a palindrome."
run = True
while run:
    print
    p = raw_input("Enter a word or phrase: ") # Promt user for word/phrase
    cap = p.upper() # Make all uppercase
    new = "" # Create new as a blank string
    reverse = "" # Create reverse as a blank string
    for x in range(0,len(p)):
        asci = ord(cap[x]) # Give ascii value to each character
        if asci in range(65,91):
            new = new + cap[x] # Add it to new list if it is a letter, not a space
    for i in range(len(new)-1,-1,-1):
        reverse = reverse + new[i] # Reverse the list
    if reverse == new:
        print "'"+p+"' is a palindrome." # If word reversed is the same it IS a palindrome
    else:
        print "'"+p+"' is NOT a palindrome." # Otherwise, NOT a palindrome
    # Ask user to repeat program
    repeat = True
    while repeat:
        response = raw_input("Would you like to try again?(y/n): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Palindrome Checker!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
