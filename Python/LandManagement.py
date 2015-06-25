# Eric Bachmeier
# Date Completed: October 6, 2011

print "Land Management"
print "---------------"
print
print "Careless land management causes approximately 1 percent of the topsoil"
print "to erode each year. It is then lost forever, since it takes nature"
print "approximately 500 years to produce 2.5 cm of topsoil. At 9 cm the"
print "topsoil is so shallow that crops cannot be grown on a large scale."
print "Canada has about 30 cm of topsoil."
print
print "This program will calculate how many years it will take for the depth"
print "to be reduced to 9 cm."
print
repeat = True
while repeat == True:
    soil = float (raw_input ("Enter the amount of soil in cm: "))
    print "Year".rjust(4), "Soil Depth".rjust(10)
    print "----".rjust(4), "----------".rjust(10)
    year = 2011
    while soil > 9:
        year = year + 1
        produce = 2.5 / 500
        soil = (soil - (soil * 0.01) + produce)
        print str (year).rjust(4), str (soil).rjust(10)
        print
        if soil <= 9:
            print "The soil will be too shallow for crops in the year", year
        print
    response = raw_input("Would you like to enter another set of conditions?(Y/N): ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"
        
        
