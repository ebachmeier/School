#ifndef TEACH_BARGRAPH1_VO_H
#define TEACH_BARGRAPH1_VO_H

#include <string>
#include <memory>
#include <vector>
#include <csvdata.h>
#include <algorithm>
#include "teachingdto.h"

class Teach_BarGraph1_VO
{
public:
    std::string name;
    std::vector<std::string> years;
    std::vector<std::string> teachingTypes;
    std::vector<std::vector<int>> values;
    Teach_BarGraph1_VO(std::shared_ptr<CSVData<TeachingDTO>> data, int start, int end);
};

#endif
