#include "data.h"

#include "DTO/csvdto.h"
#include "CSV-Data/csvtype.h"

using namespace std;

Data* Data::_instance = 0;

Data::Data(){
    csv = vector<shared_ptr<CSVDTO>>(4);
}

Data* Data::Instance()
{
    if(_instance == 0) _instance = new Data;
    return _instance;
}

bool Data::loadDTO(string *fname, CSVType t){
    std::shared_ptr<CSVDTO> newcsv(new CSVDTO(fname, t));
    csv.at(t).swap(newcsv);
    lastType = t;

    return true;
}

CSVDTO *Data::getDTO(size_t t){
    return csv.at(t).get();
}

bool Data::isEmpty(size_t t){
    //If the pointer is null return true;
    if(!csv.at(t)) return true;
    //If the CSV has valid data return true;
    if(csv.at(t)->hasValid()) return false;
    //IF the CSV has errors left rturn true
    if(this->hasErrors(t)) return false;
    //Otherwise reset the pointer and return false;
    csv.at(t).reset();
    return true;
}

bool Data::hasErrors(size_t t){
    //If pointer is null return false;
    if(!csv.at(t)) return false;
    //If there are no error lines
    return (csv.at(t)->hasErrors());
}

CSVType Data::getLastType(){
    return lastType;
}

string Data::getShortFileName(CSVType t){
    string s = *csv.at(t)->getFile();
    return s.substr(s.find_last_of("\\")+1,s.length());
}

vector<string> *Data::getHeaders(CSVType t){
    return csv.at(t)->getHeader();
}

size_t Data::getNMan(CSVType t){
    return csv.at(t)->getNMan();
}

vector<vector<CSVField>> *Data::getErrorLines(CSVType t){
    return csv.at(t)->getErrorLines();
}

void Data::ignoreAllErrors(CSVType t){
    csv.at(t)->clearErrors();
}

bool Data::validateNewErrors(vector<vector<string>> *newErr, CSVType t){
    return csv.at(t)->validateErrors(newErr);
}

void Data::removeErrorLine(int line, CSVType t){
    csv.at(t)->removeError(line);
}

void Data::saveCSV(string *fname, size_t t){
    csv.at(t)->save(fname);
}
