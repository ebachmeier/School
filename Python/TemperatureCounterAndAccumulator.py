# Eric Bachmeier
# Date Completed: September 30, 2011

import math # Import the math library
# Print Introduction
print "Celcius Temperature Counter and Accumulator"
print
print "This program has users enter temperature's in degress celcius and it calculates how many temperatures were entered and the average temperature."
print
num_temp = 0 # counter for number of temperatures
temp_total = 0 # accumulator for the amount of temperatures
repeat = True
while repeat==True:
    sales_amount = float(raw_input("Enter sales amount $"))
    num_sales = num_sales + 1
    sales_total = sales_total + sales_amount
    print
    response = raw_input("Are you finished?(Y/N):")
    print
    if response=="Y" or response=="y":
        repeat=False
print
print "Number of sales entered: " + str(num_sales)
print "Total amount of sales $"+ str(sales_total)
average = sales_total/num_sales # calculate the average
print "The average sale was $" + str(round(average,2))
