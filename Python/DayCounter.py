# Eric Bachmeier
#      The purpose of this program is to output the number of days from the
# specified date to the beginning of that year.
# Apr. 30, 2013

def DayNumber(d,m,y): # Define day number function
    total = 0
    yd[m-1] = d # Set days 
    for x in range(0,m):
        total+=yd[x] # Set total to the total days from beginning of year
    return total
    
def isnum(num,valid): # Define number input validation
    try:
        num = int(num) # True for integer
    except:
        print "Invalid input."
        valid = False
    else:
        valid = True
    return num,valid

print "Day Counter"
print "-----------"
print # Print introduction
print "This program will count the number of days from the"
print "beginning of a year for any day, month, and year."

yd = [31,0,31,30,31,30,31,31,30,31,30,31] # Create blank list for days 
run = True
while run:
    print
    valid = False
    while not (valid): # Prompt user for day
        d = raw_input("Enter the value for the day (1-31): ")
        d,valid = isnum(d,valid) # Validate input
        if valid and (d<1 or d>31):
            print "Invalid input."
            valid = False
    valid = False
    while not (valid): # Prompt user for month
        m = raw_input("Enter the value for the month (1-12): ")
        m,valid = isnum(m,valid) # Validate input
        if valid and (m<1 or m>12):
            print "Invalid input."
            valid = False
    valid = False
    while not (valid): # Prompt user for year
        y = raw_input("Enter the value for the year: ")
        y,valid = isnum(y,valid) # Validate input
    if (y%4 == 0 and y%100 != 0) or (y%4 == 0 and y%400 == 0):
        yd[1] = 29
    else: # Set days in february based on leap year rules
        yd[1] = 28
    if d <= (yd[m-1]):
        td = DayNumber(d,m,y) # Set td to total days, calling DayNumber()
    else:
        print
        print "Invalid number of days for that particular month."
        continue
    print
    print "The number of days from the beginning of the year is:", td # Print days
    print # Promt user to repeat
    response = raw_input("Would you like to try again?(Y/N): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
    
