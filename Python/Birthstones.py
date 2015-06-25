# Eric Bachmeier
# This program reads a plural noun, a verb and a singular noun from the text files and randomly generates sentences.
# Date Completed: December 21, 2011

print "Birthstone Program"
print "------------------"
print
print "Jewelry stores often sell birthday presents based on a person's"
print "birthstone. When a store clerk enters the number of the month, the"
print "correct birthstone is printed."

repeat = True
while repeat == True:
    print
    months = int(raw_input("Please enter a month number (1-12) : "))
    while months > 12 or months < 1:
        months = int(raw_input("Please enter a month number that is BETWEEN 1 and 12:"))
    month = ["","January","Febuary","March", "April", "May", "June", "July","August","September","October","November", "December"]
    modern=["","Garnet","Amethyst","Aquamarine","Diamond","Emerald","Pearl and Moonstone","Ruby","Peridot","Sapphire","Opal and Tourmaline","Yellow Topaz and Citrine","Blue Topaz and Turquoise"]
    traditional = ["","Garnet","Amethyst","Bloodstone","Diamond","Emerald","Alexandrite","Ruby","Sardonyx","Sapphire","Tourmaline", "Citrine","Zircon, Turquoise and Lapis Lazuli"]
    print
    print "The modern birthstone for", month[months],"is", modern[months]+"."
    print
    print "The traditional birthstone for", month[months],"is", traditional[months]+"."
    print

    response = raw_input("Would you like to make another MadLib sentence? (Y/N) :  ")
    if response == "N" or response == "n":
        repeat = False
print
print "Good bye!"
    
