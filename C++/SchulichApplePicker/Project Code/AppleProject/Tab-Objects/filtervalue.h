#ifndef FILTERVALUE_H
#define FILTERVALUE_H

#include <string>
#include "DTO/filteradapter.h"

enum FilterValueType: unsigned int{
    FILTERNAME, FILTERYEAR, FILTERTYPE
};

class FilterValue
{
public:
    virtual std::string *getValue(FilterAdapter*);
};

class NameValue: public FilterValue{
public:
    static FilterValue *Instance();
    std::string *getValue(FilterAdapter *f);
protected:
    NameValue(){}
private:
    static FilterValue *_instance;
};

class YearValue: public FilterValue{
public:
    static FilterValue *Instance();
    std::string *getValue(FilterAdapter *f);
protected:
    YearValue(){}
private:
    static FilterValue *_instance;
};

class TypeValue: public FilterValue{
public:
    static FilterValue *Instance();
    std::string *getValue(FilterAdapter *f);
protected:
    TypeValue(){}
private:
    static FilterValue *_instance;
};

//Factory for filter value getters
FilterValue *getFilterValue(FilterValueType t);
#endif // FILTERVALUE_H
