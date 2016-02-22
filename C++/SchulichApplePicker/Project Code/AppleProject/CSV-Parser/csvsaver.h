#ifndef CSVSAVER_H
#define CSVSAVER_H

#include <string>
#include <vector>

class CSVField;


void saveCSV(std::string *fname, std::vector<std::string> *header,
             std::vector<std::vector<CSVField>> *lines);

std::string escapeField(CSVField *field);

#endif // CSVSAVER_H
