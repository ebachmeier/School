# Eric Bachmeier
# This purpose of this program is to find the value of a word.
# Date Completed: November 24, 2011

print "Word Value Program"
print "------------------"
print
print "This program has users enter a word and the program will return"
print "the value of the word."
print
repeat = True
while repeat == True:
    w = raw_input("Enter a word: ")
    while w.isalpha() == False or w.isdigit() == True:
        w = raw_input("Enter a word that has only letters:")
    w = w.upper()
    value = 0
    for letter in w:
        value = value + ord(letter)-64
    print "The Value of the word is", value, "."
    print
    response = raw_input("Would you like to find the value of another word (Y/N): ")
    print
    while response == "n" or response == "N":
        repeat = False
print
print "Good bye!"



