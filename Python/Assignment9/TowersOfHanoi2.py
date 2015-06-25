# Eric Bachmeier
# TowersOfHanoi2.py - This program shows the moves to complete Towers of Hanoi
# game and shows what discs are on each peg.
# May 28, 2013

def hanoi(fromPeg,toPeg,tempPeg,numDiscs):
    if numDiscs == 1:
        print "Move disc 1 from " + fromPeg + " to " + toPeg   
    else:
        hanoi(fromPeg, tempPeg, toPeg, numDiscs-1)
        if fromPeg == "A":
            a.remove(a[-1])
        if fromPeg == "B":
            b.remove(str(numDiscs))
        if fromPeg == "C":
            c.remove(str(numDiscs))
        if toPeg == "A":
            a.append(str(numDiscs))
        if toPeg == "B":
            b.append(str(numDiscs))
        if toPeg == "C":
            c.append(str(numDiscs))
        print "Peg A:",
        printpegs(a)
        print "Peg B:",
        printpegs(b)
        print "Peg C:",
        printpegs(c)
        print "Move disc " + str(numDiscs) + " from " + fromPeg + " to " + toPeg
        hanoi(tempPeg, toPeg, fromPeg, numDiscs-1);

def printpegs(l):
    for x in range(0,len(l)):
        print l[x],
    print
    
print "Towers of Hanoi"
print "---------------"
print
num = int(raw_input("Enter number of discs on peg A initially: "))
while num < 1:
    num = int(raw_input("Enter number of discs on peg A initially: "))
a = []
b = []
c = []
count = num
for x in range(0,num):
    a.append(count)
    count -= 1
print "Peg A:",
printpegs(a)
print "Peg B:",
printpegs(b)
print "Peg C:",
printpegs(c)
fPeg = "A"
tPeg = "C"
tmpPeg = "B"
repeat = True
while repeat:
    r = raw_input("Press Enter to see the next move or 'q' to quit. ")
    if r.upper() == "Q":
        repeat = False
    else:
        print
        hanoi(fPeg, tPeg, tmpPeg, num)
























def hanoi(fromPegl,toPegl,tempPegl,fPeg,tPeg,tmpPeg,numDiscs):
    if numDiscs == 1:
        toPegl.append(fromPegl[-1])
        fromPegl.pop(-1)
        print "Move disc 1 from " + fPeg + " to " + tPeg
        print"Peg A:"," ".join([str(x) for x in fPegl])
        print"Peg B:"," ".join([str(x) for x in tmpPegl])
        print"Peg C:"," ".join([str(x) for x in tPegl])
        raw_input("Press Enter To See Next Step.")
        print
    else:
        hanoi(fromPegl, tempPegl, toPegl,fPeg,tmpPeg,tPeg, numDiscs-1)
        toPegl.append(fromPegl[-1])
        fromPegl.pop(-1)
        print "Move disc " + str(numDiscs) + " from " + fPeg + " to " + tPeg
        print"Peg A:"," ".join([str(x) for x in fPegl])
        print"Peg B:"," ".join([str(x) for x in tmpPegl])
        print"Peg C:"," ".join([str(x) for x in tPegl])
        raw_input("Press Enter To See Next Step.")
        print
        hanoi(tempPegl, toPegl, fromPegl,tmpPeg,tPeg,fPeg, numDiscs-1)
print "Towers of Hanoi"
print "---------------"
print
num = int(raw_input("Enter number of discs on peg A initially: "))
if num < 1:
    print "Invalid number of discs"
else:
    fPeg = "A"
    tPeg = "C"
    tmpPeg = "B"
    fPegl,tPegl,tmpPegl=[x for x in range(num,0,-1)],[],[]
    print"Peg A:"," ".join([str(x) for x in fPegl])
    print"Peg B:"," ".join([str(x) for x in tmpPegl])
    print"Peg C:"," ".join([str(x) for x in tPegl])
    raw_input("Press Enter To See Next Step.")
    print
    hanoi(fPegl,tPegl,tmpPegl,fPeg,tPeg,tmpPeg, num)

    

