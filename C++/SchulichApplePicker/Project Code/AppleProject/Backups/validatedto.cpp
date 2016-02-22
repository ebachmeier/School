#include "validatedto.h"
#include "Utility/stringfunctions.h"
#include <iostream>
using namespace std;


bool validateString(string s){
    if(s.length() == 0) return false;
    if(s[0] != '*') return true;
    else{
        string whitespaces (" \t\f\v\n\r");
        size_t found = s.find_last_not_of(whitespaces);
        return(found != 0);
    }
}

bool isLeapYear(int y){
    if((y%4) == 0){
       if((y%100) == 0){
           if((y%400) == 0){
               return true;
           }
           return false;
       }
       return true;
    }
    return false;
}

bool makeDate(string *s){
    if(s->length() == 0) return false;

    vector<string> elm;
    stringstream ss(*s);
    string item;

    //Split around /
    while(getline(ss, item, '/')) elm.push_back(item);

    //More than three tokens
    if(elm.size() > 3) return false;

    //Check that only numerical data remains.
    vector<int> ielm(elm.size());
    for(int i = 0; i < (int)elm.size(); i++){
        for(int j = 0; j < (int)elm[i].length(); j++){
            if(!isdigit(elm[i][j])) return false;
        }
        ielm.push_back(atoi(elm[i].c_str()));
    }

    //Sort the array
    sort(ielm.begin(), ielm.end());

    //Check if the year is in the correct range.
    if((ielm.back() < 1900)||(ielm.back() > 2100)) return false;

    //Check that DD/MM/YYYY is valid
    if(ielm.size() == 3){
        int m[] = {31,isLeapYear(ielm.back())?29:28,31,30,31,30,31,31,30,31,30,31};
        if(((ielm[0] < 12)&&(ielm[1] > m[ielm[0]]))||((ielm[1] < 12)&&(ielm[0] > m[ielm[1]]))) return false;
    }
    //Check that MM/YYYY is valid
    if(ielm.size() == 2){
        if(ielm[0] > 12) return false;
    }

    *s = to_string(ielm.back());
    return true;
}

bool validateDate(string *s){
    return makeDate(s);
}

bool validateAuthorName(string *str){
    string s = *str;
    if(s[s.length() - 1] == '.'){
        s = s.substr(0, s.length() - 1);
    }

    vector<string> elm;
    stringstream ss(s);
    string item;

    //Split around ' '
    while(getline(ss, item, ' ')) elm.push_back(item);


    string alpha = u8"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "ùûüÿàâæçéèêëïîôœÙÛÜŸÀÂÆÇÉÈÊËÏÎÔŒ-";
    for(int k = 0; k < (int)elm.size(); k++){
        trimString(&(elm[k]));
        for(int j = 0; j < (int)elm[k].length(); j++){
            if(alpha.find(elm[k][j]) == string::npos){
                return false;
            }
        }
    }

    *str = "";
    for(size_t k = 0; k < elm.size(); k++){
        *str = *str + elm[k] + " ";
    }

    return true;
}

bool makeAuthors(string *str){
    //return true;
    string s = *str;
    if(s.length() == 0) return false;

    vector<string> elm;
    stringstream ss(s);
    string item;

    //Split around ,
    while(getline(ss, item, ',')) elm.push_back(item);
    for(int i = 0; i < (int)elm.size(); i++){
        //Make sure no comma deliniated entry is whitespace
        trimString(&elm[i]);
        if(elm[i].length() == 0) return false;
        if(!validateAuthorName(&(elm[i]))) return false;
    }

    *str = "";
    for(int i = 0; i < (int)elm.size(); i++){
        *str = *str + elm[i];
    }

    return true;
}

bool makeMoney(string *str){
    //make copy of the string so the original is preserved if error is found
    string s = *str;

    //If string is empty return false.
    if(s.length() == 0) return false;

    //If string starts with a $ remove it
    if(s[0] == '$') s = s.substr(1,s.length());

    vector<string> elm;
    stringstream ss(s);
    string item;

    //Split around "," and then paste the string back together
    while(getline(ss, item, ',')) elm.push_back(item);
    s = "";
    for(int i = 0; i < (int)elm.size(); i++){
        trimString(&(elm[i]));
        s = s + elm[i];
    }

    //Period is false if no period has been found
    bool period = false;

    //Check to see if all digits are one and at most one period
    for(int i = 0; i < (int)s.length(); i++){
        if(!isdigit(s[i])){
            if((period)||(s[i] != '.')) return false;
            else period = true;
        }
    }

    *str = s;
    return true;
}

bool validateMoney(string *s){
    return makeMoney(s);
}

bool validateAuthors(string *s){
    return makeAuthors(s);
}

/* Checks the 9 mandatory fields for a publication DTO.
 * The check is made in reverse order for ease of unpacking
 * the encoded int to display which entries are invalid.
 */
int validatePublication(std::vector<string> *fields){
    int result = 0;

    if(!validateAuthors(&(*fields)[8])) result+=1;
    result <<= 1;

    //Check the 7 mandatory fields
    for(int i = 7; i > 0; i--){
        if(!validateString((*fields)[i])) result+=1;
        result <<= 1;
    }

    if(!validateDate(&(*fields)[0])) result+=1;
    return result;
}

/* Checks the 7 mandatory fields for a presentation DTO.
 * The check is made in reverse order for ease of unpacking
 * the encoded int to display which entries are invalid.
 */
int validatePresentation(std::vector<string> *fields){
    int result = 0;

    if(!validateAuthors(&(*fields)[8])) result+=1;
    result <<= 1;

    //Check the 9 mandatory fields
    for(int i = 7; i > 0; i--){
        if(!validateString((*fields)[i])) result+=1;
        result <<= 1;
    }

    if(!validateDate(&(*fields)[0])) result+=1;
    return result;
}

/* Checks the 13 mandatory fields for a grant DTO.
 * The check is made in reverse order for ease of unpacking
 * the encoded int to display which entries are invalid.
 * Jennifer/Jaisen, did you mean to call this validateGrant? I renamed it to silence errors
 */
int validateGrant(std::vector<string> *fields){
    int result = 0;
    
    if(!validateAuthors(&(*fields)[12])) result+=1;
    result <<= 1;
    
    if(!validateMoney(&(*fields)[11])) result+=1;
    result <<= 1;

    //Check the 13 mandatory fields - the coinvestigators
    for(int i = 10; i > 1; i--){
        if(!validateString((*fields)[i])) result+=1;
        result <<= 1;
    }
    
    if(!validateDate(&(*fields)[1])) result+=1;
    result <<= 1;
    if(!validateDate(&(*fields)[0])) result+=1;
    return result;
}


int validateTeaching(std::vector<string> * fields)
{
    int result = 0;

    for(int i = 9; i >= 0; i--) {
        if(!validateString((*fields)[i])) result+=1;
        result <<= 1;
    }

    if(!validateDate(&(*fields)[2])) result+=1;
    if(!validateDate(&(*fields)[3])) result+=1;
    if((*fields)[2] >(*fields)[3]) result+=1;
    return result;
}
