#ifndef BARGRAPHADAPTER_H
#define BARGRAPHADAPTER_H

/* An adpater that turns a validated line of the csv into
 * a form that makes creating a bar graph easy.
 *
 * Our bar graphs (currently) need a year, a type and a value
 * from each used line to be constructed
 */

#include <vector>
#include <string>

class CSVField;
enum CSVType: unsigned int;

class BarGraphAdapter
{
    std::vector<CSVField> *line;
    std::size_t year, type;
    double value;
public:
    BarGraphAdapter(std::vector<CSVField> *csvline, CSVType csvtype);

    std::string *getYear();
    std::string *getType();
    double *getValue();
};

#endif // BARGRAPHADAPTER_H
