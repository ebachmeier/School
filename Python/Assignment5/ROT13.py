# Eric Bachmeier
#      The purpose of this program is to encrypt and decrypt a message using 
# the ROT13 cipher, shifting each letter by 13.
# Mar. 20, 2013

print"ROT13 Cipher"
print # Print title sequence and intro
print "A simple kind of encryption for words is ROT13. In ROT13, letters of"
print "the alphabet are changed with each other using a simple pattern. For"
print "example, A changes to N, B changes to O, C changes to P, and so on."
print "Each letter is 'rotated' by 13 letters."
run = True
while run:
    print
    w = raw_input("Enter a word or phrase: ") # Promt user for word/phrase
    decode = "" # Create blank decode string
    for x in range(0,len(w)):
        ascii = ord(w[x]) # Return ascii of each character
        if ascii in range(65,91):
            ascii-=65 # Subtract 65 from ascii value if if capital letter
            ascii+=13 # Shift 13 for ROT13 cipher
            while ascii>25:
                ascii-=26 # Subtract 26 if greater than 25 so it remains in alphabet
            ascii+=65 # Add 65 to get back to capital letter ascii
        elif ascii in range(97,123):
            ascii-=97 # Subtract 97 from ascii value if a lower case letter
            ascii+=13 # Shift 13 for ROT13 cipher
            while ascii>25:
                ascii-=26# Subtract 26 if greater than 25 so it remains in alphabet
            ascii+=97 # Add 97 to get back to lower case letter ascii
        decode+=chr(ascii)
    print "The encrypted phrase is", decode+"." # Print decoded phrase/word

    # Ask user to repeat program
    
    repeat = True
    while repeat:
        print
        response = raw_input("Would you like to try again?(y/n): ") 
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using ROT13!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
