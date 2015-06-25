# Eric Bachmeier
#      The purpose of this program is to show arithmetic operations to output
# integers to the same base between 2 and 16.
# May 2, 2013

def op(info): # Define display operation function
    print
    print "  "+str(info[1])+" (base "+str(info[0])+") "+str(info[2])+" "+str(info[3])+" (base "+str(info[0])+")"
    info[1] = int(info[1],int(info[0]))
    info[3] = int(info[3],int(info[0]))
    info[0] = "10"
    print "= "+str(info[1])+" (base "+str(info[0])+") "+str(info[2])+" "+str(info[3])+" (base "+str(info[0])+")"
    if info[2] == "+":
        n = info[1]+info[3]
    elif info[2] == "-":
        n = info[1]-info[3]
    elif info[2] == "*":
        n = info[1]*info[3]
    elif info[2] == "/":
        n = info[1]/info[3]
    print "= "+str(n)+" (base",info[0]+")"
    string = ""
    b = int(info[4])
    while n > 0:
        r = n%b
        n = n/b
        if r > 9:
            r = chr(r+55)
        string = str(r)+string
    print "= "+str(string)+" (base "+str(info[4])+")"
    print
    
print "Base Arithmetic"
print "---------------"
print # Print introduction
print "This program performs arithmetic on numbers in any base from 2 to 16."
inFile = open('BaseArithmetic.txt','r')
info = inFile.readline().rstrip('\n')
while info != "":
    info = info.split(" ")
    op(info)
    info = inFile.readline().rstrip('\n')
inFile.close()


