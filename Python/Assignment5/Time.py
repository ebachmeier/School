# Eric Bachmeier
#      The purpose of this program is to output the angle between the hour and 
# minute hand on a clock, for the time entered by the user.
# Mar. 22, 2013

print"Time"
print # Print title sequence and intro
print"At any given time, the hour hand and the minute hand of a clock"
print"will form an angle. This program will calculate and print the angle"
print"in degrees, minutes and seconds, given the time in hours, minutes"
print"and seconds."
import math # Import math library
run = True
while run:
    valid = False
    while not(valid):
        print
        time = raw_input("Enter the time in the format HH:MM:SS - ") # Promt user for time
        if len(time) != 8: # Validate by length of 8
            print "Invalid input."
            continue
        elif time[0:2].isdigit() == False or time[3:5].isdigit() == False or time[6:8].isdigit() == False:
            print "Invalid input." # Validate that hours, minutes, and seconds are numbers
            continue
        else:
            valid = True
        t = ["","",""] # Create blank list for hours, minutes, seconds
        c = 0
        for x in range(0,len(time)):
            if time[x] != ":": # If not a ':' add to list
                t[c]+=time[x] # Add to list 't'
            else:
                c+=1 # Move to next space in user input
        for i in range(0,3):
            t[i] = int(t[i])
        if t[0] <= 12 and t[0] >= 1:
            valid = True
        else:
            print "Invalid input."
            continue
        if t[1] < 60 and t[1] >= 0:
            valid = True
        else:
            print "Invalid input."
            continue
        if t[2] < 60 and t[2] >= 0:
            valid = True
        else:
            print "Invalid input."
            continue
        
        h = t[0]*30+t[1]*0.5+t[2]*(0.5/60)
        m = t[1]*6+t[2]*0.1
        if h > m:
            middle = h - m
        else:
            middle = m - h
        if middle > 180:
            middle = 360 - middle
        middle = str(middle)
        mdec = ""
        for g in range(0,len(middle)):
            if middle[g] == ".":
                mdec = middle[g:]
                break
        mdec = float(mdec)
        mm = mdec+60
        mm = str(mm)
        sdec = ""
        for y in range(0,len(mm)):
            if mm[y] == ".":
                sdec = mm[y:]
                break
        sdec = float(sdec)
        ss = sdec*60
        middle = float(middle)
        mm = round(float(mm),0)%60
        ss = round(ss,0)%60
    print "The angle between the hour hand and minute hand is: "+str(int(middle))+":"+str(int(mm)).rjust(2,"0")+":"+str(int(ss)).rjust(2,"0")
    repeat = True
    while repeat:
        print  # Ask user to repeat program
        response = raw_input("Would you like to try again?(y/n): ") 
        if response.upper() == "N" or response.upper() == "NO":
            run = False
            repeat = False
            print
            print"Thank you for using Time Program!"
        elif response.upper() == "Y" or response.upper() == "YES":
            repeat = False
        else:
            print "Invalid input."
            repeat = True
        
