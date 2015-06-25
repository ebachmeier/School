# Eric Bachmeier
#      The purpose of this program is to display the test marks with the
# corresponding student names, as well as the class average and people who failed.
# Apr. 10, 2013

inFile = open('Test1Marks.txt', 'r') # Open file
outof = inFile.readline().rstrip('\n') # Read first like what test is out of (marks)
print "Results of Test 1 (Out of", outof+")" # Print title with out of
print "-----------------------------"
name = inFile.readline().rstrip('\n') # Read first student name
mark = inFile.readline().rstrip('\n') # Read first student mark
outof = float(outof)
students = 0 # Student counter set to zero
total = 0 # Total marks set to zero
fail = [] # Blank list of students who fail (<50%)
while name != "": # While information in readline
    students += 1 # Add 1 to students counter
    print str(name).ljust(15), # Print name
    print "-".rjust(10),
    print " ".rjust(3),
    percfl = float(mark)/(outof)*100 # Calculate percent
    percfl = float(percfl)
    total += percfl # Add percent to total
    percent = int(percfl)
    print str(percent).rstrip(".")+"%", # Print percent for student
    print "Level:".ljust(7), # Print corresponding level to percent
    if percent >= 95:
        print "4+".ljust(2)
    elif percent >= 87:
        print "4".ljust(2)
    elif percent >= 80:
        print "4-".ljust(2)
    elif percent >= 77:
        print "3+".ljust(2)
    elif percent >= 73:
        print "3".ljust(2)
    elif percent >= 70:
        print "3-".ljust(2)
    elif percent >= 67:
        print "2+".ljust(2)
    elif percent >= 63:
        print "2".ljust(2)
    elif percent >= 60:
        print "2-".ljust(2)
    elif percent >= 57:
        print "1+".ljust(2)
    elif percent >= 53:
        print "1".ljust(2)
    elif percent >= 50:
        print "1-".ljust(2)
    elif percent < 50:
        print "<1".ljust(2)
        x = 0.48
        fail.append(name) # IF less than 50%, add name to fail list
    name = inFile.readline().rstrip("\n") # Read next student name
    mark = inFile.readline().rstrip("\n") # Read next student mark
inFile.close() # Close file
print
classt = total / students-x # Calculate class percent average
print "Class Average: ",
print round(float(classt), 2),"%" # Print class average
print
print "Students with a Percentage Less Than 50"
print "---------------------------------------"
print
for num in range(0,len(fail)):
    print fail[num] # Print students names who failed
    

