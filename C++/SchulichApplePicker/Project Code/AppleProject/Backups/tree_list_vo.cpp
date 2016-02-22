#include "tree_list_vo.h"
/*
/**
 * @brief tree_list_vo::tree_list_vo default constructor for tree_list_vo
 */
/*tree_list_vo::tree_list_vo()
{
    // default constructor
    num_pub_types = 0;
}

/**
 * @brief tree_list_vo::tree_list_vo overloaded constructor for tree_list_vo
 * @param _data is PUBLICATION data
 */
/*tree_list_vo::tree_list_vo(shared_ptr<CSVData<PublicationDTO> > _data)
{
    _data = _data;
    num_pub_types = 0;  // default 0 publication types
}

/**
 * @brief tree_list_vo::tree_list_vo overloaded constructor for tree_list_vo
 * @param _data is GRANT data
 */
/*tree_list_vo::tree_list_vo(shared_ptr<CSVData<GrantDTO> > _data)
{
    _data = _data;
    num_funding_types = 0;  // default 0 funding types
}

/**
 * @brief tree_list_vo::tree_list_vo overloaded constructor for tree_list_vo
 * @param _data is TEACHING data
 */
/*tree_list_vo::tree_list_vo(shared_ptr<CSVData<TeachingDTO> > _data)
{
    _data = _data;
    num_teach_types = 0;  // default 0 teaching types
}

/**
 * @brief tree_list_vo::tree_list_vo overloaded constructor for tree_list_vo
 * @param _data is PRESENTATION data
 */
/*tree_list_vo::tree_list_vo(shared_ptr<CSVData<PresentationDTO> > _data)
{
    _data = _data;
    num_pub_types = 0;  // default 0 presentation types
}




/**
 * @brief tree_list_vo::get_parent_set returns the parent set of the tree list vo object
 * @return parent_set of the tree_list_vo object
 */
/*vector<string_data_object> tree_list_vo::get_parent_set()
{
    return parent_set;
}

/**
 * @brief tree_list_vo::get_child_set returns the child set of the tree list vo object
 * @return child_set of the tree_list_vo object
 */
/*vector<vector<string_data_object> > tree_list_vo::get_child_set()
{
    return child_set;
}

// Functions to populate VO with various CSV data pointers

/**
 * @brief tree_list_vo::populate_for_publications populates the tree VO with publication data
 * @param _data shared pointer containing the csv parsed data
 * @param start is the initial date range filter
 * @param end is the final date range filter
 * @return 0 if it's executed successfully
 * COMPLETED BY JERRY DO NOT MODIFY
 */
/*int tree_list_vo::populate_for_publications(shared_ptr<CSVData<PublicationDTO> > _data, int start, int end)
{
    // Create the first empty child set
    vector<string_data_object> t;
    child_set.push_back(t);

    int start_index = 0;
    int date = 0;
    while(start_index < _data->dtos->size())    // Iterates through data to find first valid range
    {
        date = _data->dtos->at(start_index).date;

        if ((start <= date) && (end >= date))
        {
            break;            // Found the index of dto where the first legal date range is found
        }
        start_index += 1;
    }

    string_data_object first_sd;
    first_sd.label = _data->dtos->at(start_index).name; // Add first Member Name
    first_sd.num = 0;                                                        // Default is 0 publications
    child_set.at(0).push_back(first_sd);                          // Add first publication author

    string_data_object first_pub;                                   // Add first publication type
    first_pub.label = _data->dtos->at(start_index).type;
    first_pub.num = 0;                                                    // 0 publications first
    first_pub.value = -1;

    parent_set.push_back(first_pub);                             // 1 Author and 1 Pub inserted

    // start_index now contains the first DTO we begin at.
    for (int i = start_index; i < _data->dtos->size(); i ++)
    {
        date = _data->dtos->at(i).date;            // Get date of starting index
        if ((start <= date) && (end >= date))   // Should pass b/c starting at 1st valid data index
        {
            string author = _data->dtos->at(i).name;    // Temp name
            string pubtype = _data->dtos->at(i).type;   // Temp publication type

            int pub_value = find_label_index(pubtype, parent_set);
            if (pub_value == -1)    // New publication type
            {
                num_pub_types += 1;                      // Increment total publication count

                string_data_object new_pub;
                new_pub.label = pubtype;                // Set label of the new publication type
                new_pub.num = 1;                            // 1st of its pubtype found
                new_pub.value = -1;

                vector<string_data_object> empty_child;
                child_set.push_back(empty_child);

                parent_set.push_back(new_pub);

                string_data_object new_auth;        // Add 1st author of new publicaiton type
                new_auth.label = author;
                new_auth.num = 1;
                new_auth.value = -1;

                int index = find_label_index(pubtype, parent_set);
                child_set.at(index).push_back(new_auth);    // Add author to specific publication
            }

            if (pub_value != -1)    // Publication type exists, look for potential authors
            {
                parent_set.at(pub_value).num += 1;      // Add another entry for publications
                int auth_value = find_label_index(author, child_set.at(pub_value));

                if (auth_value == -1)   // New author is encountered
                {
                    string_data_object new_auth;    // Create new author
                    new_auth.label = author;
                    new_auth.num = 1;
                    new_auth.value = -1;
                    child_set.at(pub_value).push_back(new_auth);
                }
                else        // Author is already found, increment their count for publications
                {
                    vector<string_data_object> *tmp = &child_set.at(pub_value);
                    tmp->at(auth_value).num += 1;
                }
            }
        }
    }

    return 0;   // Exited with success.
}

/**
 * @param _data shared pointer containing the csv parsed data
 * @param start is the initial date range filter
 * @param end is the final date range filter
 * @param fType is the type of funding that the tree will populate
 * @return 0 if it's executed successfully
 */
/*int tree_list_vo::tree_list_vo::populate_for_grants(shared_ptr<CSVData<GrantDTO> > _data, int start, int end, const char* fType)
{
    // Create the first empty child set
    vector<string_data_object> t;
    child_set.push_back(t);
    
    int start_index = 0;
    // grants have a start and an end date
    int grant_start_date = 0;
    int grant_end_date = 0;
    
    // Iterates through data to find first valid range
    // valid --> EITHER grant_start_date OR grant_end_state is in the date range chosen by the user
    while(start_index < _data->dtos->size())
    {
        grant_start_date = _data->dtos->at(start_index).startDate;
        grant_end_date = _data->dtos->at(start_index).endDate;
        string grant_fType = _data->dtos->at(start_index).fundingType;
        
        if ((((start <= grant_start_date) && (end >= grant_start_date)) || ((start <= grant_end_date) && (end >= grant_end_date))) && fType == grant_fType){
            break;
        }
        
        start_index += 1;
    }

    //string_data_object.label holds author(memberName)
    string_data_object first_sd;
    
    if (start_index == _data->dtos->size()){
        first_sd.label = "";                                        // Add first faculty Name
        first_sd.num = 0;                                           // Default for this author is 0 grants
        parent_set.push_back(first_sd);                            // Add first grant author
    }

    //string_data_object.label holds funding type (grant or clinical)
    first_sd.label = _data->dtos->at(start_index).memberName;
    first_sd.num = 0;                                               // Default is 0 hours
    child_set.at(0).push_back(first_sd);                            // Add first name
    
    
    string_data_object first_grant;                                 // Add first funding type
    // Peer Reviewed or Industry Sponsored?
    if (_data->dtos->at(start_index).peerReviewed == "True"){
        first_grant.label = "Peer Reviewed";
    }
    else{
        first_grant.label = "Industry Grant";
    }
    first_grant.num = 0;                                            // Default for this funding type is 0
    first_grant.value = _data->dtos->at(start_index).totalAmount;   // add the value of the grant to the total sum for this funding type
    parent_set.push_back(first_grant);                              // 1 faculty1 and 1 grant inserted
    
    
    // start_index now contains the first DTO we begin at.
    for (int i = start_index; i < _data->dtos->size(); i ++)
    {
        grant_start_date = _data->dtos->at(i).startDate;            // Get start date of starting index
        grant_end_date = _data->dtos->at(i).endDate;                // Get end date of starting index
        string grant_fundingType = _data->dtos->at(i).fundingType;
        
        // Should pass b/c starting at 1st valid data index
        if (((start <= grant_start_date) && (end >= grant_start_date)) || ((start <= grant_end_date) && (end >= grant_end_date)) && fType == grant_fundingType)
        {
                
            string memberName = _data->dtos->at(i).memberName;     // Temp name
            
            // Find the label (Peer reviewed or Industry grant)
            string PRorIG = "";
            if (_data->dtos->at(i).peerReviewed == "True"){
                PRorIG = "Peer Reviewed";
            }
            else{
                PRorIG = "Industry Grant";
            }

            int grant_value = find_label_index(PRorIG, parent_set);

            if (grant_value == -1)                                // New grant type found
            {
                num_funding_types += 1;                           // Increment total grant count

                string_data_object new_funding;
                // Peer Reviewed or Industry Sponsored?
                if (_data->dtos->at(i).peerReviewed == "True"){
                    new_funding.label = "Peer Reviewed";
                }
                else{
                    new_funding.label = "Industry Grant";
                }
                new_funding.num = 1;                              // 1st of its fundingType found
                new_funding.value = _data->dtos->at(i).totalAmount; //add grant value to the funding type

                vector<string_data_object> empty_child;
                child_set.push_back(empty_child);

                parent_set.push_back(new_funding);

                string_data_object new_auth;                      // Add 1st author of new funding type
                new_auth.label = memberName;
                new_auth.num = 1;                                 // first grant/clinial trial for this grant author
                new_auth.value = _data->dtos->at(i).totalAmount;    // add grant value to this grant author

                int index = find_label_index(PRorIG, parent_set);
                child_set.at(index).push_back(new_auth);            // Add author to specific publication
            }

            else if (grant_value != -1)                                  // If grant type exists, look for potential investigators
            {
                parent_set.at(grant_value).num += 1;                // Add another entry for grants
                int inv_value = find_label_index(memberName, child_set.at(grant_value));    // try to find the index if this investigator already exists

                if (inv_value == -1)                                // Not found: New investigator is encountered
                {
                    string_data_object new_inv;                     // Create new grant investigator
                    new_inv.label = memberName;
                    new_inv.num = 1;                                // firstgrant/clinial trial for this grant investigator
                    new_inv.value = _data->dtos->at(i).totalAmount;  // add grant value to this new grant author
                    child_set.at(grant_value).push_back(new_inv);
                }
                else                                            // investigator is already found, increment their count for grants
                {
                    vector<string_data_object> *tmp = &child_set.at(grant_value);
                    tmp->at(inv_value).num += 1;
                }
            }
        }
    }
    return 0;   // Exited with success.
}

// Angus wrote this - it covers the PME, UME, and CME programs
int tree_list_vo::tree_list_vo::populate_for_teaching(shared_ptr<CSVData<TeachingDTO> > _data, const char* program, int start, int end)
{

    // Create the first empty child set of the tree
    vector<string_data_object> t;
    child_set.push_back(t);

    int start_index = 0;
    
    // Start and end date for teaching
    int start_date = 0;
    int end_date = 0;
    std::string str;

    // Iterate to find the first valid range in the data
    
    while(start_index < _data->dtos->size())
    {
        start_date = _data->dtos->at(start_index).startDate;
        end_date = _data->dtos->at(start_index).endDate;
        str = _data->dtos->at(start_index).program;

        if ((((start <= start_date) && (end >= start_date)) || ((start <= end_date) && (end >= end_date))) && str == program)
        {
            break;          // Found the index of dto where the first legal date range is found
        }

        start_index += 1;
    }

    string_data_object first_sd;

    if(start_index == _data->dtos->size()) {
        first_sd.label = "";          // Add first Faculty
        first_sd.num = 0;                                               // Default is 0 hours
        first_sd.num2 = 0;
        parent_set.push_back(first_sd);
        return 0;
    }

    first_sd.label = _data->dtos->at(start_index).faculty;          // Add first Faculty
    first_sd.num = 0;                                               // Default is 0 hours
    first_sd.num2 = 0;
    child_set.at(0).push_back(first_sd);                            // Add first teaching member's name

    string_data_object first_teach;                                 // Add first teaching type
    first_teach.label = std::to_string(_data->dtos->at(start_index).startDate) + "-" + std::to_string(_data->dtos->at(start_index).endDate);
    first_teach.num = 0;                                            // 0 teachings first
    first_teach.num2 = 0;
    first_teach.value = -1;

    parent_set.push_back(first_teach);                              // 1 Teaching inserted

    // start_index now contains the first DTO we begin at.
    for (int i = start_index; i < _data->dtos->size(); i ++)
    {
        start_date = _data->dtos->at(i).startDate;                  // Get date of starting index
        end_date = _data->dtos->at(i).endDate;
        str = _data->dtos->at(i).program;

        if (((start <= start_date) && (end >= start_date) || (start <= end_date) && (end >= end_date)) && str == program)   // Should pass b/c starting at 1st valid data index
        {
            string memberName = _data->dtos->at(i).faculty;    // Name of the Faculty
            string dateRange = std::to_string(_data->dtos->at(i).startDate) + "-" + std::to_string(_data->dtos->at(i).endDate);   // Faculty name

            int teach_value = find_label_index(dateRange, parent_set);  //find the date range

            if (teach_value == -1)    // New publication type
            {
                num_teach_types += 1;                      // Increment total teaching count

                string_data_object new_teaching;
                new_teaching.label = dateRange;                // Set label of the new teaching type
                new_teaching.num = _data->dtos->at(i).totalHours;                // Set hour amount
                new_teaching.num2 = atof(_data->dtos->at(i).students.c_str()); //Set student amount
                //new_teaching.value = _data->dtos->at(i).totalHours; //add teaching value
                new_teaching.value = -1; //add teaching value
                //std::cout << "Hours: " + std::to_string(new_teaching.num) << endl;

                vector<string_data_object> empty_child;
                child_set.push_back(empty_child);

                parent_set.push_back(new_teaching);

                string_data_object new_auth;        // Add 1st author of new teaching type
                new_auth.label = memberName;
                new_auth.num = _data->dtos->at(i).totalHours;
                new_auth.num2 = atof(_data->dtos->at(i).students.c_str());
                new_auth.value = -1;

                int index = find_label_index(dateRange, parent_set);
                child_set.at(index).push_back(new_auth);    // Add author to specific teaching
            }

            else if (teach_value != -1)    // Teaching type exists, look for potential authors
            {
                parent_set.at(teach_value).num += _data->dtos->at(i).totalHours;      // Add another entry for teachings
                parent_set.at(teach_value).num2 += atof(_data->dtos->at(i).students.c_str());
                int auth_value = find_label_index(memberName, child_set.at(teach_value));

                if (auth_value == -1)   // New author is encountered
                {
                    string_data_object new_auth;    // Create new author
                    new_auth.label = memberName;
                    new_auth.num = _data->dtos->at(i).totalHours;
                    new_auth.num2 = atof(_data->dtos->at(i).students.c_str());
                    new_auth.value = -1;
                    child_set.at(teach_value).push_back(new_auth);
                }
                else        // Author is already found, increment their count for publications
                {
                    vector<string_data_object> *tmp = &child_set.at(teach_value);
                    tmp->at(auth_value).num += _data->dtos->at(i).totalHours;
                    tmp->at(auth_value).num2 += atof(_data->dtos->at(i).students.c_str());
                }
            }
        }
    }
    // Exit success
    return 0;
}

// This function populates the "Other" tree for teaching
// Not entirely sure if it works properly though
int tree_list_vo::tree_list_vo::populate_for_teaching(shared_ptr<CSVData<TeachingDTO> > _data, int start, int end)
{

    // Create the first empty child set of the tree
    vector<string_data_object> t;
    child_set.push_back(t);

    int start_index = 0;

    // Start and end date for teaching
    int start_date = 0;
    int end_date = 0;
    std::string str;

    // Iterate to find the first valid range in the data

    while(start_index < _data->dtos->size())
    {
        start_date = _data->dtos->at(start_index).startDate;
        end_date = _data->dtos->at(start_index).endDate;
        str = _data->dtos->at(start_index).program;

        if ((((start <= start_date) && (end >= start_date)) || ((start <= end_date) && (end >= end_date)))
                && (str != "Postgraduate Medical Education") && (str != "Undergraduate Medical Education")
                && (str != "Continuing Medical Education"))
        {
            break;          // Found the index of dto where the first legal date range is found
        }

        start_index += 1;
    }

    string_data_object first_sd;

    if(start_index == _data->dtos->size()) {
        first_sd.label = "";          // Add first Faculty
        first_sd.num = 0;                                               // Default is 0 hours
        first_sd.num2 = 0;
        parent_set.push_back(first_sd);
        return 0;
    }

    first_sd.label = _data->dtos->at(start_index).faculty;          // Add first Faculty
    first_sd.num = 0;                                               // Default is 0 hours
    first_sd.num2 = 0;
    child_set.at(0).push_back(first_sd);                            // Add first teaching member's name

    string_data_object first_teach;                                 // Add first teaching type
    first_teach.label = std::to_string(_data->dtos->at(start_index).startDate) + "-" + std::to_string(_data->dtos->at(start_index).endDate);
    first_teach.num = 0;                                            // 0 teachings first
    first_teach.num2 = 0;
    first_teach.value = -1;

    parent_set.push_back(first_teach);                              // 1 Teaching inserted

    // start_index now contains the first DTO we begin at.
    for (int i = start_index; i < _data->dtos->size(); i ++)
    {
        start_date = _data->dtos->at(i).startDate;                  // Get date of starting index
        end_date = _data->dtos->at(i).endDate;
        str = _data->dtos->at(i).program;

        if (((start <= start_date) && (end >= start_date) || (start <= end_date) && (end >= end_date))
                && (str != "Postgraduate Medical Education") && (str != "Undergraduate Medical Education")
                && (str != "Continuing Medical Education"))   // Should pass b/c starting at 1st valid data index
        {
            string memberName = _data->dtos->at(i).faculty;    // Name of the Faculty
            string dateRange = std::to_string(_data->dtos->at(i).startDate) + "-" + std::to_string(_data->dtos->at(i).endDate);   // Faculty name

            int teach_value = find_label_index(dateRange, parent_set);  //find the date range

            if (teach_value == -1)    // New publication type
            {
                num_teach_types += 1;                      // Increment total teaching count

                string_data_object new_teaching;
                new_teaching.label = dateRange;                // Set label of the new teaching type
                new_teaching.num = _data->dtos->at(i).totalHours;                // Set hour amount
                new_teaching.num2 = atof(_data->dtos->at(i).students.c_str()); //Set student amount
                //new_teaching.value = _data->dtos->at(i).totalHours; //add teaching value
                new_teaching.value = -1; //add teaching value
                //std::cout << "Hours: " + std::to_string(new_teaching.num) << endl;

                vector<string_data_object> empty_child;
                child_set.push_back(empty_child);

                parent_set.push_back(new_teaching);

                string_data_object new_auth;        // Add 1st author of new teaching type
                new_auth.label = memberName;
                new_auth.num = _data->dtos->at(i).totalHours;
                new_auth.num2 = atof(_data->dtos->at(i).students.c_str());
                new_auth.value = -1;

                int index = find_label_index(dateRange, parent_set);
                child_set.at(index).push_back(new_auth);    // Add author to specific teaching
            }

            else if (teach_value != -1)    // Teaching type exists, look for potential authors
            {
                parent_set.at(teach_value).num += _data->dtos->at(i).totalHours;      // Add another entry for teachings
                parent_set.at(teach_value).num2 += atof(_data->dtos->at(i).students.c_str());
                int auth_value = find_label_index(memberName, child_set.at(teach_value));

                if (auth_value == -1)   // New author is encountered
                {
                    string_data_object new_auth;    // Create new author
                    new_auth.label = memberName;
                    new_auth.num = _data->dtos->at(i).totalHours;
                    new_auth.num2 = atof(_data->dtos->at(i).students.c_str());
                    new_auth.value = -1;
                    child_set.at(teach_value).push_back(new_auth);
                }
                else        // Author is already found, increment their count for publications
                {
                    vector<string_data_object> *tmp = &child_set.at(teach_value);
                    tmp->at(auth_value).num += _data->dtos->at(i).totalHours;
                    tmp->at(auth_value).num2 += atof(_data->dtos->at(i).students.c_str());
                }
            }
        }
    }
    // Exit success
    return 0;
}


// To implement later once DO _data pointer is known
// Jerry will implement
int tree_list_vo::tree_list_vo::populate_for_presentations(shared_ptr<CSVData<PresentationDTO> > _data, int start, int end)
{
    // Invited
    // Lectures
    // Abstracts
    // Presented
    // Next Presentation
    // type
    // Other

    //Mandatory Fields
    //name, domain, type, role, title, date

    cout << "Testing for first user." << endl;
    cout <<"name"<<_data->dtos->at(0).name << endl;
    cout << "domain" << _data->dtos->at(0).domain << endl;
    cout << "type" << _data->dtos->at(0).type << endl;
    cout << "role" << _data->dtos->at(0).role << endl;
    cout << "title" << _data->dtos->at(0).title << endl;
    cout << "date" << _data->dtos->at(0).date << endl;



    // Adding 1st empty child set
    vector<string_data_object> t;
    child_set.push_back(t);

    int start_index = 0;
    int date = 0;
    while(start_index < _data->dtos->size())
    {
        date = _data->dtos->at(start_index).date;

        if ((start <= date) && (end >= date))
        {
            break;
        }
        start_index += 1;
    }

    string_data_object first_sd;
    first_sd.label = _data->dtos->at(start_index).name; // Add presenter's name
    first_sd.num = 0;
    first_sd.value = -1; // No value field for presentations

    child_set.at(0).push_back(first_sd);

    string_data_object first_pres;
    first_pres.label = _data->dtos->at(start_index).type;
    first_pres.num = 0;
    first_pres.value = -1;

    parent_set.push_back(first_pres);

    for (int i = start_index; i < _data->dtos->size(); i ++)
    {
        date = _data->dtos->at(i).date;
        if ((start <= date) && (end >=date))
        {
            string presenter = _data->dtos->at(i).name;
            string subject = _data->dtos->at(i).type;

            int pres_value = find_label_index(subject, parent_set);
            if (pres_value == -1)
            {
                num_pub_types +=1;

                string_data_object new_pres;
                new_pres.label = subject;
                new_pres.num = 1;
                new_pres.value = -1;

                vector <string_data_object> empty_child;
                child_set.push_back(empty_child);

                parent_set.push_back(new_pres);

                string_data_object new_presenter;
                new_presenter.label = presenter;
                new_presenter.num = 1;
                new_presenter.value = -1;

                int index = find_label_index(subject, parent_set);
                child_set.at(index).push_back(new_presenter);
            }

            if (pres_value != -1)
            {
                parent_set.at(pres_value).num += 1; // Add another presenter
                int presenter_value = find_label_index(presenter, child_set.at(pres_value));

                if (presenter_value == -1)      // Add new presenter
                {
                    string_data_object new_presenter;
                    new_presenter.label = presenter;
                    new_presenter.num = 1;
                    new_presenter.value = -1;
                    child_set.at(pres_value).push_back(new_presenter);
                }
                else
                {
                    vector<string_data_object> * tmp = &child_set.at(pres_value);
                    tmp->at(presenter_value).num +=1;
                }
            }
        }
    }
     return 0;
}






// PRIVATE FUNCTIONS FOR USAGE
/**
 * @brief tree_list_vo::find_label_index will return the index of a label stored in
 * the list specified by param set
 * @param label is the label being searched for
 * @param set is the vector that stores string:data objects
 * @return the index at which label is stored if found, -1 otherwise
 */
/*int tree_list_vo::find_label_index(string label, vector<string_data_object> set)
{
    for (int i = 0; i < set.size(); i ++)
    {
        if( (set.at(i).label).compare(label) == 0)
        {
            return i;
        }
    }
    return -1;
}*/
