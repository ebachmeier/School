# Eric Bachmeier
#      This program promts the user for the degree of the compass and the
# program will output the closest direction on a 16 point circle.
# Feb. 13, 2013

print "Compass Rose"
print # Print introduction
print"Before the Magnetic Compass was discovered, early map makers would draw"
print"a small 16 pointed circle on the map, and place an 'N' to point to North."
print"These were the 16 Cardinal Points from which the winds were thought to blow."
print"This drawing was called a 'Wind Rose.' When the magnetic compass came along,"
print"it was usually set on top of the Wind Rose pattern in order to help face the"
print"nautical chart in the proper direction. The wind rose started to become known"
print"as a COMPASS ROSE."
print
print "This program will ask you for a degree value from the North of the compass"
print "and will return the closest directioon on a 16 point compass i.e. NNE"
# Validate degree of compass
def isnumber(num,valid):
    try:
        num = float(num)
    except:
        print "Invalid input."
        print
    else:
        if num < 0 or num > 360:
            print "Invalid input."
            print
        else:
            valid = True
    return num,valid
run = True
while run:
    valid = False
    while not(valid):
        # Promt user for
        print
        degrees = raw_input ("Enter the amount of degrees for the compass: ")
        print
        degrees,valid = isnumber (degrees,valid)
    # Print statements for each degree interval
    # This are known becuase 22.5 degrees is each interval
    # Plus or minus 11.25 degrees from each one determines which is closer to
    if (degrees >= 0 and degrees <= 11.25) or (degrees > 348.75 and degrees <= 360):
        print "North (N)"
    elif degrees <= 33.75:
        print "North North East (NNE)"
    elif degrees <= 56.25:
        print "North East (NE)"
    elif degrees <= 78.75:
        print "East North East (ENE)"
    elif degrees <= 101.25:
        print "East (E)"
    elif degrees <= 123.75:
        print "East South East (ESE)"
    elif degrees <= 146.25:
        print "South East (SE)"
    elif degrees <= 168.75:
        print "South South East (SSE)"
    elif degrees <= 191.25:
        print "South (S)"
    elif degrees <= 213.75:
        print "South South West (SSW)"
    elif degrees <= 236.25:
        print "South West (SW)"
    elif degrees <= 258.75:
        print "West South West (WSW)"
    elif degrees <= 281.25:
        print "West (W)"
    elif degrees <= 303.75:
        print "West Noth West (WNW)"
    elif degrees <= 326.25:
        print "North West (NW)"
    elif degrees <= 348.75:
        print "North North West (NNW)"
    print
    # Ask to repeat 
    response = raw_input ("Would you like to enter a new amount?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print "Thankyou for using Compass Rose!"
