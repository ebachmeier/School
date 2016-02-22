#ifndef CSVFIELD_H
#define CSVFIELD_H

/* Holds the string field of a row in the CSV. Has a defined validator
 * that validates the data depending on what type of data we
 * expect to be in the field
 */

#include <string>

class CSVFieldValidator;

class CSVField
{
    std::string value, field; //The values of the field (possibly with an '*' removed)
    CSVFieldValidator *validator = 0; //The validation strategy for this field
    bool asterisk = false; //True if the field has a leading asterisk, false otherwise

public:
    CSVField(CSVFieldValidator *v);

    CSVField(CSVFieldValidator *v, std::string s);

    //Returns true if the field is valid, false otherwise
    //Also reformats the string if valid
    bool validate();

    //Returns the field value (modified by asterisk)
    std::string *getField();

    //Sets the field of the object. Behavior depends on the possibilty
    //of a leading '*'
    void setField(std::string *s);

    //Returns the value of the field (ie with no asterisk)
    std::string *getValue();
};

#endif // CSVFIELD_H
