# Eric Bachmeier
# This program has users imput a date as DD MM YY
# Date Completed: November 28, 2011

print "Date Checker"
print "------------"
print
print "Users enter a date as DD MM YY and the program outputs it in the"
print "following formats: "
print
print "DD MM YY"
print "DD Month YY"
print "DD Month Year" 
print "Month Day, Year"
print
repeat = True
while repeat == True:
    date = raw_input("Please enter a date in DDMMYY format: ")
    print
    # Ensure date is valid
    while date [2:4] > "12":
        print "This is not a valid date. Enter a valid month."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "01" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "02" and date[0:2] > "29":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "03" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "04" and date[0:2] > "30":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "05" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "06" and date[0:2] > "30":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "07" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "08" and date[0:2] > "30":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "09" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "10" and date[0:2] > "30":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "11" and date[0:2] > "31":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
    while date [2:4] == "12" and date[0:2] > "30":
        print "This is not a valid date. Enter a valid day."
        date = raw_input("Please enter a valid date: ")
        
    print
    print "The date can be printed as: "
    print
    print date[0:2], date[2:4], date[4:6]
    if date [2:4] == "01":
         print date[0:2],"January",date[4:6]
         print date[0:2],"January 20"+date[4:6]
         print "January",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "02":
         print date[0:2],"February",date[4:6]
         print date[0:2],"February 20"+date[4:6]
         print "February",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "03":
         print date[0:2],"March",date[4:6]
         print date[0:2],"March 20"+date[4:6]
         print "March",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "04":
         print date[0:2],"April",date[4:6]
         print date[0:2],"April 20"+date[4:6]
         print "April",date[0:2]+", 20"+date[4:6]
    if date [2:4]== "05":
         print date[0:2],"May",date[4:6]
         print date[0:2],"May 20"+date[4:6]
         print "May",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "06":
         print date[0:2],"June",date[4:6]
         print date[0:2],"June 19"+date[4:6]
         print "June",date[0:2]+", 19"+date[4:6] 
         print
    if date [2:4]== "07":
         print date[0:2],"July",date[4:6]
         print date[0:2],"July 19"+date[4:6]
         print "July",date[0:2]+", 19"+date[4:6] 
         print
    if date [2:4]== "08":
         print date[0:2],"August",date[4:6]
         print date[0:2],"August 20"+date[4:6]
         print "August",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "09":
         print date[0:2],"September",date[4:6]
         print date[0:2],"September 20"+date[4:6]
         print "September",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "10":
         print date[0:2],"August",date[4:6]
         print date[0:2],"August 20"+date[4:6]
         print "August",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "11":
         print date[0:2],"November",date[4:6]
         print date[0:2],"November 20"+date[4:6]
         print "November",date[0:2]+", 20"+date[4:6] 
         print
    if date [2:4]== "12":
         print date[0:2],"December",date[4:6]
         print date[0:2],"Decemeber 20"+date[4:6]
         print "December",date[0:2]+", 20"+date[4:6]
         print
    response = raw_input("Would you like to enter another date? (Y/N): ")
    print
    while response == "n" or response == "N":
        repeat = False
print "Good bye!"      
print
