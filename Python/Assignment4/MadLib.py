# Eric Bachmeier
#      The purpose of this program is to randomly generate a sentence from a
# list of verbs, singular nouns, and plural nouns.
# Mar. 1, 2013

print"Mad Lib"
print # Print title sequence and intro
print"This program randomly picks one word from each list"
print"(plural nouns, verbs, singular nouns) and creates a"
print"potentially comical sentence."
# Import random library
import random
# Three one dimensional arrays for words
pn =["Cars","Houses","Cats","Dogs","Cows","Eggs","Apples","Bottles","Queeens","Books","Boards","Stores","Televisions","Grapes","Photos","Daises","Cups","Bowls","Pots","Pans"]
v =["accept","wipe","hit","cut","slice","cook","jump","spank","dive","sprint","calculate","squeeze"]
sn =["apartment","crow","alligator","muffin","log","paper","knife","lizzard","dock","rock","building"]
run = True
while run:
    # Define random choice for plural noun
    pnoun = random.randint(0,19)
    # Define random choice for verb
    verb = random.randint(0,11)
    # Define random choice for singular noun
    snoun = random.randint(0,10)
    print
    print pn[pnoun], # Print plural noun
    print v[verb], # Print verb
    print sn[snoun]+"." # Print singular noun and period
    # Ask user to repeat program
    repeat = True
    while repeat:
        response = raw_input("Would you like to generate another random sentence?(y/n): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using MadLib!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
