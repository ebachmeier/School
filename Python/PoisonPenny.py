# Eric Bachmeier
# Date Compleetd: October 7, 2011

print "Poison Penny"
print "------------"
print
print "Poison penny is a game for two players. Twelve pennies and a nickel"
print "are laid out. Each player can take one or two pennies, alternating"
print "turns until only the nickel (the poison) is left. Whoever's turn it is,"
print "when only the poisoned nickel is left, loses."
print
repeat = True
while repeat == True:
    pennies = 12
    nickel = 1
    player = 1
    #enter player names
    player1 = raw_input ("Enter player 1's name: ")
    player2 = raw_input ("Enter player 2's name: ")
    while nickel == 1:
        print "There are ", pennies, "pennies and ", nickel, "nickel left."
        print
        valid = 0
        while valid == 0:
            if player == 1:
                pick = int (raw_input (player1 + ", how many pennies do you wish to take? "))
            else:
                pick = int (raw_input (player2 + ", how many pennies do you wish to take? "))

            if pick > 2 or pick > pennies or pick < 1:
                valid = 0
            else:    
                pennies = pennies - pick
                valid = 1

                # check for end of game
                if pennies == 0:
                    print
                    if player == 1:
                        #player1 wins
                        print player2 +", you lose because you must take the nickel."
                        print "Congratulations " + player1 +", you are the winner."
                        nickel = 0
                    else:
                        #player2 wins
                        print player1 +", you lose because you must take the nickel."
                        print "Congratulations " + player2 +", you are the winner."
                        nickel = 0
                else:
                    #switch players
                    if player == 1:
                        player = 2
                    else:
                        player = 1
    print
    loop = 1
    while loop == 1:
        response = raw_input ("Would you like to play again? (Y/N): ")
        if response == "n" or response == "N":
            repeat = False
            loop = 0
        elif response == "y" or response == "Y":
            repeat = True
            loop = 0
            print
        else:
            print "Please enter a valid response eg. (Y/N)"
                       
               
print
print "GAME OVER!"
print
print "Thanks you for playing. Come back soon."
            
        
    
