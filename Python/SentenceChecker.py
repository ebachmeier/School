# Eric Bachmeier
# The purpose of the program is to tell if a sentence is proper.
# Date Completed: November 21, 2011

print "Sentence Checker"
print "----------------"
print
print "This program has the user enter a sentence and it will tell if it is a"
print "proper sentence bases on if it has a caputal and punctuation."
print
response = "Y"
while response == "Y" or response == "y":
    sentence = raw_input("Please enter a sentence: ")
    capital = False
    punctuation = False
    firstletter = sentence[0]
    if ord(firstletter) >= 65 and ord(firstletter) <= 90:
        print "The sentence begins with a capital."
        capital = True
    if sentence.endswith(".") or sentence.endswith("?") or sentence.endswith("!"):
        print "The sentence ends in punctuation."
        punctuation = True
    if capital == True and punctuation == True:
        print "This is a proper sentence."
    elif capital == False and punctuation == False:
        print "This sentence is missing a capital at the beginning of the"
        print "sentence and punctuation at the end."
        print "This is not a proper sentence."
    elif capital == False and punctuation == True:
        print "This sentence is missing a capital at the beginning of the sentence."
        print "This is not a proper sentence."
    elif capital == True and punctuation == False:
        print "This sentence is missing punctuation at the end."
        print "This is not a proper sentence."
    print
    response = raw_input("Would you like to input another sentence? (Y/N) ")
    print
print
print "Good bye!"
        
    
