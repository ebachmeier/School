#include "grant_bargraph1_vo.h"

using namespace std;

/*
 * Note I use a two pass system here, you can do it in one pass if you wish, though you will
 * likely have to deal with sorting both lists will keeping the 2d array in a consistant ordering
 */
Grant_BarGraph1_VO::Grant_BarGraph1_VO(std::shared_ptr<CSVData<GrantDTO> > data, int start, int end)
{
    cout << start << " " << end << endl;
    name = data->dtos->at(0).memberName;// Gets original name

    // Loop though the DTOs
    for(int i = 0; i < (int) data->dtos->size(); i++){
        GrantDTO dto = data->dtos->at(i);

        if(dto.memberName == name){
              if((start <= dto.endDate)&&(dto.endDate <= end)){
                vector<string>::iterator index;
                index = find(grantTypes.begin(), grantTypes.end(), dto.fundingType);

                if(index == grantTypes.end()) grantTypes.push_back(dto.fundingType);

                index = find(years.begin(), years.end(), to_string(dto.endDate));

                if(index == years.end()) years.push_back(to_string(dto.endDate));
                }
            }
        }


    sort(grantTypes.begin(), grantTypes.end());
    sort(years.begin(), years.end());

    for(int i = 0; i < (int)grantTypes.size(); i++){
        vector<int> temp;
        for(int j = 0; j < (int)years.size(); j++){
            temp.push_back(0);
        }
        values.push_back(temp);
    }

    cout << "pass 2" << endl;

    for(int i = 0; i < (int) data->dtos->size(); i++){
        GrantDTO dto = data->dtos->at(i);


        if(dto.memberName == name){
             if((start <= dto.endDate)&&(dto.endDate <= end)){
                vector<string>::iterator index;
                index = find(grantTypes.begin(), grantTypes.end(), dto.fundingType);
                int i = distance(grantTypes.begin(),index);
                index = find(years.begin(), years.end(), to_string(dto.endDate));
              // same here
                int j = distance(years.begin(),index);
                values.at(i).at(j) += 1;
            }
        }
    }
    cout << "pass 3" << endl;
}
