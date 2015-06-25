# - Eric Bachmeier

# - The purpose of this program is to perform two main tasks. It can display
#   the stats for an individual event, or the total medal count for all the top
#   10 events for countries. The significance of this program is that it can
#   display the stats even when the text files are updated for another olympic
#   games or changed. It is useful for anybody who wants to see Olympic stats
#   easily and efficiently. It is easy to use, user friendly, and works with
#   all numbers of stats in the text files for the events.

# - Date Completed: January 19, 2012

print "Vancouver 2010 Olympics Stats Program"
print "-------------------------------------"
print # introduction
print "This program will have users choose if they would like to view stats"
print "for a specific event or if they would like to see the medal total count"
print "for each country. The stats are imported from text files with"
print "corresponding names. The stats can be updated or changed to work for"
print "other olympics if the text files are updated manually. The default stats"
print "are for the Vancouver 2010 Winter Olympics. Enjoy!"
repeat = True
while repeat == True: # events list .txt files
    events = ["","Alpine Skiing.txt", "Biathlon.txt", "Curling.txt", "Figure Skating.txt", "Freestyle Ski.txt", "Ice Hockey.txt", "Luge.txt", "Ski Jump.txt", "Snowboarding.txt", "Speed Skating.txt"]
    valid = 0 
    while valid == 0:
        print
        menu = raw_input ("Would you like to view an INDIVIDUAL [I] event statistics or the medal TOTAL [T] for all of the countries in the main 10 events? [I/T] : ")
        # ask user for individual or total
        if menu == "I" or menu == "i":
            valid = 1
            # user chooses individual event stats
            print
            print "Here are the events in the Vancouver 2010 Olympics that you can choose from for individual events:"
            print # user can choose from following numbered events
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
            checknum = 0
            while checknum == 0:                
                input = raw_input ("What corresponding event NUMBER [#] from the ones listed above would you like to see the stats for? [#] : ")
                if input.isdigit():
                    event = int(input)
                    if event > 0 and event < 11:
                        checknum = 1  
                else:
                    checknum = 0
            filename = events[event] # import proper event .txt file
            names = [] # create blank lists for names and countries
            cons = []
            inFile = open(filename, "r") # open file
            name_read = inFile.readline().rstrip("\n") # read name
            con_read = inFile.readline().rstrip("\n") # read country
            print
            print " ".ljust(10), "Name".ljust(20), "Country".ljust(40) # create table to display stats
            print " ".ljust(10), "----".ljust(20), "-------".ljust(40)
            while name_read != "":
                names.append(name_read) # add reads to list for table data
                cons.append(con_read)
                name_read = inFile.readline().rstrip("\n")
                con_read = inFile.readline().rstrip("\n")
            print "GOLD - ".ljust(10), names[0].ljust(20), cons[0].ljust(40) # ljust data for organized display
            print "SILVER - ".ljust(10), names[1].ljust(20), cons[1].ljust(40)
            print "BRONZE - ".ljust(10), names[2].ljust(20), cons[2].ljust(40)
            inFile.close() # close file
        elif menu == "T" or menu == "t":
            valid = 1
            # user chooses total medals
            countries = [] # countries list empty
            # list of gold, silver, bronze for each country in the format [0, 0, 0]
            medals = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]
            inFile = open("COUNTRIES.txt", "r") # open country names .txt file
            country_read = inFile.readline().rstrip("\n") # read and add countries to list countries
            while country_read != "":
                countries.append(country_read) # add read to list
                country_read = inFile.readline().rstrip("\n")
            inFile.close()
            # open the file for each event
            for x in range (1, len(events)):
                filename = events[x]
                inFile = open(filename, "r") # open file
                scrap = inFile.readline().rstrip("\n") # scrap the name
                con_gold = inFile.readline().rstrip("\n") # reads the gold medal country name
                con_num = countries.index(con_gold) # finds the country number [0-13] in countries list
                temp = medals[con_num][0] # check current medal count for gold
                medals[con_num][0] = temp + 1 # add the new gold medal
                scrap = inFile.readline().rstrip("\n")
                con_silver = inFile.readline().rstrip("\n")
                con_num = countries.index(con_silver)
                temp = medals[con_num][1]
                medals[con_num][1] = temp + 1
                scrap = inFile.readline().rstrip("\n")
                con_bronze = inFile.readline().rstrip("\n")
                con_num = countries.index(con_bronze)
                temp = medals[con_num][2]
                medals[con_num][2] = temp + 1
                inFile.close()
            print
            print "Country".ljust(10), "GOLD".ljust(10), "SILVER".ljust(10), "BRONZE".ljust(10)
            print "-------".ljust(10), "----".ljust(10), "------".ljust(10), "------".ljust(10)
            for n in range (0, len(countries)):
                # print the medal count and country name in table
                print countries[n].ljust(10), str(medals[n][0]).ljust(10), str(medals[n][1]).ljust(10), str(medals[n][2]).ljust(10)
            print
        # repeat
        else:
            valid = 0
    print
    check = 0
    while check == 0:
        response = raw_input("Would you like to repeat the program? (Y/N): ")
        if response == "n" or response == "N":
            check = 1
            repeat = False
        elif response == "y" or response == "Y":
            check = 1
            repeat = True
        else:
            check = 0
print
print "Thank you for using my Olymics program, Good bye!"
