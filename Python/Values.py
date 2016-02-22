# Eric Bachmeier
#      The purpose of this program is to display information about a text file 
# Apr. 9, 2013

print "Information about 'Values.txt'"
print "------------------------------"
print # Print title
inFile = open('Values.txt', 'r') # Open file
number = inFile.readline().rstrip('\n') # Read first number
high = int(number) # Set high to first number
low = int(number) # Set low to first number
add = 0 # Set sum counter to zero
count = 0 # Set number counter to zero
while number != "": # While there is information in line execute
    if int(number) > high:
        high = int(number) # If number is higher, set it equal to high
    if int(number) < low:
        low = int(number)# If number is lower set it equal to low
    count += 1 # Count next number as 1
    add += int(number) # Add to sum count
    number = inFile.readline().rstrip('\n') # Read next number
average = float(add)/float(count) # Calculate average
print
print "Number of values:", count # Print count of numbers
print "Average of values:", round(average,2) # Print total average
print "Highest value:", high # Print highest value
print "Lowest value:", low # Print lowest value
inFile.close() # Close file
