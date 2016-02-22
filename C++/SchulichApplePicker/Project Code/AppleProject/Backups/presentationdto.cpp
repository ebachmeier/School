#include "presentationdto.h"

//Default Constructor
PresentationDTO::PresentationDTO()
{
    //Mandatory Fields
    name = domain = type = role = title = "";
    date = 0;

    authorship = shared_ptr<vector<string>>( new vector<string> );

    activityType = geoScope = host = country = province = city =
    attendeeNum = hours = teachScore = presentation = remarks = citation = personalRenumeration = "";//optional

}

PresentationDTO::~PresentationDTO()
{
    authorship.reset();
}

std::string PresentationDTO::getName(){
    return name;
}

std::string PresentationDTO::getBarField1(int btype){
    return to_string(date);
}

std::string PresentationDTO::getBarField2(int btype){
    return type;
}

double PresentationDTO::getBarValue(int btype){
    return 1.0;
}
