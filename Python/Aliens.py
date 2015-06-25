# Eric Bachmeier
# The purpose of this program is to have the user input the number of eyes and
# antenna, and tell them what type of alien it may be.
# Date Completed: November 1, 2011

print "Aliens Program"
print "--------------"
print
print "The STA Cosmos Control (STACC) has received a report of another alien"
print "incident. They believe that an alien has illegally entered our space."
print "An STA student who witnessed the appearance of the alien has come"
print "forward to describe the alien's appearance. It is your role within the"
print "STACC to determine which alien has arrived. There are only 3 alien"
print "species that we are aware of, described below:"
print
print "> BobMartian, who has at least 3 antenna and at most 4 eyes;"
print "> StephSaturnian, who has at most 6 antenna and at least 2 eyes;"
print "> LynneMercurian, who has at most 2 antenna and at most 3 eyes."
print
alien = False
repeat = True
while repeat == True: 
    # eyes = number of eyes on alien
    eyes = int(raw_input ("How many eyes? " ))
    # antenna = number of eyes on alien
    antenna = int(raw_input ("How many antennas? " ))
    if antenna >= 3 and eyes <= 4:
        print "The alien may be a BobMartian."
        alien = True
    if antenna <= 6 and eyes >= 2:
        print "The alien may be a StephSaturnian."
        alien = True
    if antenna <= 2 and eyes <= 3:
        print "The alien may be a LynneMercurian."
        alien = True
    if alien == False:
        print "No alien matches your description."
    print
    response = raw_input ("Would you like to input more numbers? (Y/N): ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
