# Reading and writing from a file
writeListToFile(List, File) :-
	open(File, write, Stream),
	write(Stream, List), nl, 
	close(Stream).
	
readFileToList(File, List) :-
	open(File, read, Stream),
	get_char(Stream, List),
	process(List, Stream),
	close(Stream).
	
process(end_of_file, _) :- !.

process(Character, Stream) :-
	get_char(Stream, CharacterNext),
	process(CharacterNext, Stream).
	
# Copying a file stream without the use of a list
copyFileToFile(FileIn, FileOut) :- 
	open(FileIn, read, StreamIn),
	open(FileOut, write, StreamOut),
	copy_stream_data(FileIn, FileOut),
	close(FileIn), 
	close(FileOut).
	
# findall to list page numbers
find(Word, List) :- 
	findall(Page, index(Word, Page), List).
	
# setof page numbers with no listing duplicates
find(Word, List) :- 
	setof(Page, index(Word, Page), List).