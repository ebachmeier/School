# Eric Bachmeier
#      The purpose of this program is to generate a list of 1000 random integers 
# and say at what positions the inoutted number occurs in the list.
# Mar. 4, 2013

print"Random Numbers"
print # Print title sequence and intro
print"This program creates an array of 1000 random integers from 1 to 100."
print"The program then prompts the user for any integer from 1 to 100 and"
print"prints out how many times it occurs in the array and at which positions."
# Import random library
import random
# Define search for numbers in list
def searchlist(s,nums):
    occurs = nums.count(s)
    positions = []
    for i in range(0,1000):
        if nums[i] == s:
            positions.append(i)
    return positions,occurs
# Validate integer between 1 and 100
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print"Invalid Input."
        valid = False
    else:
        if num < 1 or num > 100:
            print "Invalid input."
        else:
            valid = True
    return num,valid
# Make list of 1000 random integers between 1 and 100
nums = [random.randint(1,100) for x in range(0,1000)]
run = True
while run:
    print
    valid = False
    while not(valid): # Promt user for integer to search for
        search = raw_input("Enter the number you would like to search for: ")
        search,valid = isnumber(search,valid) # Validate integer and between 1 and 100
    positions,occurs = searchlist(search,nums)
    print "The number "+str(search)+" occurs "+str(occurs), # Print the number and how many times it occurs
    if occurs == 1: # Determine and print proper singular or plural
        print "time at position:"
    else:
        print "times at positions:"
    for i in range(0,len(positions)): # Print at which points it occurs
        if i != (len(positions)-1):
            print str(positions[i])+",",
        else:
            print "and "+str(positions[i])+"."
    print
    # Ask user to repeat program
    repeat = True
    while repeat:
        response = raw_input("Would you like to find a different number?(y/n): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Random Number Finder!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
