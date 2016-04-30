Now that we have substitute(Value, X, Formula, Result) and know that it
is used in:

evaluate([\,X,Formula], Value, Result) :- 
                             substitute(Value, X, Formula, Result).

What other rules do we need for evaluate.  reduce is the
top level that does one pass of reduction and evaluate handles the
case of application, invoked as:

reduce([Target, Value], Result) :- evaluate(Target, Value, Result).

note: a formula is a variable (dealt with above), a lambda
expression [\,x,F], or an application [F,G] (where x is
a variable and F and G are formulas).

