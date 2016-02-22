#include "DTO/csvdto.h"

#include <iostream>
#include <fstream>

#include "CSV-Data/csvtype.h"
#include "CSV-Data/csvlinevalidator.h"
#include "CSV-Data/csvfieldvalidator.h" //FilterTypr
#include "CSV-Data/csvfield.h"
#include "CSV-Parser/csvsaver.h"

using namespace std;

CSVDTO::CSVDTO(string *fname, CSVType t)
{
    type = t;

    //Holds the validation properties for the csv
    vector<CSVField> f;

    //Save the file name for use in saving the validated csv
    fileName = *fname;

    //Set the properties of the parser based on the type of csv
    setReadProperties(&f);

    //Makes a new csv parser parsing file fname, using the given header
    //and number of mandatory fields
    CSVParser parser = CSVParser(fileName, &header, nMan);

    //Keeps track of the line of the csv we are on
    int nLines = 2;

    //Until there are no more lines to parse.
    while(parser.hasNext()){
        //Read the new line of the csv
        parser.readLine(&f);

        vector<CSVField> line;
        //Add the line of the CSV to the dto
        line.push_back(CSVField(getCSVValidator(STRINGVALIDATOR)));
        string lineN = "Line " + to_string(++nLines);
        line.at(0).setField(&lineN);

        //Save the read line for validation and storage
        for(size_t j = 0; (j < f.size()); j++ ){            
            line.push_back(f.at(j));
        }

        //Add dto to correct list based on validity
        if(validateLine(&line)) validLines.push_back(line);
        else errorLines.push_back(line);
    }
}

vector<FilterAdapter> *CSVDTO::getFilterDTOs(){
    if(filterDTOs.size() < validLines.size()){
        for(size_t i = 0; i < validLines.size(); ++i){
            filterDTOs.push_back(FilterAdapter(&validLines[i], type));
        }
    }

    return &filterDTOs;
}

vector<BarGraphAdapter> *CSVDTO::getBarGraphDTOs(){
    if(barGraphDTOs.size() < validLines.size()){
        for(size_t i = 0; i < validLines.size(); ++i){
            barGraphDTOs.push_back(BarGraphAdapter(&validLines[i], type));
        }
    }

    return &barGraphDTOs;
}

vector<TreeListAdapter> *CSVDTO::getTreeListDTOs(){
    if(treeListDTOs.size() < validLines.size()){
        for(size_t i = 0; i < validLines.size(); ++i){
            treeListDTOs.push_back(TreeListAdapter(&validLines[i], type));
        }
    }

    return &treeListDTOs;
}

/*Sets up the properties of the csvdto and the csv reader based on
 *the given csv type. The number of mandatory fields, the name of
 * the fields, and the validation strategy for each field need to be
 * set.
 */
void CSVDTO::setReadProperties(std::vector<CSVField> *f){
    lineValidator = getCSVLineValidator(type);
    switch(type){
    case PUBLICATION:{
        nMan = NPUBMANDATORY;
        string head[] = {"Status Date","Member Name","Primary Domain",
            "Publication Status","Type","Role",
            "Journal Name | Published In | Book Title | etc.","Title","Author(s)",

            "Pubmed Article ID","Peer Reviewed?","Author #","Volume","Issue",
            "Page Range","DOI","Website","Journal Impact Factor","International",
            "Publisher","Is Presentation?","Personal Remuneration",
            "Trainee Details","Is Most Significant Publication?",
            "Most Significant Contribution Details","Education Publication",
            "ISBNISSN"
            };

        header = std::vector<std::string>(head, head + NPUBHEADER);

        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        for(size_t i = 0; i < 7; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }
        f->push_back(CSVField(getCSVValidator(NAMELISTVALIDATOR), ""));

        for(size_t i = f->size(); i < NPUBHEADER; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }

        break;
    }
    case GRANTS:{
        nMan = NGRAMANDATORY;

        string head[] = {"Start Date","End Date","Member Name","Primary Domain",
            "Funding Type","Status", "Peer Reviewed?","Industry Grant?", "Role",
            "Title", "Principal Investigator", "Total Amount", "Co-Investigators",

            "Short Title", "Application Summary", "Grant Purpose", "Area",
            "Grand and/or Account #", "Prorated Amount", "Administered By",
            "Funding Source", "Project", "Currency", "Received Amount",
            "Member Share", "Monetary", "Reportable", "Hours Per Week",
            "Personnel Paid", "Rnw", "Education Grant", "Duplicate Reported"
                 };

        header = std::vector<std::string>(head, head + NGRAHEADER);

        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        for(size_t i = 0; i < 9; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }
        f->push_back(CSVField(getCSVValidator(MONEYVALIDATOR), ""));
        f->push_back(CSVField(getCSVValidator(NAMELISTVALIDATOR), ""));

        for(size_t i = f->size(); i < NGRAHEADER; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }

        break;
    }
    case PRESENTATION:{
        nMan = NPREMANDATORY;

        string head[] = {"Date","Member Name","Primary Domain","Type","Role", "Title",

                  "Activity Type","Geographical Scope","Host","Country","Province",
                  "City","Number of Attendees","Hours","Teaching Effectiveness Score",
                  "Education Presentation","Remarks","Authorship",
                  "Rest of Citation","Personal Remuneration"
                 };

        header = std::vector<std::string>(head, head + NPREHEADER);

        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        for(size_t i = 0; i < 5; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }

        for(size_t i = f->size(); i < NPREHEADER; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }

        break;
    }
    case TEACHING:{
        nMan = NTEAMANDATORY;

        string head[] = {"Start Date","End Date","Member Name","Primary Domain","Program",
                      "Type of Course / Activity","Geographical Scope",
                      "Hours per Teaching Session or Week",
                      "Number of Teaching Sessions or Weeks","Total Hours",

                      "Number Of Trainees",

                      "Institution / Organization","Faculty","Department","Division",
                      "Location","Faculty Member Additional Comments","Student Name(s)",
                      "Initial Lecture","Faculty Development","Stipend Received","Comment"
                 };

        header = std::vector<std::string>(head, head + NTEAHEADER);

        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        f->push_back(CSVField(getCSVValidator(DATEVALIDATOR), ""));
        for(size_t i = 0; i < 5; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR)));
        }
        f->push_back(CSVField(getCSVValidator(MONEYVALIDATOR), ""));
        f->push_back(CSVField(getCSVValidator(MONEYVALIDATOR), ""));
        f->push_back(CSVField(getCSVValidator(MONEYVALIDATOR), ""));

        for(size_t i = f->size(); i < NTEAHEADER; i++){
            f->push_back(CSVField(getCSVValidator(STRINGVALIDATOR), ""));
        }

        break;
    }
    }
}

string *CSVDTO::getFile(){
    return &fileName;
}

vector<vector<CSVField>> *CSVDTO::getErrorLines(){
    return &(errorLines);
}

size_t CSVDTO::getNMan(){
    return nMan;
}

vector<string> *CSVDTO::getHeader(){
    return &header;
}

bool CSVDTO::validateErrors(vector<vector<string>> *newErr){
    bool result = false;
    for(int i = (newErr->size() - 1); i >= 0 ; --i){
        vector<CSVField> *line = &errorLines.at(i);
        vector<string> *newLine = &(newErr->at(i));

        for(size_t j = 0; j < newLine->size(); ++j){
            CSVField *field = &(line->at(j + 1));
            string *newField = &(newLine->at(j));
            field->setField(newField);
        }

        if(validateLine(line)){
            result = true;
            validLines.push_back(*line);
            errorLines.erase(errorLines.begin() + i);
        }
    }

    return result;
}

string *CSVDTO::getDomain(){
    vector<CSVField> *line = &validLines.at(0);
    switch(type){
        case PUBLICATION:
            {
                CSVField *field = &line->at(3);
                return field->getField();
            }
        case GRANTS:
            {
                CSVField *field = &line->at(4);
                return field->getField();
            }
        case PRESENTATION:
            {
                CSVField *field = &line->at(3);
                return field->getField();
            }
        case TEACHING:
            {
                CSVField *field = &line->at(4);
                return field->getField();
            }
    }
    return 0;
}

bool CSVDTO::hasValid(){
    return (validLines.size() > 0);
}

bool CSVDTO::hasErrors(){
    return (errorLines.size() > 0);
}

void CSVDTO::clearErrors(){
    errorLines.clear();
    errorLines.shrink_to_fit();
}

void CSVDTO::removeError(int i){
    errorLines.erase(errorLines.begin() + i);
}

bool CSVDTO::validateLine(vector<CSVField> *line){
    bool result = true;
    for(size_t i = 0; (i < nMan)&&result; i++){
        result &= line->at(i + 1).validate();
    }

    return result&&(lineValidator->validate(line));
}

size_t CSVDTO::getType(){
    return type;
}

void CSVDTO::save(std::string *fname){
    saveCSV(fname, &header, &validLines);
}
