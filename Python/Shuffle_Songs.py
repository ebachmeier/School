# Eric Bachmeier
# Do The Shuffle
# February 16, 2012

print "Song Shuffle Program"
print "--------------------"
print
b = 0
p = ["A", "B", "C", "D", "E"]
while b != 4:
    b = int(raw_input("Button Number: "))
    press = int(raw_input("Number of Button Presses: "))
    if b == 1:
        for x in range (0, press):
            p = [p[1], p[2], p[3], p[4], p[0]]
    if b == 2:
        for x in range (0, press):
            p = [p[4], p[0], p[1], p[2], p[3]]
    if b == 3:
        for x in range (0, press):
            p = [p[1], p[0], p[2], p[3], p[4]]
print p
