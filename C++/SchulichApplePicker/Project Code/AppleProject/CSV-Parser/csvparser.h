#ifndef CSVPARSER
#define CSVPARSER

#include <string>
#include <vector>

#include "CSV-Parser/csv.h"
#include "Utility/stringfunctions.h"
#include "CSV-Data/csvfield.h"

#define QUOTE '"'
#define SEP ','

//Modified CSV.H
namespace error{
    struct base : std::exception{
        const char*what()const throw(){
            return 0;
        }
    };

    struct escaped_string_not_closed :
            base{};
    struct csv_format_error :
            base{};
    struct missing_header_error :
            base{};
    struct duplicate_header_error :
            base{};
}

class CSVParser
{
    //Line Reader
    std::shared_ptr<io::LineReader> lineReader;
    char* nextLine;

    //Vector that keeps track of order of columns in CSV relative to header
    std::vector<int> order;

    //header variables
    std::size_t nHeader;

    //csvVariables
    std::size_t nCol;
    std::size_t nMan;

    //Gets the next column on the line (modified from CSV.H)
    static const char*find_next_column_end(const char*col_begin){
    while(*col_begin != SEP && *col_begin != '\0')
        if(*col_begin != QUOTE)
            ++col_begin;
        else{
            do{
                ++col_begin;
                while(*col_begin != QUOTE){
                    if(*col_begin == '\0')
                        throw error::escaped_string_not_closed();

                    ++col_begin;
                    }
                    ++col_begin;
                }while(*col_begin == QUOTE);
            }
        return col_begin;
    }

    //Returns the next column
    void chop_next_column(
            char*&line, char*&col_begin, char*&col_end
    ){
            assert(line != nullptr);

            col_begin = line;
            // the col_begin + (... - col_begin) removes the constness
            col_end = col_begin + (find_next_column_end(col_begin) - col_begin);

            if(*col_end == '\0'){
                    line = nullptr;
            }else{
                    *col_end = '\0';
                    line = col_end + 1;
            }
    }

    //Parse a csv line with deliniator ',' and escape character "
    std::vector<std::string> parseLine(char* line){
        std::vector<std::string> result;

        while(line != nullptr){
            char*col_begin, *col_end;
            chop_next_column(line, col_begin, col_end);
            std::string s(col_begin);
            trimString(&s);
            unescape(&s);
            trimString(&s);
            result.push_back(s);
        }

        return result;
    }

    //Gets the next line of the csv hasNext should be called first.
    char *getNext(){
        char *result = nextLine;
        nextLine = lineReader->next_line();
        return result;
    }

    //Unescapes a trimmed field from the csv
    void unescape(std::string *s){
        std::string result = "";
        //Check if we need to unquote this line
        if((*s)[0] == QUOTE) *s = s->substr(1, s->length() - 2);
        else return;
        for(std::size_t i = 0; i < s->length(); i++){
            result += (*s)[i];
            if((*s)[i] == QUOTE) i++;
        }
        *s = result;
        return;
    }

public:
    CSVParser(std::string fname, std::vector<std::string> *header, std::size_t man){
        lineReader = std::shared_ptr<io::LineReader>(new io::LineReader(fname));

        nHeader = header->size();
        nMan = man;

        std::vector<std::string> csvHeader = parseLine(lineReader->next_line());
        nCol = csvHeader.size();

        //check for duplicate headers
        for(std::size_t i = 0; i < csvHeader.size(); i++){
            std::vector<std::string>::iterator s,e;
            s = csvHeader.begin();
            e = csvHeader.end();
            if(find(s+i+1, e, csvHeader.at(i)) != e)
                throw error::duplicate_header_error();
        }

        //Initailize all the order values
        for(std::size_t i = 0; i < nCol; i++){
            std::vector<std::string>::iterator j,s,e;
            s = header->begin();
            e = header->end();
            j = std::find(s, e, csvHeader.at(i));
            if(j == e){
                order.push_back(-1);
            }
            else{
                order.push_back(j - s);
            }
        }

        //Check that each mandatory header is mapped somewhere.
        for(std::size_t i = 0; (i < nMan); i++){
            std::vector<int>::iterator j,s,e;
            s = order.begin();
            e = order.end();
            j = std::find(s, e, i);
            //A mandatory header has no index in the order (ie is missing)
            if(j == e){
                throw error::missing_header_error();
            }
        }

        nextLine = lineReader->next_line();
    }

    void readLine(std::vector<CSVField> *fields){
        std::vector<std::string> csvLine;
        std::string oldLine = "";
        char *charLine;

        while(csvLine.size() < nCol){
            if(!this->hasNext()) throw error::csv_format_error();
            std::string newLine = oldLine + this->getNext();
            oldLine = newLine + "\n";

            try{
                charLine = (char*)malloc(newLine.length() + 1);
                std::strcpy(charLine, newLine.c_str());
                std::vector<std::string> line = parseLine(charLine);

                //Check if line is empty
                if(line.size() == 0){
                    free(charLine)    ;
                    break;
                }
                csvLine = std::vector<std::string>(line.begin(), line.end());
            }
            //If new line is not escaped we need to paste them together
            catch(error::escaped_string_not_closed){}

            free(charLine);
        }

        //If the loop was exited not reading the expected number of columns
        if(csvLine.size() != nCol){
            throw error::csv_format_error();
        }

        for(std::size_t i = 0; i < nHeader; i++){
            std::vector<int>::iterator j,s,e;
            s = order.begin();
            e = order.end();
            j = std::find(s, e, i);

            if(j!=e) fields->at(i).setField(&csvLine[j - s]);
        }
    }

    bool hasNext(){
        return (nextLine != nullptr);
    }
};

#endif // CSVPARSER

