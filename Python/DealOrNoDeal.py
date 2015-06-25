# Eric Bachmeier
# This program is like the NBC game show Dealor No Deal. It asks the user deal or
# no deal after calculating the average of the unopened cases.
# November 8, 2011

print "Deal or No Deal"
print "---------------"
print
print "In the STA ICS3U version of the game, there are 10 possible dollar"
print "amounts: $100, $500, $1000, $5000, $10000, $25000, $50000, $100000,"
print "$500000, $1000000 sealed in imaginary briefcases."
print
filename = "DealOrNoDeal.txt"
inFile = open(filename,"r")
caseopen = int(inFile.readline().rstrip("\n"))
print caseopen,"cases have been opened."
casegone = 0
for case in range (0, (int(caseopen))):
    case = int(inFile.readline().rstrip("\n"))
    if case == 1:
        casegone = casegone + 100
        print "The $100 case has been eliminated."
    if case == 2:
        casegone = casegone + 500
        print "The $500 case has been eliminated."
    if case == 3:
        casegone = casegone + 1000
        print "The $1000 case has been eliminated."
    if case == 4:
        casegone = casegone + 5000
        print "The $5000 case has been eliminated."
    if case == 5:
        casegone = casegone + 10000
        print "The $10000 case has been eliminated."
    if case == 6:
        casegone = casegone + 25000
        print "The $25000 case has been eliminated."
    if case == 7:
        casegone = casegone + 50000
        print "The $50000 case has been eliminated."
    if case == 8:
        casegone = casegone + 100000
        print "The $100000 case has been eliminated."
    if case == 9:
        casegone = casegone + 500000
        print "The $500000 case has been eliminated."
    if case == 10:
        casegone = casegone + 1000000
        print "The $1000000 case has been eliminated."
offer = inFile.readline().rstrip("\n")
print "The banker's offer is $",offer
total = 100 + 500 + 1000 + 5000 + 10000 + 25000 + 50000 + 100000 + 500000 + 1000000
leftcases = 10 - (int(caseopen))
average = (total - casegone)/leftcases
print "The average of the remaining amounts is $", average
print
if average > offer:
    print "No Deal"
elif offer > average:
    print "Deal"



