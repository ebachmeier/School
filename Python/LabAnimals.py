# Eric Bachmeier
# Date Completed: October 4, 2011

print "Lab Animals Program"
print "-------------------"
print
print "This program is designed to have users enter the initial animal"
print "population, the initial food supply and the amount of food added at"
print "the end of each hour. It will then make a chart telling users the"
print "the number of animals at the start and end and the amount of food"
print "at the start and end, while saying what hour it is."
print

repeat = True
while repeat == True:
    animals = int (raw_input ("Enter the initial amount of animals: "))
    food = int (raw_input ("Enter the intitial amount of food: "))
    food_added = int (raw_input ("Enter the amount of food added: "))
    print "Hour".rjust(4),"Animals at the start".rjust(16),"Food at the start".rjust(13),"Food at the end".rjust(11),"Animals at end".rjust(14)
    print "----".rjust(4),"--------------------".rjust(16),"-----------------".rjust(13),"---------------".rjust(11),"--------------".rjust(14)
    hour = 1
    end_population = 0
    food_end = 0
    while end_population <= food_end:
        food_end = food + food_added - animals
        end_population = animals * 2
        print str (hour).rjust(4), str (animals).rjust(16), str (food).rjust(13), str (food_end).rjust(11), str (end_population).rjust(14)
        hour = hour + 1
        animals = end_population
        food = food_end
        print
        if end_population > food_end:
            print "The animals will outgrow the food supply after", hour - 1, "hours."
        print
    response = raw_input("Would you like to enter another set of conditions?(Y/N): ")
    print
    if response == "N" or response == "n":
        repeat = False
print "Good bye!"

