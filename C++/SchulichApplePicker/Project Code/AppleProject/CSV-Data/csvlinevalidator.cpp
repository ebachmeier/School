#include "csvlinevalidator.h"

#include "CSV-Data/csvfield.h"
#include "CSV-Data/csvtype.h"

using namespace std;

CSVLineValidator* CSVLineValidator::_instance = 0;

CSVLineValidator* CSVLineValidator::Instance(){
    if(_instance == 0) _instance = new CSVLineValidator();
    return _instance;
}

bool CSVLineValidator::validate(vector<CSVField> *){
    return true;
}

CSVLineValidator* PublicationLineValidator::_instance = 0;

CSVLineValidator* PublicationLineValidator::Instance(){
    if(_instance == 0) _instance = new PublicationLineValidator();
    return _instance;
}

bool PublicationLineValidator::validate(vector<CSVField> *){
    return true;
}


CSVLineValidator* GrantLineValidator::_instance = 0;

CSVLineValidator* GrantLineValidator::Instance(){
    if(_instance == 0) _instance = new GrantLineValidator();
    return _instance;
}

bool GrantLineValidator::validate(vector<CSVField> *line){
    int startY = stoi(*line->at(1).getValue());
    int endY = stoi(*line->at(2).getValue());
    return (startY <= endY);
}


CSVLineValidator* PresentationLineValidator::_instance = 0;

CSVLineValidator* PresentationLineValidator::Instance(){
    if(_instance == 0) _instance = new PresentationLineValidator();
    return _instance;
}

bool PresentationLineValidator::validate(vector<CSVField> *){
    return true;
}

CSVLineValidator* TeachingLineValidator::_instance = 0;

CSVLineValidator* TeachingLineValidator::Instance(){
    if(_instance == 0) _instance = new TeachingLineValidator();
    return _instance;
}

bool TeachingLineValidator::validate(vector<CSVField> *line){
    int startY = stoi(*line->at(1).getValue());
    int endY = stoi(*line->at(2).getValue());

    double hpers = stod(*line->at(8).getValue());
    double ns = stod(*line->at(9).getValue());
    double totalh = stod(*line->at(10).getValue());

    return ((startY <= endY)&&(totalh == (hpers*ns)));
}

CSVLineValidator *getCSVLineValidator(CSVType t){
    switch(t){
        case PUBLICATION: return PublicationLineValidator::Instance();
        case GRANTS: return GrantLineValidator::Instance();
        case PRESENTATION: return PresentationLineValidator::Instance();
        case TEACHING: return TeachingLineValidator::Instance();
    }
    return CSVLineValidator::Instance();
}
