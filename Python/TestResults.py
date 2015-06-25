# Eric Bachmeier
# Date Completed: Date Completed: October 27, 2011

filename = "Test1Marks.txt"
inFile = open(filename, "r")
total = inFile.readline().rstrip("\n")
print "Results of Test 1 (Out of", total,"marks)"
print "-----------------------------------"
print
name = inFile.readline().rstrip("\n")
lvl = inFile.readline().rstrip("\n")
percenttotal = 0
counter = 0
while name != "": 
    print name.rjust(18) ,"-     ".rjust(13),
    percentage = float(lvl)/float(total) * 100
    percenttotal = percenttotal + percentage
    counter = counter + 1
    if percentage >= 95:
        print float(round(percentage,2)), "4+".rjust(13)
    elif percentage >= 87:
        print float(round(percentage,2)), "4".rjust(13)
    elif percentage >= 80:
        print float(round(percentage,2)), "4-".rjust(13)
    elif percentage >= 77:
        print float(round(percentage,2)), "3+".rjust(13)
    elif percentage >= 73:
        print float(round(percentage,2)), "3".rjust(13)
    elif percentage >= 70:
        print float(round(percentage,2)), "3-".rjust(13)
    elif percentage >= 67:
        print float(round(percentage,2)), "2+".rjust(13)
    elif percentage >= 63:
        print float(round(percentage,2)), "2".rjust(13)
    elif percentage >= 60:
        print float(round(percentage,2)), "2-".rjust(13)
    elif percentage >= 57:
        print float(round(percentage,2)), "1+".rjust(13)
    elif percentage >= 53:
        print float(round(percentage,2)), "1".rjust(13)
    elif percentage >= 50:
        print float(round(percentage,2)), "1-".rjust(13)
    else:
        print float(round(percentage,2)), "<1".rjust(13)
    name = inFile.readline().rstrip("\n")
    lvl = inFile.readline().rstrip("\n")
inFile.close()
print
print "Class Average: ", round (float(percenttotal) / float(counter), 2)
print
print "Students with a Percentage Less Than 50"
print "---------------------------------------"
print
filename = "Test1Marks.txt"
inFile = open(filename, "r")
total = inFile.readline().rstrip("\n")
name = inFile.readline().rstrip("\n")
lvl = inFile.readline().rstrip("\n")
while name != "":
    percentage = float(lvl)/float(total) * 100
    if percentage < 50:
        print str(name)
    name = inFile.readline().rstrip("\n")
    lvl = inFile.readline().rstrip("\n")
inFile.close()


    
