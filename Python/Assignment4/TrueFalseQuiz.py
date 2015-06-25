# Eric Bachmeier
#      The purpose of this program is to make a 10 mark true/false quiz
# and evaluate for correct answers.
# Mar. 5, 2013

print "True/False Quiz"
print "---------------" 
print # Print title sequence and intro
print "This program asks you 10 True/False questions about Canada."
# Make questions list
q = ["The fourth Prime Minister of Canada was Winston Churchill.","The capital of Canada before 1867 was Quebec City.",
    "Wayne Gretzky has been inducted to the Hockey Hall of Fame.","The Toronto Blue Jays joined Major League Baseball in 1977",
    "Celine Dion was born in the province of Quebec.","Wheat is the number 1 export from Canada.",
    "More Canadians travel to Europe than the United States every year.","Charles Best co-discovered insulin with Fredrick Banting.",
    "James Gosling, a Canadian, developed Java.","Terry Fox was born in Winnipeg."]
# Make answers list
a = [False,False,True,True,True,True,False,True,True,True]
run = True
while run:
    print
    print "Good Luck!"
    print
    r = [] # Make empty list for responses from user
    for x in range(0,10):
        valid = False
        while not(valid): # Ask appropriate question number
            answer = raw_input(str(x+1)+". "+q[x]+"(T)rue or (F)alse ")
            if answer.upper() == "T" or answer.upper() == "F" or answer.upper() == "TRUE" or answer.upper() == "FALSE":
                valid = True # Validate response of true or false (T or F)
            else:
                print "Please enter True or False."
                valid = False # Ask again if answer is invalid
        if answer.upper() == "T" or answer.upper() == "TRUE":
            r.append(True) # Append a True if correct
        else:
            r.append(False) # Append a False if incorrect
    print
    print "Results"
    print "-------"
    print
    correct = 0
    for i in range(0,10):
        print q[i]
        print "Your answer:", # Print users answer
        if a[i] == True:
            print"T",
        else:
            print"F",
        print "Correct answer:", # Print the correct answer
        if r[i] == True:
            print"T"
        else:
            print"F"
        if r[i] == a[i]:
            correct = correct + 1 # User is correct if answer is same as computer answer (correct answer)
    print
    print "You got "+str(correct)+" out of 10 correct." # Print total score
    print "Your percent is "+str(int((float(correct)/10)*100))+"%" # Print percent
    print
    # Ask user to repeat program
    repeat = True
    while repeat:
        response = raw_input("Would you like to try again?(y/n): ")
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using True/False Quiz!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
