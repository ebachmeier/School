#ifndef FILTERADAPTER_H
#define FILTERADAPTER_H

/* An adaptor that turns a valid csv line into a form
 * that we can check against a filter object.
 *
 * The filter object will test that the data on the line
 * meets the user requirement for date range, memeber name,
 * and type.
 */

#include <vector>
#include <string>

enum CSVType: unsigned int;
class CSVField;

class FilterAdapter
{
    std::vector<CSVField> *line;
    std::size_t name, year, type;
public:
    FilterAdapter(std::vector<CSVField> *csvline, CSVType t);

    std::string *getName();
    std::string *getYear();
    std::string *getType();
};

#endif // FILTERADAPTER_H
