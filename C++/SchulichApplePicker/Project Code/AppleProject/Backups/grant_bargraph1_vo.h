#ifndef GRANT_BARGRAPH1_VO
#define GRANT_BARGRAPH1_VO

#include <string>
#include <memory>
#include <vector>
#include <csvdata.h>
#include <algorithm>
#include "grantdto.h"

// Dummy class for Jennifer/Jaisen to populate with data
// You guys need to create the grant_bargraph1_vo.cpp in order to match this file
//
class Grant_BarGraph1_VO
{
public:
    std::string name;
    std::vector<std::string> years;
    std::vector<std::string> grantTypes;
    std::vector<std::vector<int>> values;
    Grant_BarGraph1_VO(std::shared_ptr<CSVData<GrantDTO>> data, int start, int end);
};

#endif // GRANT_BARGRAPH1_VO

