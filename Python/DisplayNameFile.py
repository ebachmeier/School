# Eric Bachmeier
# Date Completed: Date Completed: October 20, 2011

print "Display File Name"
print "-----------------"
print
print "This program opens the file and displays the info from the 10 people"
print
filename = "NameInfo.txt"
outFile = open (filename, "r")
print "Name".rjust(20), "Address".center(40), "Phone Number".ljust(20)
print "----".rjust(20), "-------".center(40), "------------".ljust(20)

for person in range (1, 10, 1):
    name = outFile.readline().rstrip("\n")
    address = outFile.readline().rstrip("\n")
    phonenumber = outFile.readline().rstrip("\n")
    print str(name).rjust(20), str(address).center(40), str(phonenumber).ljust(20)
outFile.close()
