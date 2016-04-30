readFileToList(File, List) :- open(File, read, Stream),
                              readStreamToList(Stream, List),
                              close(Stream).

readStreamToList(Stream, List) :- get_code(Stream, Ch),
                                  readMoreStreamToList(Stream, Ch, List).

readMoreStreamToList(Stream, -1, List) :- List = [].
readMoreStreamToList(Stream, Ch, List) :- Ch \= -1,
                                          readStreamToList(Stream, Rest),
                                          List = [Ch | Rest].

printToStandardOutput([Ch | Rest]) :- put_code(Ch), 
                                      printToStandardOutput(Rest).

printToStandardOuput([]) :- nl.

