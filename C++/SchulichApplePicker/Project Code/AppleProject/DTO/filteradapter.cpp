#include "filteradapter.h"

#include "CSV-Data/csvfield.h"
#include "CSV-Data/csvtype.h"

using namespace std;

FilterAdapter::FilterAdapter(std::vector<CSVField> *csvline, CSVType t)
{
    line = csvline;
    switch(t){
        case PUBLICATION:
            year = 1;
            name = 2;
            type = 5;
            break;
        case GRANTS:
            year = 2;
            name = 3;
            type = 5;
            break;
        case PRESENTATION:
            year = 1;
            name = 2;
            type = 4;
            break;
        case TEACHING:
            year = 2;
            name = 3;
            type = 4;
            break;
    }
}

string *FilterAdapter::getName(){
   return line->at(name).getField();
}

string *FilterAdapter::getYear(){
    return line->at(year).getField();
}

string *FilterAdapter::getType(){
    return line->at(type).getField();
}

