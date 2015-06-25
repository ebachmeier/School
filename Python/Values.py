# Eric Bachmeier
# Date Completed: Date Completed: October 26, 2011

print "Values"
print "------"
print
print "Print out the number of values in the file, the average of the values"
print "in the file, the highest value in the file, and the lowest value in the"
print "file."
print
filename = "Values.txt"
inFile = open(filename, "r")
total = 0
num_value = 0
high = -999999
low = 999999
num = inFile.readline().rstrip("\n")
while num != "":
    num_value = num_value + 1
    total = total + int(num)
    if int(num) > high:
        high = int(num)
    if int(num) < low:
        low = int(num)
    num = inFile.readline().rstrip("\n")
print "There are",num_value,"numbers in the file."
print "The average of the numbers is:",total/num_value
print "The highest number is:",high
print "The lowest number is:",low
inFile.close()
