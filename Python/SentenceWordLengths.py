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
    sentence = raw_input ("Enter a sentence (end with a period): ")
    sentence = sentence.replace("."," ")
    sentence = " " + sentence
    shortest = 999
    longest = -999
    position = 0
    while position <> - 1:
        positionSpace = sentence.find(" ",position+1)
        if positionSpace <> - 1:
            wordLength = positionSpace - position - 1
            if wordLength > longest:
                longest = wordLength
            if wordLength < shortest:
                shortest = wordLength
        position = positionSpace
    print
    print "The longest word(s) have", longest, "letter(s) in it."
    print "The words are:",
    position = 0
    while position <> - 1:
        positionSpace = sentence.find(" ", position+1)
        if positionSpace <> - 1:
            wordLength = positionSpace - position - 1
            if wordLength == longest:
                print sentence[position+1:positionSpace],
        position = positionSpace
    print
    print "The shortest word(s) have", shortest, "letter(s) in it."
    print "The words are:",   
    position = 0
    while position <> - 1:
        positionSpace = sentence.find(" ", position+1)
        if positionSpace <> - 1:
            wordLength = positionSpace - position - 1
            if wordLength == shortest:
                print sentence[position+1:positionSpace],
        position = positionSpace
    print
    print
    response = raw_input("Would you like to try again? (Y/N) : ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
