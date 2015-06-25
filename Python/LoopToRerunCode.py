import math   # import the Math library
# print introduction
print "Area of Triangle Calculator"
print
print "In geometry, Heron's formula states that the area A of a triangle"
print "with sides that have lengths a, b, and c is:"
print u"A = \u221A(s(s-a)(s-b)(s-c))"
print "where s is the semi perimeter of the triangle:"
print "s = (a + b + c) / 2"
print
print "This program will calculate the area of a triangle using Heron's formula."
print
response = "Y"
while response == "Y":
    # prompt the user for the length of the three sides
    a = float(raw_input("Enter the length of side a: "))
    b = float(raw_input("Enter the length of side b: "))
    c = float(raw_input("Enter the length of side c: "))
    # calculate the area, round to three decimal places and print it
    s = (a+b+c)/2
    area = round(math.sqrt(s*(s-a)*(s-b)*(s-c)),3)
    print
    print "The area of the triangle is:",area,"square units."
    print
    response = raw_input("Would you like to calculate the area of another triangle? (Y/N) ")
    print
