# Eric Bachmeier
# This program tell you the certain digit in the sequence that you enter.
# Date Compleetd Januray 10, 2012

print "Fibonacci Series"
print "----------------"
print
print "The Fibonacci series is a sequence of numbers in which each number in "
print "the sequence equals the sum to the two preceding numbers. The first two"
print "numbers in the sequence are 1. The sequence of numbers are 1,1,2,3,5,8,"
print "13,21,..."
print
repeat = True
while repeat == True:
    term = int(raw_input("Which term would you like to see? (1-50) "))
    while term < 1 or term > 50:
        print "You have entered an invalid number."
        term = int(raw_input("Which term would you like to see? (1-50)"))
    fib = [0,1,1]
    for x in range(3,term+1):
        fib.append(fib[x-1] + fib[x-2])
    print "The term",term,"in the Fibonacci series is",fib[term],"."
    print
    response = raw_input("Would you like to see another term? (Y/N) : ")
    if response == "N" or response == "n":
        repeat = False
print
print "Good bye!"
