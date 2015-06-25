# Eric Bachmeier
# The purpose of this program is prompt the user for the names and scores of 4 golfers and print the
# scorecard and which holes each player won.
# May 8, 2013

print "Golf Game Application"
print "---------------------"
print # Print title
card = [[0 for column in range(0,9)]for row in range(0,4)] # Generate card with all zero scores
players = [[0],[0],[0],[0]] # Create blank list of players set to 0
for p in range(0,4):
    name = raw_input("Player "+str(p+1)+"....Enter your name: ") # Promt players for name
    players[p].append(name) # Append name to players list
print
for column in range(0,9):
    for row in range(0,4):
        valid = False
        while not(valid):
            try: # Promt user for score on certain hole
                num = int(raw_input(str(players[row][1]).ljust(12,".")+"Enter your score for Hole "+str(column+1)+": "))
            except:
                valid = False
                print "Invalid input"
            else:
                if num > 0:
                    valid = True # Valid input only if an integer
        card[row][column] = num # Assign that number to the scorecard
for column in range(0,9):
    win = -1
    low = 100
    for row in range(0,4):
        if card[row][column] < low: # Find lowest score for each hole
            low = card[row][column] # Update low
            win = row # Set what player one by row
        elif card[row][column] == low:
            low = card[row][column] # If another player has same low score keep win at -1
            win = -1 
    if win == -1:
        pass # No winners if hole has a tie
    else:
        players[win][0] += 1 # Add a win to player number that won
        players[win].append(column+1) # Append what hole they won
print
print" ".rjust(12),"Hole 1".rjust(6),"Hole 2".rjust(6),"Hole 3".rjust(6),"Hole 4".rjust(6),"Hole 5".rjust(6),"Hole 6".rjust(6),"Hole 7".rjust(6),"Hole 8".rjust(6),"Hole 9".rjust(6) # Print table headings
for row in range(0,4):
    print players[row][1].ljust(12), # Print player name for each row
    for column in range(0,9):
        print str(card[row][column]).center(6), # Print score for each player in proper column
    print
print
for p in range(0,4):
    print players[p][1],"won",players[p][0], # Print player name and number of wins
    if players[p][0] == 1:
        print "Hole :", # Singular for one win
    else:
        print "Holes:", # Plural for more than one win
    if players[p][0] == 0:
        print "N/A", # N/A for no win holes
    else:
        for h in range(2,len(players[p])):
            print "Hole",players[p][h], # Print the hole names and numbers after corresponding player
    print

