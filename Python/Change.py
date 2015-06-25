# Eric Bachmeier
# This program allows users to input an amount of change in cents and it will output the amount of change with the least amount of coins if it is under 100 cents. 
# Date Completed: September 22, 2011

import math
print "Change Calculator"
print
cents = int (raw_input ("Enter the amount of change in cents: "))
print

qs = " quarter, "
ds = " dimes, "
ns = " nickel, "
cs = " penny."

q = cents / 25
d = (cents - (q * 25)) / 10
n = (cents - (q * 25) - (d * 10)) / 5
c = (cents - (q * 25) - (n * 5) - (d * 10)) / 1
if q > 1:
    qs = " quarters, "
elif q == 0:
    qs = ""
    q = str ("")
else:
    qs = " quarter, "
if d > 1:
    ds = " dimes, "
elif d == 0:
    ds = ""
    d = str ("")
else:
    ds = " dime, "
if n > 1:
    ns = " nickels, "
elif n == 0:
    ns = ""
    n = str ("")
else:
    ns = " nickel, "
if c > 1: 
    cs = " pennies."
elif c == 0:
    cs = ""
    c = str ("")
else:
    cs = " penny."
print str(cents) + " cents requires " + str(q) + qs + str (d) + ds + str(n) + ns + " and " + str(c) + cs
