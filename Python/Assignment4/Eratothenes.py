# Eric Bachmeier
#      The purpose of this program is to generate a list of 1000 random integers 
# and say at what positions the inputted number occurs in the list.
# Mar. 6, 2013

print "Eratothenes"
print # Print title sequence and intro
print "This program finds all of the prime numbers from 2 to 5000 using the"
print "Sieve of Eratosthenes."
print
# Ask user to hit enter to see all of the primes
raw_input("Press ENTER to see the prime numbers")
print
# Make list from 2-5000 all True
e = [True for i in range(0,5000)]
for number in range(0,5000):
    if number == 0 or number == 1:
        e[number] = False # Set number to false if it is 0 or 1
    else:
        if e[number] == True:
            c = 2 # Counter starts at 2
            div = 0 # Divide equals 0
            while div < 5000: # While less than 5000 check for division of number
                try:
                    div = number * c # Check multiple
                    e[div] = False # Set False the number times the multiple
                    c = c + 1 # Counter c += 1
                except:
                    pass # Remains True if not multiple
for i in range(0,5000):
    if e[i] == True: # Print all prime (True) numbers
        print i,
