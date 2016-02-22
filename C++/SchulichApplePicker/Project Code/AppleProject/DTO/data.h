#ifndef DATA_H
#define DATA_H

/* Singleton class that will hold up to 4 sets of csv data, for use in
 * the program
 */

#include <vector>
#include <string>
#include <memory>

enum CSVType: unsigned int;
class CSVDTO;
class CSVField;

class Data
{
public:
    static Data *Instance();

    //Attempts to load a new csv of type t from the given file
    //Will throw errors that need to be caught and displayed to the user
    //File not found, missing columns, csv format error, TODO duplicate columns
    bool loadDTO(std::string *fname, CSVType t);
    //Checks if a dto is empty. If it is returns true
    //and clears it
    CSVDTO *getDTO(std::size_t t);
    bool isEmpty(std::size_t t);
    //Return true if the csv of type t has error lines
    bool hasErrors(std::size_t t);
    //Returns the most recently loaded type of csv
    CSVType getLastType();
    //Returns the short file name
    std::string getShortFileName(CSVType t);
    //Returns the list of headers for the csv
    std::vector<std::string> *getHeaders(CSVType t);
    //Returns the number of mandatory headers for the csv
    std::size_t getNMan(CSVType t);
    //Returns the list of errors rows for the csv
    std::vector<std::vector<CSVField>> *getErrorLines(CSVType t);
    //Clears all error rows from the csv
    void ignoreAllErrors(CSVType t);
    //Loads the updated error lines and tries to validate them
    bool validateNewErrors(std::vector<std::vector<std::string>> *newErr, CSVType t);
    void removeErrorLine(int line, CSVType t);

    //Save the csv
    void saveCSV(std::string *fname, std::size_t t);
protected:
    Data();
private:
    static Data* _instance;
    CSVType lastType;
    std::vector<std::shared_ptr<CSVDTO>> csv;
};

#endif // DATA_H
