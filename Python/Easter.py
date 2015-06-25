# Eric Bachmeier
# This program allows users to input the year and it will output that day Easter will b e celebrated on that year.
# Date Completed: September 20, 2011

import math

print "Day and Month of Easter"

print
year = int (input ("Enter the Year: "))
a = year % 19
b = year // 100
c = year % 100
d = b // 4
e = b % 4
f = (8 * b + 13) // 25
g = (19 * a + b - d - f + 15) % 30
h = (a + 11 * g) // 319
i = c // 4
j = c % 4
m = (2 * e + 2 * i - g - h - j + 32) % 7
month = (g - h + m +90) // 25
day = (g - h + m + month + 19) % 32

print
print "Easter will be on ", month, "/", day, " in the year", year

