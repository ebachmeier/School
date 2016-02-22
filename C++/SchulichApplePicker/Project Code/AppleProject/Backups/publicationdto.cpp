#include "publicationdto.h"

using namespace std;

/* Here if we need it
string PUBLICATION_STATUS[] = {"Published", "In-Press/Accepted", "Submitted"};

string PUBLICATION_TYPE[] = {"Book Chapters", "Books", "Books Edited",
                             "Case Reports", "Clinical Care Guidlines",
                             "Commentaries", "Conference Proceedings", "Editorials",
                             "Invited Articals", "Journal Articals",
                             "Letters to Editor", "Magazine Enteries", "Manuals",
                             "Monographs", "Multimedia", "Newsletter Articles",
                             "Newspaper Articles", "Published Abstract",
                             "Supervised Student Publications", "Working Papers"};


string AUTHOR_ROLE[] = {"Principal Author", "Co-Author", "Collaborator",
                             "Senior Responsible Author", "Editor", "Reviewer"};

*/

int nextid = 0;

//Default Constructor
PublicationDTO::PublicationDTO()
{
    //Mandatory Fields
    name = domain = journalName = title = ISBN = status = type = role = "";
    date = 0;
    authors = shared_ptr<vector<string>>( new vector<string> );

    pubmedID = authorNumber = impactFactor = peerReviewed = international =
            presentation = mostSignificant = education = "";

    /* Commented out until we decide if they need to be not strings
    //Optional Fields
    volume = issue = pageRange = DOI = website = publisher = personalRenumeration =
    traineeDetails = mostSignificantDetails = "";
    pubmedID = authorNumber = 0;
    impactFactor = 0;
    peerReviewed = international = presentation = mostSignificant = education = false;
    */
    id = ++nextid;
}

PublicationDTO::~PublicationDTO()
{
    authors.reset();
}

std::string PublicationDTO::getName(){
    return name;
}

int PublicationDTO::getYear(int btype){
    return date;
}

std::string PublicationDTO::getBarField1(int btype){
    return to_string(date);
}

std::string PublicationDTO::getBarField2(int btype){
    return type;
}

double PublicationDTO::getBarValue(int btype){
    return 1.0;
}

vector<string> PublicationDTO::getTreePath(int btype){
    return treePath;
}

vector<double> PublicationDTO::getTreeValues(int btype){
    return treeValues;
}
