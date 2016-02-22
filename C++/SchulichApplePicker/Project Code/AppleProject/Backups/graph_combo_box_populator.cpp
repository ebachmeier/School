#include "graph_combo_box_populator.h"
/*
QStringList populateGraphComboName(std::shared_ptr<CSVData<PublicationDTO>> data) {
    size_t i, j;
    std::vector<string> names;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (names.empty()) {
            names.push_back(data->dtos->at(i).name);
        }
        else {

            // add names only if they aren't already in the list
            bool add = true;
            for (j=0; j < names.size(); j++) {
                if (data->dtos->at(i).name.compare(names.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                names.push_back(data->dtos->at(i).name);
            }
        }
    }

    //sort the lists
    std::sort(names.begin(), names.end());

    //put the dates in a QString vector list
    QStringList combo_names;
    for (i=0; i < names.size(); i++) {
        combo_names << QString::fromStdString(names.at(i));
    }

    return combo_names;
}

QStringList populateGraphComboType(std::shared_ptr<CSVData<PublicationDTO>> data) {
    size_t i, j;
    std::vector<string> types;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (types.empty()) {
            types.push_back(data->dtos->at(i).type);
        }
        else {
            // add types only if they aren't already in the list
            bool add = true;
            for (j=0; j < types.size(); j++) {
                if (data->dtos->at(i).type.compare(types.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                types.push_back(data->dtos->at(i).type);
            }
        }
    }

    //sort the lists
    std::sort(types.begin(), types.end());

    //put the dates in a QString vector list
    QStringList combo_types;
    for (i=0; i < types.size(); i++) {
        combo_types << QString::fromStdString(types.at(i));
    }

    return combo_types;
}

QStringList populateGraphComboName(std::shared_ptr<CSVData<PresentationDTO>> data) {
    size_t i, j;
    std::vector<string> names;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (names.empty()) {
            names.push_back(data->dtos->at(i).name);
        }
        else {

            // add names only if they aren't already in the list
            bool add = true;
            for (j=0; j < names.size(); j++) {
                if (data->dtos->at(i).name.compare(names.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                names.push_back(data->dtos->at(i).name);
            }
        }
    }

    //sort the lists
    std::sort(names.begin(), names.end());

    //put the dates in a QString vector list
    QStringList combo_names;
    for (i=0; i < names.size(); i++) {
        combo_names << QString::fromStdString(names.at(i));
    }

    return combo_names;
}

QStringList populateGraphComboType(std::shared_ptr<CSVData<PresentationDTO>> data) {
    size_t i, j;
    std::vector<string> types;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (types.empty()) {
            types.push_back(data->dtos->at(i).type);
        }
        else {
            // add types only if they aren't already in the list
            bool add = true;
            for (j=0; j < types.size(); j++) {
                if (data->dtos->at(i).type.compare(types.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                types.push_back(data->dtos->at(i).type);
            }
        }
    }

    //sort the lists
    std::sort(types.begin(), types.end());

    //put the dates in a QString vector list
    QStringList combo_types;
    for (i=0; i < types.size(); i++) {
        combo_types << QString::fromStdString(types.at(i));
    }

    return combo_types;
}

QStringList populateGraphComboName(std::shared_ptr<CSVData<GrantDTO>> data) {
    size_t i, j;
    std::vector<string> names;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (names.empty()) {
            names.push_back(data->dtos->at(i).memberName);
        }
        else {

            // add names only if they aren't already in the list
            bool add = true;
            for (j=0; j < names.size(); j++) {
                if (data->dtos->at(i).memberName.compare(names.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                names.push_back(data->dtos->at(i).memberName);
            }
        }
    }

    //sort the lists
    std::sort(names.begin(), names.end());

    //put the dates in a QString vector list
    QStringList combo_names;
    for (i=0; i < names.size(); i++) {
        combo_names << QString::fromStdString(names.at(i));
    }

    return combo_names;
}

QStringList populateGraphComboFunding(std::shared_ptr<CSVData<GrantDTO>> data) {
    size_t i, j;
    std::vector<string> funding_list;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (funding_list.empty()) {
            funding_list.push_back(data->dtos->at(i).fundingType);
        }
        else {
            // add types only if they aren't already in the list
            bool add = true;
            for (j=0; j < funding_list.size(); j++) {
                if (data->dtos->at(i).fundingType.compare(funding_list.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                funding_list.push_back(data->dtos->at(i).fundingType);
            }
        }
    }

    //sort the lists
    std::sort(funding_list.begin(), funding_list.end());

    //put the dates in a QString vector list
    QStringList combo_fundings;
    for (i=0; i < funding_list.size(); i++) {
        combo_fundings << QString::fromStdString(funding_list.at(i));
    }

    return combo_fundings;
}

QStringList populateGraphComboName(std::shared_ptr<CSVData<TeachingDTO>> data) {
    size_t i, j;
    std::vector<string> names;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (names.empty()) {
            names.push_back(data->dtos->at(i).name);
        }
        else {

            // add names only if they aren't already in the list
            bool add = true;
            for (j=0; j < names.size(); j++) {
                if (data->dtos->at(i).name.compare(names.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                names.push_back(data->dtos->at(i).name);
            }
        }
    }

    //sort the lists
    std::sort(names.begin(), names.end());

    //put the dates in a QString vector list
    QStringList combo_names;
    for (i=0; i < names.size(); i++) {
        combo_names << QString::fromStdString(names.at(i));
    }

    return combo_names;
}

QStringList populateGraphComboProgram(std::shared_ptr<CSVData<TeachingDTO>> data) {
    size_t i, j;
    std::vector<string> programs;

    // loop through the names and types from the dto
    for (i=0; i < data->dtos->size(); i++) {
        if (programs.empty()) {
            programs.push_back(data->dtos->at(i).program);
        }
        else {
            // add types only if they aren't already in the list
            bool add = true;
            for (j=0; j < programs.size(); j++) {
                if (data->dtos->at(i).program.compare(programs.at(j)) == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                programs.push_back(data->dtos->at(i).program);
            }
        }
    }

    //sort the lists
    std::sort(programs.begin(), programs.end());

    //put the dates in a QString vector list
    QStringList combo_programs;
    for (i=0; i < programs.size(); i++) {
        combo_programs << QString::fromStdString(programs.at(i));
    }

    return combo_programs;
}
*/
