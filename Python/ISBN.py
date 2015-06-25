# Eric Bachmeier
# This program will compute the 1-3-sum of a 13-digit ISBN number and to
# determine if it is a valid number or not.
# Date Completed: November 4, 2011

print "ISBN Program Calculator"
print "-----------------------"
print
print "This program has users input a 13-digit code for identifying books."
print "The program will then tell the user if the number was written correctly."
print "These codes have a special property becuase the 1-3-sum is always a"
print "multiple of 10."
print
print "This program will compute the 1-3-sum of a 13-digit ISBN number and to"
print "determine if it is a valid number or not."
print
repeat = True
while repeat == True:
    number = int (raw_input("Enter the 13-digit ISBN Number: "))
    while number < 1000000000000 or number > 9999999999999:
        number = int (raw_input("Please enter a valid 13-digit number: "))
    
    d13 = number% 10
    number = number // 10
    d12 = number% 10
    number = number // 10
    d11 = number% 10
    number = number // 10
    d10 = number% 10
    number = number // 10
    d9 = number% 10
    number = number // 10
    d8 = number% 10
    number = number // 10
    d7 = number% 10
    number = number // 10
    d6 = number% 10
    number = number // 10
    d5 = number% 10
    number = number // 10
    d4 = number% 10
    number = number // 10
    d3 = number% 10
    number = number // 10
    d2 = number% 10
    number = number // 10
    d1 = number% 10
    number = number // 10
    sum13 = d13*1+d12*3+d11*1+d10*3+d9*1+d8*3+d7*1+d6*3+d5*1+d4*3+d3*1+d2*3+d1*1
    if sum13%10==0:
        print "The 1-3-sum is",sum13, "so it is a valid ISBN."
    else:
        print "The 1-3-sum is",sum13, "so it is not a valid ISBN."
    response = raw_input ("Would you like to enter another ISBN number? (Y/N) ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
