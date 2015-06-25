# Eric Bachmeier
# This program reads a plural noun, a verb and a singular noun from the text files and randomly generates sentences.
# Date Completed: December 14, 2011

filename = "Plurals.txt"
inFile = open(filename,"r")
plural_read = inFile.readline().rstrip("\n")
plurals = []
while plural_read != "":
    plurals.append(plural_read)
    plural_read = inFile.readline().rstrip("\n")
inFile.close()

filename = "Verbs.txt"
inFile = open(filename,"r")
verb_read = inFile.readline().rstrip("\n")
verbs = []
while verb_read != "":
    verbs.append(verb_read)
    verb_read = inFile.readline().rstrip("\n")
inFile.close()

filename = "Singulars.txt"
inFile = open(filename,"r")
sing_read = inFile.readline().rstrip("\n")
sing = []
while sing_read != "":
    sing.append(sing_read)
    sing_read = inFile.readline().rstrip("\n")
inFile.close()

print "Mad Lib Program"
print "---------------"
print
print "This program makes a MadLib sentence from the words read from the text"
print "files. The sentence is randomly generated and user is asked if they"
print "would like to generate."

import random
repeat = True
while repeat == True:
    pN = random.choice(plurals)
    V = random.choice(verbs)
    sN = random.choice(sing)
    print
    print "Your MadLib sentence is", pN, V, sN+"."
    print
    response = raw_input("Would you like to make another MadLib sentence? (Y/N) : ")
    if response == "N" or response == "n":
        repeat = False
print
print "Good bye!"
    
