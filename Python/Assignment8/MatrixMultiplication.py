# Eric Bachmeier
# The purpose of this program is to read a text file containing two matrices 
# and determine the product of them.
# May 10, 2013

inFile = open('MatrixAandB.txt','r')
m = inFile.readline().rstrip('\n')
d1 = m.split(" ")
r1 = int(d1[0])
c1 = int(d1[1])
m1 = []
for x in range(0,r1):
    m = inFile.readline().rstrip('\n')
    line = m.split(" ")
    m1.append(line)
m = inFile.readline().rstrip('\n')
d2 = m.split(" ")
r2 = int(d2[0])
c2 = int(d2[1])
m2 = []
for i in range(0,r2):
    m = inFile.readline().rstrip('\n')
    line = m.split(" ")
    m2.append(line)
inFile.close()
print "---",
for x in range(0,len(m1[0])-1):
    print "   ",
print "---"
for y in range(0,len(m1)):
    print "|",
    for x in range(0,len(m1[0])):
        print str(m1[y][x]).center(3),
    print "|"
print "---",
for x in range(0,len(m1[0])-1):
    print "   ",
print "---"
print
print "         X"
print
print "---",
for x in range(0,len(m2[0])-1):
    print "   ",
print "---"
for y in range(0,len(m2)):
    print "|",
    for x in range(0,len(m2[0])):
        print str(m2[y][x]).center(3),
    print "|"
print "---",
for x in range(0,len(m2[0])-1):
    print "   ",
print "---"
print
print "         ="
print
m3 = [[0 for c in range(0,c2)] for r in range(0,r1)]
for z in range(0,r1):
    col2 = 0
    for z1 in range(0,c1):
        total = 0
        for z2 in range(0,r2):
            total += int(m1[z][z1])*int(m2[z1][z2])
        m3[z][col2] = total
        col2 += 1
print m3
    
    


