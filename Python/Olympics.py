# - Eric Bachmeier
# - The purpose of this program is 
# - Date Completed: January 12, 2012

print "Vancouver 2010 Olympics Stats Program"
print "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
print
print "This program will have users choose if they would like to view stats"
print "for a specific event or if they would like to see the medal total count"
print "for each country. The stats are imported from text files with"
print "corresponding names. The stats can be updated or changed to work for"
print "other olympics if the text files are updated manually."
print
repeat = True
while repeat == True:
    menu = raw_input ("Would you like to view an INDIVIDUAL event statistics or the medal TOTAL for all of the countries in the main 10 events? (INDIVIDUAL / TOTAL) : ")
    if menu == "INDIVIDUAL" or menu == "Individual" or menu == "individual":
        print
        print "Here are the events in the Vancouver 2010 Olympics that you can choose from for individual events:"
        print
        print "1 - Alpine Skiing"
        print "2 - Biathlon"
        print "3 - Curling"
        print "4 - Figure Skating"
        print "5 - Freestyle Ski"
        print "6 - Ice Hockey"
        print "7 - Luge"
        print "8 - Ski Jump"
        print "9 - Snowboarding"
        print "10 - Speed Skating"
        print
        events = ["","Alpine Skiing.txt", "Biathlon.txt", "Curling.txt", "Figure Skating.txt", "Freestyle Ski.txt", "Ice Hockey.txt", "Luge.txt", "Ski Jump.txt", "Snowboarding.txt", "Speed Skating.txt"]
        event = int (raw_input ("What corresponding event NUMBER from the ones listed above would you like to see the stats for? (#) : "))
        filename = events[event]
        names = []
        cons = []
        inFile = open(filename, "r")
        name_read = inFile.readline().rstrip("\n")
        con_read = inFile.readline().rstrip("\n")
        while name_read != "":
            names.append(name_read)
            cons.append(con_read)
            name_read = inFile.readline().rstrip("\n")
            con_read = inFile.readline().rstrip("\n")
        for x in range (0,len(names)):
            print names[x], cons[x]
        inFile.close()
    if menu == "TOTAL" or menu == "Total" or menu == "total":
        print
        
response = raw_input("Would you like yo repeat with another event? (Y/N): ")
if response == "n" or response == "N":
    repeat = False
print
print "Good bye!"

