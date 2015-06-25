# Eric Bachmeier
# This program prompts users for their age and tells them if they are old enough to vote.
# Date Completed: September 16, 2011

print "Voting Age Program"
print
age = int (raw_input ("Enter your age: "))
print
if age < 18:
    print "You are not old enough to vote."
else:
    print "You are old enough to vote."
