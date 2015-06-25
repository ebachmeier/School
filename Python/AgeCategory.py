# Eric Bachmeier
# This program's purpose is have users enter their age and tell them what category they fit into.
# Date Completed: September 16, 2011

print "Age Category Program"
print
age = int (raw_input ("Enter your Age: "))
print
if age <= 1:
    print "You are an in infant."
elif age <= 4:
    print "You are a toddler."
elif age <= 12:
    print "You are a child."
elif age <= 19:
    print "You are a teenager."
else:
    print "You are an adult."

