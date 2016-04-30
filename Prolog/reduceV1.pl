%% This file is for handling lambda reduction rules in Chapter 4 of textbook

%% A formula can be one of three things:
%%              a variable, e.g., x
%%              a lambda expression, e.g., [\,x,[x,x]]
%%              an application, e.g., [[\,x,[x,x]], p]


%% One of the trickier parts is the business about renaming free variables.
%% For example, in [[\x,[x,x]], x] the x on the right side of the application
%% is actually different from the x on the left side of the application,
%% and it is necessary to rename it to avoid confusion.

%% We don't have any examples that press this issue, so this part is pretty
%% much untested.

%% For the stuff we have been discussing in class, skip forward to the
%% definition of reduction predicate.

unique(Formula, FormulaRenamed) :- freeRename(Formula, [], 0, FormulaRenamed).

freeRename(Formula, Bound, Count, RenamedFormula) :- atomic(Formula),
                      renameHelper(Formula, Bound, Count, RenamedFormula).
freeRename([Target, Value], Bound, Count, [RTarget, RValue]) :-
                       TCount is Count * 2,
                       VCount is Count * 2 + 1,
                       freeRename(Target, Bound, TCount, RTarget),
                       freeRename(Value, Bound, VCount, RValue).
freeRename([\, Var, Formula], Bound, Count, [\, Var, RFormula]) :-
                       freeRename(Formula, [Var | Bound], Count, RFormula).

renameHelper(Formula, [Formula | _], _, Formula).
renameHelper(Formula, [First | Rest], Count, RenamedFormula) :-
                       First \= Formula,
                       renameHelper(Formula, Rest, Count, RenamedFormula).
renameHelper(Formula, [], Count, RenamedFormula) :-
                  atom_chars(Formula, F),
                  reverse(F, FR),
                  number_chars(Count, D),
                  reverse(D, DR),
                  append(DR, FR, DRFR),
                  reverse(DRFR, DF),
                  atom_chars(RenamedFormula, DF).


%% So, reduction is the thing that evaluates lambda expressions
%% until they are reduced as far as they can be reduced.

reduction(Formula,Reduced) :- reduce(Formula,Result), 
                         reduceAgain(Formula, Result, Reduced).

% reduceAgain is really part of the definition of reduction, it allows
% us to introduce an extra variable and cause the rule to be applied
% multiple times.  Basically, we keep reducing as long as reducing
% changes the formula.

reduceAgain(Formula, Formula, Result) :- internalReduction(Formula, Result).
reduceAgain(Formula, Result, Reduced) :- Formula \= Result,
                         reduction(Result, Reduced).

%% internalReduction is the part I was missing Tuesday Feb 2nd, which
%% was needed for exercise 16 d in textbook.  It looks at applications
%% that arise inside the formula as well as at the top level application.

internalReduction(X,X) :- atomic(X).
internalReduction([\,X,Formula],[\,X,Reduced]) :- reduction(Formula,Reduced).
internalReduction([Target,Value], [TargetR, ValueR]) :-
                                              reduction(Target, TargetR),
                                              reduction(Value, ValueR).

% reduce does one step of reduction.

reduce(X,X) :- atomic(X).
reduce([\,X,Formula], [\,X,Reduced]) :- reduce(Formula, Reduced).
reduce([Target, Value], Result) :- evaluate(Target, Value, Result).

% evaluate handles the case of formulas that are applications.

evaluate(Target, Value, [Target, Value]) :- atomic(Target).
evaluate([Target, Value], Other, Result) :-
    reduce([Target, Value], PartWay), 
    reduce([PartWay, Other], Result).
evaluate([\,X,Formula], Value, Result) :- 
                             substitute(Value, X, Formula, Result).

% substitute does the actual substitution when the left side of an
% application is a lambda formula.

substitute(Value,X,X,Value) :- atomic(X).
substitute(_,X,Y,Y) :- atomic(X), atomic(Y), X \= Y.
substitute(Value,X,[First,Second], [FirstResult, SecondResult]) :-
              substitute(Value,X,First,FirstResult),
              substitute(Value,X,Second,SecondResult).
substitute(_,X,[\,X,Formula],[\,X,Formula]).
substitute(Value,X,[\,Y,Formula],[\,Y,Result]) :-
                        X \= Y,
                        substitute(Value,X,Formula,Result).
