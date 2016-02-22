#ifndef STRINGFUNCTIONS
#define STRINGFUNCTIONS

#include <string>

//String trimming
//From /http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

//Trim the whitespace from left of sting
void trimLeft(std::string *s);

//Trim the whitepsace from right of string
void trimRight(std::string *s);

//Trim the whitespace from both left and right of string
void trimString(std::string *s);

//End Borrowed functions

std::string formatNumber(double d);
#endif // STRINGFUNCTIONS

