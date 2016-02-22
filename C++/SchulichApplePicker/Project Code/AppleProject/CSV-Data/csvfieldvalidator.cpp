#include "CSV-Data/csvfieldvalidator.h"

#include <vector>
#include <sstream>
#include <algorithm>

#include "Utility/stringfunctions.h"

using namespace std;

bool CSVFieldValidator::validate(string *){
    return true;
}

CSVFieldValidator* StringValidator::_instance = 0;

CSVFieldValidator* StringValidator::Instance(){
    if(_instance == 0) _instance = new StringValidator;
    return _instance;
}

bool StringValidator::validate(string *s){
    return (s->length() != 0);
}

CSVFieldValidator* DateValidator::_instance = 0;

CSVFieldValidator* DateValidator::Instance(){
    if(_instance == 0) _instance = new DateValidator;
    return _instance;
}

bool DateValidator::validate(string *s){
    if(s->length() == 0) return false;

    vector<string> elm;
    stringstream ss(*s);
    string item;

    //Split the string around '/'
    while(getline(ss, item, '/')) elm.push_back(item);

    //More than three tokens means date is invalide max is D/M/Y
    if(elm.size() > 3) return false;

    //Check that only numerical data remains.
    vector<int> ielm(elm.size());
    for(size_t i = 0; i < elm.size(); i++){
        for(size_t j = 0; j < elm[i].length(); j++){
            if(!isdigit(elm[i][j])) return false;
        }
        ielm.push_back(atoi(elm[i].c_str()));
    }
    //TODO fix this
    //Sort the array
    sort(ielm.begin(), ielm.end());

    //Check if the year is in a reasonable range. Year will be largest value
    if((ielm.back() < 1900)||(ielm.back() > 2100)) return false;

    //Check that DD/MM/YYYY is valid
    if(ielm.size() == 3){
        int m[] = {31,isLeapYear(ielm.back())?29:28,31,30,31,30,31,31,30,31,30,31};
        if(((ielm[0] < 12)&&(ielm[1] > m[ielm[0]]))||((ielm[1] < 12)&&(ielm[0] > m[ielm[1]]))) return false;
    }
    //Check that MM/YYYY is valid
    if(ielm.size() == 2){
        if(ielm[0] > 12) return false;
    }

    //Update s to just YYYY
    *s = to_string(ielm.back());
    return true;
}

CSVFieldValidator* NameListValidator::_instance = 0;

CSVFieldValidator* NameListValidator::Instance(){
    if(_instance == 0) _instance = new NameListValidator;
    return _instance;
}

bool NameListValidator::validate(string *s){
    //Make copy of s to avoid local changes
    string str = *s;
    if(str.length() == 0) return false;

    vector<string> elm;
    stringstream ss(str);
    string item;

    //Split around ',' which hopfully leaves us with an array of names
    while(getline(ss, item, ',')) elm.push_back(item);
    for(size_t i = 0; i < elm.size(); i++){
        //Make sure no comma deliniated entry is whitespace
        trimString(&elm[i]);
        if(elm[i].length() == 0) return false;
    }

    //Otherwise reconstruct the list in our expected format
    *s = "";
    for(size_t i = 0; i < elm.size(); i++){
        if(i!=0) *s = *s + ",";
        *s = *s + elm[i];
    }

    return true;
}

CSVFieldValidator* MoneyValidator::_instance = 0;

CSVFieldValidator* MoneyValidator::Instance(){
    if(_instance == 0) _instance = new MoneyValidator;
    return _instance;
}

bool MoneyValidator::validate(string *s){
    //Make copy of s to avoid local changes
    string str = *s;

    //If string is empty return false.
    if(str.length() == 0) return false;

    //If string starts with a $ remove it
    if(str[0] == '$') str = str.substr(1,str.length());

    //If string is empty after removing $ return false.
    if(str.length() == 0) return false;

    vector<string> elm;
    stringstream ss(str);
    string item;

    //Split around "," and then paste the string back together
    while(getline(ss, item, ',')) elm.push_back(item);
    str = "";
    for(int i = 0; i < (int)elm.size(); i++){
        trimString(&(elm[i]));
        str = str + elm[i];
    }

    //Period is false if no period has been found
    bool period = false;

    //Check to see if all characters are digits (or at most one period)
    for(int i = 0; i < (int)str.length(); i++){
        if(!isdigit(str[i])){
            if((period)||(str[i] != '.')) return false;
            else period = true;
        }
    }

    //update the reformated string
    *s = str;
    return true;
}

bool isLeapYear(int y){
    if((y%4) == 0){
       if((y%100) == 0){
           if((y%400) == 0){
               return true;
           }
           return false;
       }
       return true;
    }
    return false;
}

CSVFieldValidator *getCSVValidator(ValidatorType t)
{
    switch(t){
        case STRINGVALIDATOR: return StringValidator::Instance();
        case DATEVALIDATOR: return DateValidator::Instance();
        case NAMELISTVALIDATOR: return NameListValidator::Instance();
        case MONEYVALIDATOR: return MoneyValidator::Instance();
    }

    return new CSVFieldValidator();
}
