# Eric Bachmeier
#      The purpose of this program is to make a menu-based program for Madlibs.
# Apr. 24, 2013

import random,sys,os,shutil # Import random, os, and sys libraries

def loadfiles(): # Define load and read text files
    plural = open('plural.txt', 'r') # Open text file
    verb = open('verb.txt', 'r')
    singular = open('singular.txt', 'r')
    pn = [] # Make blank list for words
    pluralnoun = plural.readline().rstrip('\n') # Read first line
    while pluralnoun != "":
        pn.append(pluralnoun) # Add to list
        pluralnoun = plural.readline().rstrip('\n') # Read next line
    v = []
    verbr = verb.readline().rstrip('\n')
    while verbr != "":
        v.append(verbr)
        verbr = verb.readline().rstrip('\n')
    sn = []
    singnoun = singular.readline().rstrip('\n')
    while singnoun != "":
        sn.append(singnoun)
        singnoun = singular.readline().rstrip('\n')
    plural.close() # Close text file
    verb.close()
    singular.close()
    return pn,v,sn # Return the three lists

def madlib(pns,vs,sns): # Define madlib function
    rpn = random.randint(0, len(pns)-1) # Generate random number in range of words
    rv = random.randint(0, len(vs)-1)
    rsn = random.randint(0, len(sns)-1)
    print "The", pns[rpn], vs[rv], sns[rsn]+"." # Print MadLib

def newfile(w): # Define create new file function
    name = ""
    if w == "plural noun": # Assign text file name to 'name'
        name = "plural.txt"
    elif w == "verb":
        name = "verb.txt"
    else:
        name = "singular.txt"
    os.remove(name) # Clear the text file
    inFile = open(name,"w") # Open text file for writing
    go = True
    while go: # Promt user for words to append
        user = raw_input("Enter a "+w+" to add to "+name+" or '0' to return to MAIN MENU: ")
        if user == '0': # Return home if '0'
            go = False
        else:
            inFile.write(user+'\n') # Write to new file
    inFile.close() # Close text file

def add(w,pns,vs,sns): # Define add words to file function
    name = ""
    if w == "plural noun": # Assign text file name to 'name'
        name = "plural.txt"
        z = pns
    elif w == "verb":
        name = "verb.txt"
        z = vs
    else:
        name = "singular.txt"
        z = sns
    print
    print "The text file",name, "contains:"
    for x in range(0,len(z)):
        print z[x] # Print the contents of the text file
    inFile = open(name,'a')
    go = True
    while go: # Promt user for words to add
        user = raw_input("Enter a "+w+" to add to "+name+" or '0' to return to MAIN MENU: ")
        if user == '0': # Return home if '0'
            go = False
        else:
            inFile.write(user+'\n') # Write to new file
    inFile.close() # Close text file

def delete(w,pns,vs,sns): # Define delete word function
    name = ""
    if w == "plural noun": # Assign text file name to 'name'
        name = "plural.txt"
        z = pns
    elif w == "verb":
        name = "verb.txt"
        z = vs
    else:
        name = "singular.txt"
        z = sns
    inFile = open(name,'w') # Open text file
    go = True
    while go:
        print
        print "The "+name+" file contains:"
        for i in range(0,len(z)): # Print numbers corresponding to words
            print "["+str(i+1)+"] to delete '"+z[i]+"'"
        delete = raw_input("Enter the number of the word to delete or '0' for MAIN MENU: ")
        if delete == '0': # Prompt user for number word to delete
            go = False
        else:
            if delete.isdigit() == False: # Validate number input
                print "Invalid input."
            else:
                if int(delete) > len(z) or int(delete) < 1:
                    print "Invalid input."
                else:
                    z.pop(int(delete)-1) # Delete word
                    inFile.close() # Close text file
                    os.remove(name)
                    inFile = open(name,'w')
                    for i in range(0,len(z)): # Reset text file with words kept
                        inFile.write(z[i]+'\n')

def display(w,pns,vs,sns): # Define 
    name = ""
    if w == "plural noun": # Assign text file name to 'name'
        name = "plural.txt"
        z = pns
    elif w == "verb":
        name = "verb.txt"
        z = vs
    else:
        name = "singular.txt"
        z = sns
    print
    print "The "+name+" file contains:"
    for x in range(0,len(z)):
        if x != len(z)-1: # Display words in list
            print z[x]+",", # Add a comma if not last word
        else:
            print z[x]
    
def mainmenu(pns,vs,sns): # Define print menu function
    print
    print "MAIN MENU"
    print "---------------------------------------------------------"
    print "a. Display a Madlib"
    print "b. Create a new Plural Noun text file"
    print "c. Create a new Verb text file"
    print "d. Create a new Singular Noun text file"
    print "e. Add a new noun to the Plural Noun text file"
    print "f. Add a new verb to the Verb text file"
    print "g. Add a new noun to the Singular Noun text file"
    print "h. Delete a noun from the Plural Noun text file"
    print "i. Delete a verb from the Verb text file"
    print "j. Delete a noun from the Singular Noun text file"
    print "k. List the Plural Noun text file"
    print "l. List the Verb text file"
    print "m. List the Singular Noun text file"
    print "x. Exit the program"
    print "---------------------------------------------------------"
    print
    
    valid = False
    while not(valid):
        choice = raw_input("Enter your choice from the menu: ") # Promt user for for menu choice
        choice = choice.upper()
        if choice.isalpha() == True: # Validate alpha input
            if ord(choice) in range(65,78) or ord(choice) == 88:
                valid = True
            else:
                valid = False
                print "Invalid Input."
        else:
            if choice == "X" and valid == False:
                valid = True
            else:
                valid = False
                print "Invalid Input."
                
    if choice == "A": # Load variables for each choice and call appropriate function
        madlib(pns,vs,sns)
        return True,pns,vs,sns
    elif choice == "B":
        w = "plural noun"
        newfile(w)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "C":
        w = "verb"
        newfile(w)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "D":
        w = "singular noun"
        newfile(w)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "E":
        w = "plural noun"
        add(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "F":
        w = "verb"
        add(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "G":
        w = "singular noun"
        add(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "H":
        w = "plural noun"
        delete(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "I":
        w = "verb"
        delete(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "J":
        w = "singular noun"
        delete(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "K":
        w = "plural noun"
        display(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "L":
        w = "verb"
        display(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "M":
        w = "singular noun"
        display(w,pns,vs,sns)
        pns,vs,sns = loadfiles()
        return True,pns,vs,sns
    elif choice == "X":
        return False,pns,vs,sns

def init(): # Update variables for restart
    pns,vs,sns = loadfiles()
    run = True
    while run:
        run,pns,vs,sns = mainmenu(pns,vs,sns) # Print main menu by calling it
init()
