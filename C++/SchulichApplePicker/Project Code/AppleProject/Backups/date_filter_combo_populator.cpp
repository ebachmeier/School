#include "date_filter_combo_populator.h"
/*
// JX --> implemented 11.15.15
QStringList PopulateDateCombos(std::shared_ptr<CSVData<GrantDTO>> data) {
    std::vector<int> dates;

    // loop through the dtos to get a list of dates
    for (size_t i=0; i < data->dtos->size(); i++) {
        // loop again to see if the current date is already in the list
        if (dates.empty()) {
            dates.push_back((int)data->dtos->at(i).startDate);      // add the start and end dates to the date list
            dates.push_back((int)data->dtos->at(i).endDate);
        }else {
            bool add_start = true;
            bool add_end = true;

            for (size_t j=0; j < dates.size(); j++) {

                // if the start date already exists in the list of dates
                if ((int)data->dtos->at(i).startDate == dates.at(j)) {
                    add_start = false;
                    break;
                }
            }

            for (size_t k=0; k<dates.size(); k++){

                // if the end date already exists in the list of dates
                if ((int)data->dtos->at(i).endDate == dates.at(k)) {
                    add_end = false;
                    break;
                }

            }
            if (add_start) {
                dates.push_back((int)data->dtos->at(i).startDate);
            }
            if (add_end) {
                dates.push_back((int)data->dtos->at(i).endDate);
            }
        }
    }

    //sort the dates
    std::sort(dates.begin(), dates.end());

    //put the dates in a QString vector list
    QStringList date_strs;
    for (size_t i=0; i < dates.size(); i++)
    {

        ostringstream stream;
        stream << dates.at(i);
        string datestr = stream.str();
        date_strs << QString::fromStdString(datestr);
    }

    return date_strs;

}

QStringList PopulateDateCombos(std::shared_ptr<CSVData<TeachingDTO>> data) {
    std::vector<string> dates;

    // Loop through DTOs to get list of the dates in them
    for (size_t i = 0; i < data->dtos->size(); i ++)
    {
        string date = to_string(data->dtos->at(i).endDate);
        vector<string>::iterator index;
        index = std::find(dates.begin(), dates.end(), date);
        if(index == dates.end()) dates.push_back(date);
    }
    std::sort(dates.begin(), dates.end());  // Sort the date list
    QStringList date_strs;        // Add dates to a qstringlist for qcombobox

    for (size_t i = 0; i < dates.size(); i ++)
    {
        date_strs << QString::fromStdString(dates.at(i));
    }

    return date_strs;
}

// Jerry will implement this later
QStringList PopulateDateCombos(std::shared_ptr<CSVData<PresentationDTO>> data) {
    std::vector<int> dates;

    // Loop through DTOs to get list of the dates in them
    for (size_t i = 0; i < data->dtos->size(); i++)
    {
        if(dates.empty())
        {
            dates.push_back((int)data->dtos->at(i).date);   // Add the first date
        }
        else
        {
            bool add = true;    // Assume new date encountered is novel
            for (int j = 0; j < dates.size(); j++)
            {
                if ((int)data->dtos->at(i).date==dates.at(j))   // check to prevent duplicate dates
                {
                    add = false;
                    break;
                }
            }
            if (add)    // New date encountered, add it to the list
            {
                dates.push_back((int)data->dtos->at(i).date);
            }
        }
    }
    std::sort(dates.begin(), dates.end());  // Sort the date list
    QStringList date_strs;                          // Add dates to a qstringlist for qcombobox

    for (size_t i = 0; i < dates.size(); i ++)
    {
        ostringstream stream;
        stream << dates.at(i);
        string datestr = stream.str();
        date_strs << QString::fromStdString(datestr);
    }

    return date_strs;
}

// Use this to model the other 3 PopulateDateCombos functions
// Remember the DTOs you wrote (Presentations/Teaching/Grants) may/may not have the .date fields
QStringList PopulateDateCombos(std::shared_ptr<CSVData<PublicationDTO>> data) {
    std::vector<int> dates;

    // loop through the dtos to get a list of dates
    for (size_t i=0; i < data->dtos->size(); i++) {
        // loop again to see if the current date is already in the list
        if (dates.empty()) {
            dates.push_back((int)data->dtos->at(i).date);
        }else {
            bool add = true;
            for (int j=0; j < dates.size(); j++) {
                // if it isn't add it to the list
                if ((int)data->dtos->at(i).date == dates.at(j)) {
                    add = false;
                    break;
                }
            }
            if (add) {
                dates.push_back((int)data->dtos->at(i).date);
            }
        }
    }

    //sort the dates
    std::sort(dates.begin(), dates.end());

    //put the dates in a QString vector list
    QStringList date_strs;
    for (size_t i=0; i < dates.size(); i++)
    {

        ostringstream stream;
        stream << dates.at(i);
        string datestr = stream.str();
        date_strs << QString::fromStdString(datestr);
    }

    return date_strs;
}
*/
