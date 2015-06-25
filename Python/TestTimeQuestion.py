# Eric Bachmeier
# This program is for the test question, it converts a time entered by the
# user as HH:MM:SS to a A.M. or P.M. time such as 2:32 A.M.
# Date Cmopleted: December 8, 2011

print "24 Hour Time to A.M. P.M. Program"
print"----------------------------------"
print
print "This progam has the user enter a 24-hour time in the format HH:MM:SS and"
print "this program will convert it to a time such as 2:32 P.M. or 4:23 A.M."
print

repeat = True
while repeat:
    # ask user for time
    time = raw_input("Enter the time in the format HH:MM:SS - ")
    time2 = True
    if len(time) != 8:
        print "The time doesn't have eight digits in it."
        time2 = False
    if time [0:2] > "23" or time [0:2] < "0":
        print "This is not a valid time."
        time2 = False
    if time [3:5] > "60" or time [3:5] < "0":
        print "This is not a valid time."
        time2 = False
    if time [6:8] > "60" or time [6:8] < "0":
        print "This is not a valid time."
        time2 = False
    if time2 == True:
        # display time
        if time [0:2] == "00":
            time2 = True
            print "The time is 12:"+time[3:5],"A.M."
        if time [0:2] == "01":
            time2 = True
            print "The time is 1:"+time[3:5],"A.M."
        if time [0:2] == "02":
            time2 = True
            print "The time is 2:"+time[3:5],"A.M."
        if time [0:2] == "03":
            time2 = True
            print "The time is 3:"+time[3:5],"A.M."
        if time [0:2] == "04":
            time2 = True
            print "The time is 4:"+time[3:5],"A.M."
        if time [0:2] == "05":
            time2 = True
            print "The time is 5:"+time[3:5],"A.M."
        if time [0:2] == "06":
            time2 = True
            print "The time is 6:"+time[3:5],"A.M."
        if time [0:2] == "07":
            time2 = True
            print "The time is 7:"+time[3:5],"A.M."
        if time [0:2] == "08":
            time2 = True
            print "The time is 8:"+time[3:5],"A.M."
        if time [0:2] == "09":
            time2 = True
            print "The time is 9:"+time[3:5],"A.M."
        if time [0:2] == "10":
            time2 = True
            print "The time is 10:"+time[3:5],"A.M."
        if time [0:2] == "11":
            time2 = True
            print "The time is 11:"+time[3:5],"A.M."
        if time [0:2] == "12":
            time2 = True
            print "The time is 12:"+time[3:5],"P.M."
        if time [0:2] == "13":
            time2 = True
            print "The time is 1:"+time[3:5],"P.M."
        if time [0:2] == "14":
            time2 = True
            print "The time is 2:"+time[3:5],"P.M."
        if time [0:2] == "15":
            time2 = True
            print "The time is 3:"+time[3:5],"P.M."
        if time [0:2] == "16":
            time2 = True
            print "The time is 4:"+time[3:5],"P.M."
        if time [0:2] == "17":
            time2 = True
            print "The time is 5:"+time[3:5],"P.M."
        if time [0:2] == "18":
            time2 = True
            print "The time is 6:"+time[3:5],"P.M."
        if time [0:2] == "19":
            time2 = True
            print "The time is 7:"+time[3:5],"P.M."
        if time [0:2] == "20":
            time2 = True
            print "The time is 8:"+time[3:5],"P.M."
        if time [0:2] == "21":
            time2 = True
            print "The time is 9:"+time[3:5],"P.M."
        if time [0:2] == "22":
            time2 = True
            print "The time is 10:"+time[3:5],"P.M."
        if time [0:2] == "23":
            time2 = True
            print "The time is 11:"+time[3:5],"P.M."
            # repeat?
    response = raw_input("Would you like to enter anotgher time? (Y/N) : ")
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
        
        
        
        
        
        
