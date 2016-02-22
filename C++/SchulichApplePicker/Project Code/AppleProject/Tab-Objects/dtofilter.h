#ifndef DTOFILTER_H
#define DTOFILTER_H

/* The filter object will be seeded with data taken from the UI and then
 * used to filter only those dtos which meet it's criteria: correct name,
 * correct type, correct date range.
 *
 * isValid should be called after construction to ensure that the filter is
 * valid: currently that start date <= end date
 */

#include <string>
#include <vector>

#include "DTO/filteradapter.h"

class FilterAdapter;

class DTOFilter
{
    std::vector<std::string> *values;
public:
    DTOFilter(std::vector<std::string> *v = 0);
    bool filter(FilterAdapter *b);
};

#endif // DTOFILTER_H
