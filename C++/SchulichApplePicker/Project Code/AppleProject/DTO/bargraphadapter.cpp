#include "bargraphadapter.h"

#include "CSV-Data/csvfield.h"
#include "CSV-Data/csvtype.h"

using namespace std;

BarGraphAdapter::BarGraphAdapter(vector<CSVField> *csvline, CSVType csvtype)
{
    line = csvline;
    switch(csvtype){
        case PUBLICATION:
            year = 1;
            type = 5;
            value = 1.0;
            break;

        case GRANTS:
            {
                year = 2;
                type = 5;

                string *status = line->at(6).getValue();
                if(*status == "Funded") value = stod(*line->at(12).getValue());
                else value = 0.0;
                break;
            }
        case PRESENTATION:
            year = 1;
            type = 4;
            value = 1.0;
            break;
        case TEACHING:
            year = 2;
            type = 4;
            value = stod(*line->at(10).getValue());
            break;
    }
}

string *BarGraphAdapter::getYear(){
    return line->at(year).getField();
}

string *BarGraphAdapter::getType(){
    return line->at(type).getField();
}

double *BarGraphAdapter::getValue(){
    return &value;
}
