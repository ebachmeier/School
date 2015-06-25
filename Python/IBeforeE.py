print "I before E except after C Program"
print "---------------------------------"
print
print "This program has users enter a word and the program will ask them if it"
print "is spelled correctly."
print

repeat = True
while repeat == True:
    word = raw_input("Please enter a word: ")
    i = word.find("ie")
    if i <> -1:
        letterbefore = word[i-1]
        if letterbefore <> "c":
            print "This word could be correctly spelled because it contains ie."
        else:
            print "This word does not follow the rule I before E, except after C."
    else:
        print "This word does not have an ie in it."
    e = word.find("ei")
    if e <> -1:
        letterbefore=word[e-1]
        if letterbefore == "c":
            print "This word could be correctly spelled because it contains ei and the letter before it is a c."
        else:
            print "This word does not follow the rule I before E, except after C."
    else:
        print "This word does not have an ei in it."
    print
    response = raw_input("Would you like to check another word? (Y/N) ")
    print
    if response == "n" or response == "N":
        repeat = False
        
