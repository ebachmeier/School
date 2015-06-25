# Eric Bachmeier
#      The purpose of this program is to promt the user for their height and
# weight, then calculate their BMI number and tell them what it means.
# Feb. 7, 2013

print "BMI"
print # Print opening sequence information
print "Body mass index is a measure of the weight of a person scaled according"
print "to their height."
print "BMI is defined as the individual's body weight divided by the square of"
print "the height."
print "It is almost always expressed in the unit kg / m"+u"\u00B2"+"."
print
# Validation code
def isnumber(num,valid):
    try:
        num = float(num)
    except:
        print"Invalid input."
        valid = False
    else:
        if num <= 0:
            print"Invalid input."
        else:
            valid = True
    return num,valid
# Promt user for weight and height
run = True
while run:
    valid = False
    print
    while not(valid):
        w = raw_input("Please enter your weight(kg): ")
        w,valid = isnumber(w,valid)
    valid = False
    while not(valid):
        h = raw_input("Please enter your height(m): ")
        h,valid = isnumber(h,valid)
    # Calculate BMI
    bmi = w/(h*h)
    print # Print answer
    print"Your BMI is",round(bmi,2)
    print
    # Make closing statement intervals
    if bmi < 15: # Print accompanying statement
        print"You are in the starvation category,"
        print"more calories and protein would be a good idea."
    elif bmi < 18.5:
        print"You are in the underweight category,"
        print"eating more often would be a good idea."
    elif bmi <= 25:
        print"You are in the ideal category,"
        print"keep up the good diet, and keep exercising."
    elif bmi <= 30:
        print"You are in the overweight category,"
        print"changing your diet and starting to exercise would be a good idea."
    elif bmi <= 40:
        print"You are in the obese category,"
        print"changing your diet and starting to exercise would be a good idea."
    else:
        print"You are in the morbidly obese category,"
        print"dramatic changes to your diet and lots of exercise are crucial, see a doctor."
    print
    # Repeat loop option
    response = raw_input("Would you like to calculate another BMI?(y/n): ")
    if response.upper() == "N" or response.upper() == "NO":
        run = False
        print
        print"Thankyou for using BMI program!"
