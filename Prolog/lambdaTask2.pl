At the bottom of reduction, is the substitution of a Value 
for a variable in a Formula, invoked in my code by:

evaluate([\,X,Formula], Value, Result) :- 
                       substitute(Value, X, Formula, Result).


substitute(Value,X,X,Value) :- atomic(X).
substitute(_,X,Y,Y) :- atomic(X), atomic(Y), X \= Y.

What other rules do I need for substitute?

note: a formula is a variable (dealt with above), a lambda
expression [\,x,F], or an application [F,G] (where x is
a variable and F and G are formulas).

