%% In exercise 16 at end of Chapter 4, it says: 
%%   Each item below takes a lambda application.  We have 
%%   used a lot of parenthesis to help you parse the 
%%   expressions.  Reduce each formula until no redex 
%%   remains.  One of the items requires renaming of a 
%%   bound variable.

%%   16d-ish
%%      ( ((\x.(\y.(y(xy)))) (\p.(pp)) ) q)

%% which I will write in prolog as:

ex16d([[[\,x,[\,y,[y,[x,y]]]], [\,p,[p,p]]],q]).
