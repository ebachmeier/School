#include "Tab-Objects/filtervalue.h"

using namespace std;

FilterValue *getFilterValue(FilterValueType t){
    switch(t){
        case(FILTERNAME):return NameValue::Instance();
        case(FILTERYEAR):return YearValue::Instance();
        case(FILTERTYPE):return TypeValue::Instance();
    }
    return 0;
}

string *FilterValue::getValue(FilterAdapter*){
    return 0;
}

FilterValue* NameValue::_instance = 0;

FilterValue* NameValue::Instance(){
    if(_instance == 0) _instance = new NameValue();
    return _instance;
}
string *NameValue::getValue(FilterAdapter *f){
    return f->getName();
}

FilterValue* YearValue::_instance = 0;

FilterValue* YearValue::Instance(){
    if(_instance == 0) _instance = new YearValue();
    return _instance;
}
string *YearValue::getValue(FilterAdapter *f){
    return f->getYear();
}

FilterValue* TypeValue::_instance = 0;

FilterValue* TypeValue::Instance(){
    if(_instance == 0) _instance = new TypeValue();
    return _instance;
}
string *TypeValue::getValue(FilterAdapter *f){
    return f->getType();
}
