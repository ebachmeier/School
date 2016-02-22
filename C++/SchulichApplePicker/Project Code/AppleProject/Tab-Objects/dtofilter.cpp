#include "dtofilter.h"

using namespace std;

DTOFilter::DTOFilter(std::vector<string> *v)
{
    values = v;
}

bool DTOFilter::filter(FilterAdapter *b){
    if((!values)||(values->size() == 0)) return true;
    bool result = true;


    string value = values->at(0); //start year
    result &= (value <= *b->getYear());
    if((values->size() == 1)||(!result)) return result;


    value = values->at(1); //end year
    result &= (*b->getYear() <= value);
    if((values->size() == 2)||(!result)) return result;


    value = values->at(2); //name
    result &= (value == *b->getName());
    if((values->size() == 3)||(!result)) return result;


    value = values->at(3); //type
    result &= ( (value == "-ALL-")||(value == *b->getType()) );
    return result;
}

