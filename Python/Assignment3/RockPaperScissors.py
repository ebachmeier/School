# Eric Bachmeier
#      The purpose of this program is to allow you to play rock paper scissors
# against the computer and keep score. Also determine an overall winner.
# Feb. 22, 2013

print "Rock, Paper, Scissors"
print "---------------------"
print # Print opening sequence information
print "This program will allow you to play the game Rock, Paper, Scissors"
print "against the computer."
print
print "In this case, it is a race to 3 (three) wins."
# Import Math and Random libraries
import math
import random
# Validation code, ensure number is between 1 and 3
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print "Invalid input."
    else:
        if num < 1 or num > 3:
            print "Invalid input."
        else:
            valid = True
    return num,valid
# Make list of choices
choices = ["rock","paper","scissors"]
run = True
while run:
    pwin = 0
    cwin = 0
    ties = 0
    print # Promt user for name
    name = raw_input("Enter your name: ")
    while pwin < 3 and cwin < 3:
        print
        valid = False
        while valid == False:
            # Define random computer pick
            def compchoice():
                compchoice = random.randint(1,3)
                return compchoice
            # Promt user to choose rock, paper, or scissors
            choice = raw_input(name+", what is your choice (1-rock, 2-paper, 3-scissors : ")
            choice,valid = isnumber(choice,valid)
            if valid and (choice > 3 or choice < 1):
                valid = False
                print "Invalid input"
            compchoice = compchoice()
            # If statements for 9 different scenarios of outcome
        if choice == 1 and compchoice == 1:
            print name+",","you picked rock and so did the computer. It is a tie."
            ties = ties + 1
        elif choice == 1 and compchoice == 2:
            print name+",","your rock gets covered by the computers paper. You lose."
            cwin = cwin + 1
        elif choice == 1 and compchoice == 3:
            print name+",","your rock smashes the computers scissors. You win!"
            pwin = pwin + 1
        elif choice == 2 and compchoice == 1:
            print name+",","your paper covers the computers rock. You win!"
            pwin = pwin + 1
        elif choice == 2 and compchoice == 2:
            print name+",","you picked paper and so did the computer. It is a tie."
            ties = ties + 1
        elif choice == 2 and compchoice == 3:
            print name+",","your paper gets cut by the computers scissors. You lose."
            cwin = cwin + 1
        elif choice == 3 and compchoice == 1:
            print name+",","your scissors get smashed by the computers rock. You lose."
            cwin = cwin + 1
        elif choice == 3 and compchoice == 2:
            print name+",","your scissors cut the computers paper. You win!"
            pwin = pwin + 1
        elif choice == 3 and compchoice == 3:
            print name+",","you picked scissors and so did the computer. It is a tie."
            ties = ties + 1
        print # Print scoreboard
        print name,"Wins:",pwin
        print "Computer Wins:",cwin
        print "Ties:",ties
        # First to 3 wins, is announced the winner
    print
    if pwin == 3:
        print"Congratulations",name+", you beat the computer!"
    elif cwin == 3:
        print"Sorry",name+", you lose to the computer."
    print
    # Ask user to repeat program
    response = raw_input("Would you like to play again?(y/n): ")
    if response.upper() != "Y" and response.upper() != "YES":
        run = False
        print
        print"Thank you for using Rock Paper Scissors Program!"
