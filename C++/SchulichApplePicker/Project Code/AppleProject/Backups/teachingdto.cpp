#include "teachingdto.h"

using namespace std;

TeachingDTO::TeachingDTO() {
    // mandatory
    name = domain = program = type = scope = "";

    startDate = endDate = 0;

    hoursSession = numberSession = 0;

    totalHours = 0;

    //optional
    institution = faculty = department = division = location = facultyComments = students = lecture = development = stipend = comment = "";
}

TeachingDTO::~TeachingDTO() {
}

std::string TeachingDTO::getName(){
    return name;
}

std::string TeachingDTO::getBarField1(int btype){
    return to_string(endDate);
}

std::string TeachingDTO::getBarField2(int btype){
    if(btype == 1){
        return program;
    }
    else{
        return program + "(" + type + ")";
    }
}

double TeachingDTO::getBarValue(int btype){
    return 1.0;
}

int TeachingDTO::getYear(int btype){
    return endDate;
}

std::vector<std::string> TeachingDTO::getTreePath(int btype){
    return treePath;
}

std::vector<double> TeachingDTO::getTreeValues(int btype){
    return treeValues;
}
