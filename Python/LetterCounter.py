# Eric Bachmeier
#      The purpose of this program is to determine the number of vowels and 
# consonants in a word or phrase entered by the user.
# Mar. 19, 2013

print"Letter Counter"
print # Print title sequence and intro
print"This program counts the number of vowels and consonants in a word or phrase."
run = True
while run:
    print
    w = raw_input("Enter a word or phrase: ") # Promt user for word/phrase
    p = w.upper() # Capitalize string
    v = 0 # Create vowel counter 0
    c = 0 # Create consonant counter 0
    for x in range(0,len(w)):
        ascii = ord(p[x])
        if ascii in(65,69,73,79,85,89,97,101,105,111,117,121):
            v+=1 # Add vowel to count if ascii is that of a vowel
        elif ascii not in(65,69,73,79,85,89,97,101,105,111,117,121) and (ascii > 65 and ascii < 91):
            c+=1 # If not in the vowel ascii range and is a letter add to consonant count
    if v == 1:
        y = "vowel" # Vowel singular
    else:
        y = "vowels" # Vowel plural
    if c == 1:
        g = "consonant" # C singular
    else:
        g = "consonants" # C plural
    print "The phrase '"+w+"' has", v, y, "and", c, g+"." # Print counts
    repeat = True
    while repeat:
        response = raw_input("Would you like to try again?(y/n): ") # Ask user to repeat program
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Letter Counter!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
