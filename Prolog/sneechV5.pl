%% sneech ::= '*' 
   sneech --> "*" .
%% sneech ::=  '(' <sneech> ')' 
   sneech --> "(", sneech, ")" .
%% sneech ::= <bander>  '*' <sneech> 
   sneech --> bander, "*", sneech .
%% sneech ::= '*' <sneech> 
   sneech --> "*", sneech .
%% bander ::= <bander2> 
   bander --> bander2 .
%% bander ::=  '%', <bander> 
   bander --> "%", bander .
%% bander ::=  '%'
   bander --> "%" .
%% bander2 ::= '+$+' bander2 
   bander2 --> "+$+", bander2 .
%% bander2 ::= '+$+'
   bander2 --> "+$+" .
%% bander2 ::=  '#' bander2 
   bander2 -->  "#", bander2 .
%% bander2 ::=  '#' 
   bander2 -->  "#" .
