#ifndef CSVLINEVALIDATOR_H
#define CSVLINEVALIDATOR_H

/* A strategy pattern of line validators. As opposed to field validators which
 * simply check that each field contains the correct type of data, line
 * validators validate the line to make sure the data in it is correct
 *
 * For example start date <= end date
 */

#include <vector>
#include <string>

enum CSVType: unsigned int;
class CSVField;

class CSVLineValidator
{
public:
    static CSVLineValidator* Instance();
    virtual bool validate(std::vector<CSVField> *line);
protected:
    CSVLineValidator(){}
private:
    static CSVLineValidator* _instance;
};

//Validate a publication csv line (nothing to check currently)
class PublicationLineValidator: public CSVLineValidator
{
public:
    static CSVLineValidator* Instance();
    bool validate(std::vector<CSVField> *);
protected:
    PublicationLineValidator(){}
private:
    static CSVLineValidator* _instance;
};

//Valiadtes a grant csv line (start year <= end year)
class GrantLineValidator: public CSVLineValidator
{
public:
    static CSVLineValidator *Instance();
    bool validate(std::vector<CSVField> *line);
protected:
    GrantLineValidator(){}
private:
    static CSVLineValidator* _instance;
};

//Validates a presentation csv line (nothing to check currently)
class PresentationLineValidator: public CSVLineValidator
{
public:
    static CSVLineValidator* Instance();
    bool validate(std::vector<CSVField> *);
protected:
    PresentationLineValidator(){}
private:
    static CSVLineValidator* _instance;
};

//Validates a teaching csv line (start year < end year)
//Hours per Session * Number of Session = Total Hours
class TeachingLineValidator: public CSVLineValidator
{
public:
    static CSVLineValidator* Instance();
    bool validate(std::vector<CSVField> *line);
protected:
    TeachingLineValidator(){}
private:
    static CSVLineValidator* _instance;
};

CSVLineValidator *getCSVLineValidator(CSVType t);

#endif // CSVLINEVALIDATOR_H
