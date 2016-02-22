# Eric Bachmeier
# The purpose of this program is print the scorecard for 9 holes and which
# holes each player won.
# May 7, 2013

print "Golf Game Application"
print "---------------------"
print # Print title
import random # Import random library
card = [[0 for column in range(0,9)]for row in range(0,4)] # Generate card with all zero scores
p1 = 0 # Set player wins all to zero
p2 = 0
p3 = 0
p4 = 0
players = [[p1],[p2],[p3],[p4]] # Create blank list of players
print" ".rjust(11),"Hole 1".rjust(6),"Hole 2".rjust(6),"Hole 3".rjust(6),"Hole 4".rjust(6),"Hole 5".rjust(6),"Hole 6".rjust(6),"Hole 7".rjust(6),"Hole 8".rjust(6),"Hole 9".rjust(6) # Print table headings
for column in range(0,9):
    win = -1
    low = 100
    for row in range(0,4):
        num = random.randint(1,9)
        card[row][column] = num # Set random scores between 1 and 9 for each hole
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
for row in range(0,4):
    print "Player "+str(row+1)+"   ", # Print player name for each row
    for column in range(0,9):
        print str(card[row][column]).center(6), # Print score for each player in proper column
    print
print
for p in range(0,4):
    print "Player",p+1,"won",players[p][0], # Print player name and number of wins
    if players[p][0] == 1:
        print "Hole :", # Singular for one win
    else:
        print "Holes:", # Plural for more than one win
    if players[p][0] == 0:
        print "N/A", # N/A for no win holes
    else:
        for h in range(1,len(players[p])):
            print "Hole",players[p][h], # Print the hole names and numbers after corresponding player
    print

    







