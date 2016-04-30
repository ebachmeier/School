Now that we have evaluate(Formula, Value, Result) and know that it
is used in:

reduce([Target, Value], Result) :- evaluate(Target, Value, Result).

What other rules do we need for reduce.  reduce is the
top level that does one pass of reduction.

note: a formula is a variable (dealt with above), a lambda
expression [\,x,F], or an application [F,G] (where x is
a variable and F and G are formulas).

