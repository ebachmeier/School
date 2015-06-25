# Eric Bachmeier
# This purpose of this program is to find the shortest amd longest words
# in the sentence.
# Date Completed: November 30, 2011

print "Sentence Word Lengths"
print "---------------------"
print
print "This program finds the longest and shortest words in a sentence. It"
print "outputs the word to the user."
print
repeat = True
while repeat == True:
    sent = raw_input ("Enter a phraase or word: ")
    newSent = ""
    for x in range (0,len(sent)):
        value = ord(sent[x])
        if 65 <= value <= 90:
            value = value + 13
            if value > 90:
                value = value - 26
        elif 97 <= value <= 122:
            value = value + 13
            if value > 122:
                value = value - 26
        newSent = newSent + chr(value)
    print "The encrypted phrase is " + newSent
    print
                
    response = raw_input("Would you like to try again? (Y/N) : ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
