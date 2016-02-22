#ifndef BARGRAPH_H
#define BARGRAPH_H
/*
#include <qcustomplot.h>

#include <string>
#include <memory>
#include <vector>

template <class DTOType> class BarGraph_VO
{
public:
    std::string name;
    double maxY = 0.0;
    QVector<QString> yearLabel;
    QVector<double> yearTick;
    QVector<QString> field2;
    QVector<QVector<double>> values;
    BarGraph_VO();
    BarGraph_VO(std::shared_ptr<CSVData<DTOType> > data, string name, string start = "0", string end = "3000", int type = 1);
    BarGraph_VO(std::shared_ptr<CSVData<DTOType> > data, string name, string dtype, string start = "0", string end = "3000", int type = 1);
};
//type_combo_pub
//name_combo_pub

template <class DTOType>
BarGraph_VO<DTOType>::BarGraph_VO(std::shared_ptr<CSVData<DTOType>> data,
                                                           string fname, string start, string end, int type){

    name = fname;

    //Loop through all the dtos
    int n = (int) data->dtos->size();
    for(int i = 0; i < n; i++){

        DTOType dto = data->dtos->at(i);

        //Check if this dto is for the faculity memeber we are graphing
        if(dto.getName() == name){

            //Make sure the date is in the correct range
            string date = dto.getBarField1(type);

            if((start <= date)&&(date <= end)){
                QString qdate = QString::fromStdString(date);
                QString f2 = QString::fromStdString(dto.getBarField2(type));

                QVector<QString>::iterator index;
                //Check to see if the field is already in the list of all fields for this faculty memebr
                index = find(field2.begin(), field2.end(), f2);
                //If not add it to the list
                if(index == field2.end()) field2.push_back(f2);
                //Check to see if the current year is already in the list of all the years the fauculty member has been active
                index = find(yearLabel.begin(), yearLabel.end(), qdate);
                //If not add it to the list.
                if(index == yearLabel.end()) yearLabel.push_back(qdate);
            }
        }
    }

    //Sort both list so that years are in order and publication types are consistant in their ordering from graph to graph
    sort(yearLabel.begin(), yearLabel.end());
    sort(field2.begin(), field2.end());

    //Initialize a 2d array of (types x years)
    std::vector<std::vector<double>> tempV;
    for(int i = 0; i < (int)field2.size(); i++){
        std::vector<double> temp;
        for(int j = 0; j < (int)yearLabel.size(); j++){
            temp.push_back(0.0);
        }
        tempV.push_back(temp);
    }

    //Loop though all the dtos again
    for(int i = 0; i < n; i++){
        DTOType dto = data->dtos->at(i);
        //Check if this dto is for the faculity memeber we are graphing
        if(dto.getName() == name){
            string date = dto.getBarField1(type);
            //Make sure the date is in the correct range
            if((start <= date)&&(date <= end)){
                QString qdate = QString::fromStdString(date);
                QString f2 = QString::fromStdString(dto.getBarField2(type));

                QVector<QString>::iterator index;
                //Get the index of the publication in the publication type array
                index = find(field2.begin(), field2.end(), f2);
                int i = distance(field2.begin(),index);
                //Get the index of the year in the year array
                index = find(yearLabel.begin(), yearLabel.end(), qdate);
                int j = distance(yearLabel.begin(),index);
                //increment the value at (i,j)
                tempV.at(i).at(j) += dto.getBarValue(type);
            }
        }
    }

    //Set the values for the Qvector of doubles (it's constant so can't do it previously)
    for (int i = 0; i < (int)field2.size(); i ++)
    {
        vector<double> y_add = tempV.at(i);

        QVector<double> temp;
        for (int j = 0; j < yearLabel.size(); j ++)
        {
            temp.push_back(y_add.at(j));
        }
        values.push_back(temp);
    }

    //Set the ticks for the x axis and find the max value
    for(int i = 0; i < (int) yearLabel.size(); i++){
        yearTick.push_back(2*(i) + 1);
        for(int j = 0; j < (int)field2.size(); j++){
            if(values.at(j).at(i) > maxY)
                maxY = values.at(j).at(i);
        }
    }
}

template <class DTOType> BarGraph_VO<DTOType>::BarGraph_VO(std::shared_ptr<CSVData<DTOType>> data,
                                                           string fname, string dtype, string start, string end, int type){

    name = fname;
    field2.push_back(QString::fromStdString(dtype));
    //Loop through all the dtos
    int n = (int) data->dtos->size();
    for(int i = 0; i < n; i++){

        DTOType dto = data->dtos->at(i);

        string test_name = dto.getName();
        string test_type = dto.getBarField2(type);

        //Check if this dto is for the faculity memeber we are graphing
        if((dto.getName().compare( name) == 0)&&(dto.getBarField2(type).compare(dtype) ==0)){


            //Make sure the date is in the correct range
            string date = dto.getBarField1(type);

            if((start <= date)&&(date <= end)){
                QString qdate = QString::fromStdString(date);

                QVector<QString>::iterator index;
                //Check to see if the current year is already in the list of all the years the fauculty member has been active
                index = find(yearLabel.begin(), yearLabel.end(), qdate);
                //If not add it to the list.
                if(index == yearLabel.end()) yearLabel.push_back(qdate);
            }
        }
    }

    //Sort both list so that years are in order and publication types are consistant in their ordering from graph to graph
    sort(yearLabel.begin(), yearLabel.end());

    //Initialize a 2d array of (types x years)
    std::vector<std::vector<double>> tempV;
    for(int i = 0; i < (int)field2.size(); i++){
        std::vector<double> temp;
        for(int j = 0; j < (int)yearLabel.size(); j++){
            temp.push_back(0.0);
        }
        tempV.push_back(temp);
    }

    //Loop though all the dtos again
    for(int i = 0; i < n; i++){
        DTOType dto = data->dtos->at(i);
        //Check if this dto is for the faculity memeber we are graphing
        if(dto.getName() == name){
            string date = dto.getBarField1(type);
            //Make sure the date is in the correct range
            if((dto.getName() == name)&&(dto.getBarField2(type) == dtype)){

                if((start <= date)&&(date <= end)){
                    QString qdate = QString::fromStdString(date);

                    QVector<QString>::iterator index;
                    //Get the index of the year in the year array
                    index = find(yearLabel.begin(), yearLabel.end(), qdate);
                    int j = distance(yearLabel.begin(),index);
                    //increment the value at (i,j)
                    tempV.at(0).at(j) += dto.getBarValue(type);
                }
            }
        }
    }

    //Set the values for the Qvector of doubles (it's constant so can't do it previously)
    for (int i = 0; i < (int)field2.size(); i ++)
    {
        vector<double> y_add = tempV.at(i);

        QVector<double> temp;
        for (int j = 0; j < yearLabel.size(); j ++)
        {
            temp.push_back(y_add.at(j));
        }
        values.push_back(temp);
    }

    //Set the ticks for the x axis and find the max value
    for(int i = 0; i < (int) yearLabel.size(); i++){
        yearTick.push_back(2*(i) + 1);
        for(int j = 0; j < (int)field2.size(); j++){
            if(values.at(j).at(i) > maxY)
                maxY = values.at(j).at(i);
        }
    }
}

template <class DTOType> BarGraph_VO<DTOType>::BarGraph_VO(){}
*/
#endif // BARGRAPH_H
