# Eric Bachmeier
# This program's purpose is have users enter a temperature in degrees Celcius and tell them if it is freezing, cool, warm, hot, or extreme.
# Date Completed: September 16, 2011

print "Temperature Category Program"
print
temp = int (raw_input ("Enter a Temperature in Degrees Celcius: "))
print
if temp <= 0:
    print "It is freezing."
elif temp <= 10:
    print "It is cool."
elif temp <= 23:
    print "It is warm."
elif temp <= 35:
    print "It is hot."
else:
    print "It is extreme."
