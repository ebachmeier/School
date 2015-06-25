# -*- coding: cp1252 -*-
# Eric Bachmeier
# The purpose of this program is to compute the total calories of a meal.
# Date Completed: November 7, 2011

print "Calorie Total"
print "-------------"
print
print "At STA's Fast Food Emporium there is a very simple menu. Each food"
print "item is selected by entering a digit choice. You will be prompted for the"
print "number of the food item that you would like. The program will output"
print "the total calories for the sleected meal."
print
print "Here are the choices for the menu: "
print
print "Here are the three burger choices:      Here are the three drink choices:"
print "1 – Cheeseburger (461 Calories)         1 – Soft Drink (130 Calories)"
print "2 – Fish Burger (431 Calories)          2 – Orange Juice (160 Calories)"
print "3 – Veggie Burger (420 Calories)        3 – Milk (118 Calories)"
print "4 – no burger                           4 – no drink"
print
print "Here are the three side order choices:  Here are the three dessert choices:"
print "1 – Fries (100 Calories)                1 – Apple Pie (167 Calories)"
print "2 – Baked Potato (57 Calories)          2 – Sundae (266 Calories)"
print "3 – Chef Salad (70 Calories)            3 – Fruit Cup (75 Calories)"
print "4 – no side order                       4 – no dessert"
print
repeat = True
while repeat == True:
    burger = int(raw_input("Please enter a burger choice: "))
    if burger <= 0 or burger >= 5:
        int(raw_input("Please enter a valid burger choice (Between 1 and 4): "))
    side = int(raw_input("Please enter a side order choice: "))
    if side <= 0 or side >= 5:
        int(raw_input("Please enter a valid side choice (Between 1 and 4): "))
    drink = int(raw_input("Please enter a drink choice: "))
    if drink <= 0 or drink >= 5:
        int(raw_input("Please enter a valid drink choice (Between 1 and 4): "))
    dessert = int(raw_input("Please enter a dessert choice: "))
    if dessert <= 0 or dessert >= 5:
        int(raw_input("Please enter a valid dessert choice (Between 1 and 4): "))
    print
    if burger == 1:
        a = 461
    if burger == 2:
        a = 431
    if burger == 3:
        a = 420
    if burger == 4:
        a = 0
    if side == 1:
        b = 100
    if side == 2:
        b = 57
    if side == 3:
        b = 70
    if side == 4:
        b = 0
    if drink == 1:
        c = 130
    if drink == 2:
        c = 160
    if drink == 3:
        c = 118
    if drink == 4:
        c = 0
    if dessert == 1:
        d = 167
    if dessert == 2:
        d = 266
    if dessert == 3:
        d = 75
    if dessert == 4:
        d = 0
    total = a + b + c + d
    print "Your total calorie count is ", total, "calories."
    print
    response = raw_input ("Would you like to enter another meal? (Y/N) ")
    if response == "N" or response == "n":
        repeat = False
    
        
