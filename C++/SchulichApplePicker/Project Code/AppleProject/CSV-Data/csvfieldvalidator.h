#ifndef CSVFEILDVALIDATOR
#define CSVFEILDVALIDATOR

/**
  Interface for the functions that will be validate the data we pull from each csv.

  A class will need to be implemented for each unique type of data that will need to
  be validated.

  ie Date, String, Money, List of Authors/contributors, etc

  The validator should have one function

  bool validate(string *s)

  It should return false if the field is invalid for any reason (data formatting in the csvs
  is highly inconsistant so do your best)

  It should return true if the field is valid, as well as update the pointer to a standardized format
  that we can use

  Ie for dates

  if the field is 30/30/1985 it should return false and s is still 30/30/1985

  if the field is 11/30/1985 it should return true and s should be updated to 1985 (the only
  relevant part of the data we need in a format we will expect.
  */
#include <string>

enum ValidatorType: unsigned int{
  STRINGVALIDATOR, DATEVALIDATOR, NAMELISTVALIDATOR, MONEYVALIDATOR
};

//Interface for validators
class CSVFieldValidator
{
public:
    virtual bool validate(std::string *);
};

/* String validator
 * A string field is valid if it's non-empty
 */
class StringValidator: public CSVFieldValidator
{
public:
    static CSVFieldValidator* Instance();
    bool validate(std::string *s);
protected:
    StringValidator(){}
private:
    static CSVFieldValidator* _instance;
};

/* Date validator
 * A date field is valid if it contains a valid
 * date configuration D/M/Y M/Y Y etc, checking
 * that D is a day of month M
 */
class DateValidator: public CSVFieldValidator
{
public:
    static CSVFieldValidator* Instance();
    bool validate(std::string *s);
protected:
    DateValidator(){}
private:
    static CSVFieldValidator* _instance;
};

/* Name list validator
 * A name list is valid if it contains at least
 * one name. Names are (hopefully) in the format
 * name1, name 2, name 3
 *
 * (possibly needs to check it the name of the
 * faculty memeber this line is associated with is in
 * the list?)
 */
class NameListValidator: public CSVFieldValidator
{
public:
    static CSVFieldValidator* Instance();
    bool validate(std::string *s);
protected:
    NameListValidator(){}
private:
    static CSVFieldValidator* _instance;
};

/* Money field validator
 * A money field is vaild if it is a valid if it is
 * a of the form XXXXXX.XX (possibly with a leading $)
 * Can also be used to validate doubles (the $ is stripped)
 */
class MoneyValidator: public CSVFieldValidator
{
public:
    static CSVFieldValidator* Instance();
    bool validate(std::string *s);
protected:
    MoneyValidator(){}
private:
    static CSVFieldValidator* _instance;
};

//Checks if given year is a leapyear
bool isLeapYear(int y);

//Used by vaidate name list to validate each name in the list
//bool validateAuthorName(std::string *s);

/* Takes in the type of validator you want and returns
 * the singleton class of that validation type.
 *
 */
CSVFieldValidator *getCSVValidator(ValidatorType t);

#endif // CSVFEILDVALIDATOR
