#ifndef TEACHINGDTO_H
#define TEACHINGDTO_H

#include <string>
#include <vector>
#include <memory>

class TeachingDTO
{
public:
    //mandatory:
    std::string name, domain, program, type, scope;

    float hoursSession, numberSession, totalHours;

    unsigned int startDate, endDate;

    //optional:
    std::string institution, faculty, department, division, location, facultyComments, students, lecture, development, stipend, comment;

    std::vector<std::string> treePath;
    std::vector<double> treeValues;

    TeachingDTO();
    ~TeachingDTO();
    std::string getName();
    std::string getBarField1(int btype = 1);
    std::string getBarField2(int btype = 1);
    double getBarValue(int btype = 1);

    std::vector<std::string> getTreePath(int btype = 1);
    std::vector<double> getTreeValues(int btype = 1);
    int getYear(int btype = 1);
};

#endif // TEACHINGDTO_H
