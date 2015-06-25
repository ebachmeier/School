# Eric Bachmeier
# This program will count the maximum number of fish able to catch from
# the points
# November 8, 2011

print "Fish Points Program"
print "-------------------"
print
file_name = "FishPoints.txt"
working_file = open(file_name, "r")
trout = working_file.readline().rstrip("\n")
pike = working_file.readline().rstrip("\n") 
pickerel = working_file.readline().rstrip("\n")
maxpoints = working_file.readline().rstrip("\n")
if (int(maxpoints) !=1):
    print "You can catch", maxpoints, "points of fish."
else:
    print "You can catch", maxpoints, "point of fish."
if (int(trout) !=1):
    print "You can catch", trout, "points of trout."
else:
    print "You can catch", trout, "point of trout."
if (int(pike) !=1):
    print "You can catch", pike, "points of pike."
else:
    print "You can catch", pike, "point of pike."
if (int(pickerel) !=1):
    print "You can catch", pickerel, "points of pickerel."
else:
    print "You can catch", pickerel, "point of pickerel."
print
ways = 0
while (1 == 1):
    for t in range (0,int(maxpoints) + 1,1):
        for pik in range (0,int(maxpoints) + 1,1):
            for p in range (0,int(maxpoints) + 1,1):
                if (((int(pickerel) * p) + (int(trout) * t) + (int(pike) * pik)) != 0 and ((int(pickerel) * p) + (int(trout) * t) + (int(pike) * pik) <= int(maxpoints))):
                    ways = ways + 1
                    print "Trout", str(t), "Pike", str(pik),"Pickerel " + str(p) + "."
    break
working_file.close()
print
print "Number of ways to catch fish: ", ways
