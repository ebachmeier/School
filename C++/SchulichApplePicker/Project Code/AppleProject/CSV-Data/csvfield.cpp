#include "csvfield.h"

#include "CSV-Data/csvfieldvalidator.h"
#include "Utility/stringfunctions.h"

using namespace std;

CSVField::CSVField(CSVFieldValidator *v){
    validator = v;
}

CSVField::CSVField(CSVFieldValidator *v, std::string s){
    validator = v;
    setField(&s);
}

bool CSVField::validate(){
    return validator->validate( (&value) );
}

string *CSVField::getField(){
    field = (asterisk?"* ":"") + value;
    return &field;
}

void CSVField::setField(string *s){
    if((*s)[0] == '*'){
        asterisk = true;
        value = s->substr(1,s->length());
        trimLeft(&value);
    }
    else{
        asterisk = false;
        value = string(*s);
    }
}

string *CSVField::getValue(){
    return &value;
}
