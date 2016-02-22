#include "teach_bargraph1_vo.h"

using namespace std;

Teach_BarGraph1_VO::Teach_BarGraph1_VO(std::shared_ptr<CSVData<TeachingDTO> > data, int start, int end)
{
    // Eric/Emily please uncomment when you've implemented TeachingDTO's
    /*
    cout << start << " " << end << endl;
    name = data->dtos->at(0).name;  // Gets original name

    for(int i = 0; i < (int) data->dtos->size(); i++){
        TeachingDTO dto = data->dtos->at(i);
        if(dto.name == name){
            if((start <= dto.date)&&(dto.date <= end)){
                vector<string>::iterator index;
                index = find(teachingTypes.begin(), teachingTypes.end(), dto.type);
                if(index == teachingTypes.end()) teachingTypes.push_back(dto.type);
                index = find(years.begin(), years.end(), to_string(dto.date));
                if(index == years.end()) years.push_back(to_string(dto.date));
            }
        }
    }

    sort(teachingTypes.begin(), teachingTypes.end());
    sort(years.begin(), years.end());

    for(int i = 0; i < (int)teachingTypes.size(); i++){
        vector<int> temp;
        for(int j = 0; j < (int)years.size(); j++){
            temp.push_back(0);
        }
        values.push_back(temp);
    }

    cout << "pass 2" << endl;

    for(int i = 0; i < (int) data->dtos->size(); i++){
        TeachingDTO dto = data->dtos->at(i);
        if(dto.name == name){
            if((start <= dto.date)&&(dto.date <= end)){
                vector<string>::iterator index;
                index = find(teachingTypes.begin(), teachingTypes.end(), dto.type);
                int i = distance(teachingTypes.begin(),index);
                index = find(years.begin(), years.end(), to_string(dto.date));
                int j = distance(years.begin(),index);
                values.at(i).at(j) += 1;
            }
        }
    }
    cout << "pass 3" << endl;
    */

}

