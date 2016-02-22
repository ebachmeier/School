#include "csvsaver.h"

#include <iostream>
#include <fstream>

#include <CSV-Data/csvfield.h>

using namespace std;

void saveCSV(string *fname, vector<string> *header, vector<vector<CSVField>> *lines){
    ofstream out;
    out.open(*fname);

    //Write the header
    out << header->at(0);
    for(size_t i = 1; i < header->size(); ++i){
        out << "," << header->at(i);
    }
    out << endl;

    //write the lines
    for(size_t i = 0; i < lines->size(); ++i){
        vector<CSVField> *line = &lines->at(i);

        CSVField *field = &line->at(1);
        out << escapeField(field);
        for(size_t j = 2; j < line->size(); ++j){
            field = &line->at(j);
            out << "," << escapeField(field);
        }
        out << endl;
    }

    out.close();
}

string escapeField(CSVField *field){
    string result = "\"";
    string *f = field->getField();
    for(size_t i = 0; i < f->size(); ++i){
        char l = (*f)[i];
        result += l;
        if(l == '\"') result += l;
    }
    result += "\"";

    return result;
}
