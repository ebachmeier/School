# Eric Bachmeier
# This program tells users the number of values, the smallest value, the largest value, and average, and the median in the Values.txt file.
# Date Completed: December 14, 2011

print "Number Info Program"
print "-------------------"
print
print "This program dis[plays the number of values, smallest value, average,"
print "largest value, and the median of numbers in a text file called Values.txt"

filename = "Values.txt"
inFile = open(filename,"r")
value = inFile.readline().rstrip("\n")
numbers = []
total = 0
while value!="":
    numbers.append(int(value))
    value = inFile.readline().rstrip("\n")
print "The original list of numbers is: "

print numbers
print
print "The sorted list of numbers is:"
numbers.sort()
print numbers
print
total = 0
for x in range(0,len(numbers)):
    total = total+float(numbers[x])
average = round(total/len(numbers),2)                         
print "Number of values in the list:",len(numbers)
print "Smallest value in the list:",numbers[0]
print "The largest value in the list:",numbers[-1]
print "The average of the values in the list:",average

l = len(numbers)
if l%2 == 0:
    median = (numbers[l/2]+numbers[l/2-1])/2
else:
    median = numbers[l/2]
print "The median of the values in the list:",median
    
