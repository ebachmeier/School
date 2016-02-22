# Eric Bachmeier
#      The purpose of this program is to calculate the cost per CD from text
# file information, and display the name and cost in a table.
# Apr. 11, 2013

print "Cost of Producing and Manufacturing a Music CD"
print "----------------------------------------------"
print # Print title
inFile = open('CDTracks.txt', 'r') # Open file
line = inFile.readline().rstrip('\n') # Read first CD
print "Name of Music CD".ljust(40), # Print table headings
print "Cost".ljust(10)
print "----------------".ljust(40),
print "----".ljust(10)
print
songs = [] # Create blank song names list
cursor = 0 # Cursur to print through names list
while line != "":
    name = "" # Create blank name string
    length = "" # Create blank minutes in length string
    for x in range(0,len(line)):
        if line[x] == ":":
            length = line[x+1:] # Add track lengths to string
            break
        else:
            name += line[x] # Add name to name, character by character
    songs.append(name) # Append name to song names list
    tracks=[] # Create blank tracks list
    y = "" # Create blank string for tracks
    for i in range(0,len(length)):
        if length[i]!= " ":
            y += length[i] # Append lengths to y
        if length[i] == " " or i == len(length)-1:
            if y != "":
                tracks.append(y) # Append last number, not spaces
            y = ""
    pc = 0.45 # 45 cents per CD
    ps = int(tracks[0])*0.08 # 8 cents per track
    pm = 0 # Cost per minute variable
    tl = 0 # total length in minutes variable
    for i in range(1,len(tracks)):
        tl += int(tracks[i]) # tl is sum of tracks in minutes
    if tl <= 60:
        for i in range(1,len(tracks)):
            pm += float(tracks[i])*0.03 # Cost per minute is 3 cents
    else:
        for i in range(1,len(tracks)):
            pm += float(tracks[i])*0.02 # Cost per minute is 2 cents, if more than 60 minutes
    totalcost = pc + ps + pm # Calculate total cost per CD
    print songs[cursor].ljust(41)+"$"+str(totalcost).ljust(10) # Print name, cost
    cursor += 1 # Add 1 to scroll cursor
    line = inFile.readline().rstrip('\n') # Read next line
inFile.close() # Close file
