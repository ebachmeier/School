# Eric Bachmeier
#      The purpose of this program is to crack the message that is encrypted 
# using a Caesar cipher.
# Mar. 21, 2013

print"Caesar Cipher"
print # Print title sequence and intro
print"Caesar ciphers are the easiest codes to create and crack. The code"
print"consists of shifting the letters of a message over a constant number"
print"of characters. A Caesar cipher of 5, for example, would shift over the"
print"letters five characters: the letter 'A' becomes an 'F' , the letter 'B'"
print"a 'G' and so on. The letter 'Z' would wrap around and become an 'E'."
print
print"Since the most common letter in the English language is the letter E,"
print"most Caesar codes can be broken simply by checking which letter in the"
print"message is the most common."
print
print"This program will crack a message that used a Caesar cipher."
run = True
while run:
    w = raw_input("Enter a word or phrase to decipher: ") # Promt user for word/phrase
    w = w.upper() # Capitalize string
    freq = [0 for x in range(0,26)] # Make blank list of zeroes
    alpha  = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'] # Make blank list of alphabet
    for i in range(0,len(w)):
        ascii = ord(w[i]) # Return ascii of each letter in phrase
        if ascii != 32: # If is not a space
            freq[ascii-65]+=1 # Add one to the occurence count of that number
    high = 0 # Set high to 0 to be the highest frequency
    index = 0 # Index to zero to be the position of the letter in alpha
    for p in range(0,len(freq)):
        if freq[p] > high: # Find highest number frequency
            high = freq[p] # Find out most occuring letter
            index = p # Find out location in the alphabet
    cipher = (ord(alpha[index+1])-65)-5 # Shift is the ord of the letter compared to 'E'
    new = "" # Make new blank string
    for g in range(0,len(w)):
        ascii = ord(w[g])
        if ascii != 32: # If not a space
            ascii = ord(w[g])-65
            ascii-=cipher # Reverse the letter using the cipher shift
            while ascii > 26:
                ascii-=26 # Loop around back to 'A'
            while ascii < 0:
                ascii+=26 # Loop around to 'Z'
            new+=(alpha[ascii]) # Add reversed (decoded) letter to 'new'
        else:
            new+=w[g] # If its a space just add to 'new'
    print
    print "The cipher has a shift of", str(cipher)+"..." # Print the shift used
    print
    print "The decrypted phrase is",new # Print the decrypted phrase
    repeat = True
    while repeat:
        print  # Ask user to repeat program
        response = raw_input("Would you like to try again?(y/n): ") 
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Caesar Cipher!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
            print
        else:
            print "Invalid input."
            repeat = True
        
