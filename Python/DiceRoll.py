# Eric Bachmeier
# This program reads a text file that tells the program how many cases are
# involved and says how many ways you can roll the sum given.
# November 10, 2011

print "Dice Roll Program"
print "-----------------"
print
print "This program uses the input from the file Dice.txt to dtermine how many"
print "cases are in the file, and how many ways you can reach the given sum."
print
file_name = ("Dice.txt")
inFile = open(file_name, "r")
cases = inFile.readline().rstrip("\n")
ways = 0
print
print "Dice Roll"
print "_________"
print
for a in range (0,int(cases),1):
    die1 = inFile.readline().rstrip("\n")
    die2 = inFile.readline().rstrip("\n")
    sum_num = inFile.readline().rstrip("\n")
    print "The first die has " + str(die1) + " sides."
    print "The second die has " + str(die2) + " sides."
    for die_a in range(0,int(die1) + 1,1):
        num1 = die_a
        for die_b in range(0,int(die2) + 1,1):
            num2 = die_b
            if (num1 + num2 == int(sum_num)):
                ways = ways + 1
    print "There are " + str(ways) + " ways to get the sum " + str(sum_num) + "."
    print
    ways = 0
inFile.close()

