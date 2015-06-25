# Eric Bachmeier
# Date Completed: Date Completed: October 20, 2011

print "Name File Creator"
print "-----------------"
print
print "This program creates a file called NameInfo.txt that will contain"
print "personal information about ten people."

filename = "NameInfo.txt"
outFile = open(filename, "w")
person = 1
print
print "Enter the information for person #", person
print "------------------------------------"
print
name = raw_input ("Enter the person's name: ")
address = raw_input ("Enter the person's address: ")
phone = raw_input ("Enter the person's phone number: ")
outFile.write (name + "\n")
outFile.write (address + "\n")
outFile.write (phone + "\n")
person = 1
for person in range (1, 10, 1):
    print
    print "Enter the information for person #", person + 1
    print "------------------------------------"
    print
    name = raw_input ("Enter the person's name: ")
    address = raw_input ("Enter the person's address: ")
    phone = raw_input ("Enter the person's phone number: ")
    outFile.write (name + "\n")
    outFile.write (address + "\n")
    outFile.write (phone + "\n")
print
print "Your file NameInfo.txt has been saved."
outFile.close()
