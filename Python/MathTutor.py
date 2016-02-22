# Eric Bachmeier
#      The purpose of this program is to quiz the user with 10 random math
# questions and validate the integer answer to output a overall percent as well.
# Feb. 24, 2013

print "Math Tutor"
print # Print opening sequence information
print "This program will quiz you by asking you 10 random math questions."
print "They will be either multiplication, division, addition, or subtraction,"
print "using random integer numbers from -100 to 100. You will be scored."
print
# Import math and random libraries
import math
import random
# Validation code
def isnumber(num,valid):
    try:
        num = int(num)
    except:
        print"Invalid input."
        valid = False
    else:
        valid = True
    return num,valid
# Randomly generate operator
operators = ["*","/","+","-"]
def chooseoperator():
    op = random.randint(0,3)
    return op
# Define two random integers
def randnums():
    r1 = random.randint(-100,100)
    r2 = random.randint(-100,100)
    return r1,r2
run = True
while run:
    op = 0
    r1 = 0
    r2 = 0
    correct = 0
    average = 0
    for x in range(0,10): # For loop for 10 questions
        op = chooseoperator()
        op = operators[op]
        r1,r2 = randnums()
        if op == "/": # Division to ensure a integer answer
            r3 = r1
            r4 = r2
            r1 = r1*r2
            answer = r1/r4
        elif op == "*": # Multiplication
            answer = r1*r2
        elif op == "+": # Addition
            answer = r1+r2
        else:
            answer = r1-r2 # Subtraction
        valid = False
        while not(valid):
            # Print string for question line with corresponding number and operator
            guess = raw_input("Question "+str(x+1)+": "+str(r1)+op+str(r2)+" = ")
            guess,valid = isnumber(guess,valid)
        if guess == answer:
            print "You are correct!"
            correct = correct + 1
        else:
            print "Sorry, you are not correct. The correct answer is:",answer
    average = correct*10 # Calculate average score percent
    print # Print final score after for loop exits
    print "Your score is: "+str(correct)+"/10 = "+str(average)+"%"
    print
    # Ask user to repeat program
    repeat = True
    while repeat:
        response = raw_input("Would you like to try again with different questions?(y/n): ")
        print
        if response.upper() == "N" or response.upper() == "NO":
            run = False
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
            print"Thankyou for using Math Tutor!"
        else:
            repeat = True
        
