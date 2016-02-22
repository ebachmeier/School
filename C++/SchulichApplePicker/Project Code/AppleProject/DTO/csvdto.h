#ifndef CSVDTO_H
#define CSVDTO_H

#include <vector>
#include <string>

#include "CSV-Parser/csvparser.h"
#include "DTO/bargraphadapter.h"
#include "DTO/treelistadapter.h"
#include "DTO/filteradapter.h"

#define NPUBHEADER 27
#define NPUBMANDATORY 9
#define NGRAHEADER 32
#define NGRAMANDATORY 13
#define NPREHEADER 20
#define NPREMANDATORY 6
#define NTEAHEADER 22
#define NTEAMANDATORY 10

enum FilterType: unsigned int;
enum CSVType: unsigned int;

class CSVLineValidator;
class CSVField;
class BarGraphAdapter;
class FilterAdapter;
class TreeListAdapter;

class CSVDTO
{
    //Header for this csv
    std::vector<std::string> header;
    //Validated lines in the CSV File
    std::vector<std::vector<CSVField>> validLines;
    //Error lines in the CSV File
    std::vector<std::vector<CSVField>> errorLines;

    //Adapters
    std::vector<FilterAdapter> filterDTOs;
    std::vector<BarGraphAdapter> barGraphDTOs;
    std::vector<TreeListAdapter> treeListDTOs;

    //Line validation strategy
    CSVLineValidator *lineValidator = 0;
    CSVType type; //Type of csv
    std::size_t nMan; //Number of mandatory headers
    std::string fileName; //file name

    //Sets the properties for reading the csv
    void setReadProperties(std::vector<CSVField> *f);

    bool validateLine(std::vector<CSVField> *line);

public:
    //Creates a new data set of the chosen type from the given file
    CSVDTO(std::string *fname, CSVType t);

    //Returns the list of filterDTOS for use in filtering
    std::vector<FilterAdapter> *getFilterDTOs();
    //Returns the list of bargraphDTOs for use in constructing bargraphs
    std::vector<BarGraphAdapter> *getBarGraphDTOs();
    //Returns the list of tree list dtos for use in making the tree list
    std::vector<TreeListAdapter> *getTreeListDTOs();

    //Returns the file name for this DTO
    std::string *getFile();

    //Returns list of error lines
    std::vector<std::vector<CSVField>> *getErrorLines();
    //Tries to validate the error lines
    //Returns true if change was made
    bool validateErrors(std::vector<std::vector<std::string>> *newErr);
    //Ignores all errors
    void clearErrors();
    //Ignores one error
    void removeError(int i);

    //Returns of mandatory lines
    size_t getNMan();
    //Returns the header for this csv
    std::vector<std::string> *getHeader();
    //Returns the domain of the CSV
    std::string *getDomain();

    //True if the dto has any valid lines
    bool hasValid();
    //Returns true if the dto has error lines
    bool hasErrors();

    //returns the type of the csv
    std::size_t getType();

    //Saves the validated lines of the csv
    void save(std::string *fname);
};

#endif // CSVDTO_H
