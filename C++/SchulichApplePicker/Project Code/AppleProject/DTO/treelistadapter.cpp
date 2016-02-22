#include "treelistadapter.h"

#include "CSV-Data/csvtype.h"

using namespace std;

TreeListAdapter::TreeListAdapter(vector<CSVField> *csvline, CSVType t)
{
    if(t == PUBLICATION){
        treePath.push_back(*csvline->at(1).getField()); //Status date
        treePath.push_back(*csvline->at(2).getField()); //Member Name
        treePath.push_back(*csvline->at(5).getField()); //Type
        treePath.push_back(*csvline->at(6).getField()); //Role
        treePath.push_back(*csvline->at(0).getField()); //Line number

        treeValues.push_back(1.0);

    }
    else if(t == GRANTS){
        treePath.push_back(*csvline->at(1).getField()); //Start Date
        treePath.push_back(*csvline->at(3).getField()); //Name
        treePath.push_back(*csvline->at(5).getField()); //Type

        bool peer = (*csvline->at(7).getValue() == "TRUE");
        bool industry = (*csvline->at(8).getValue() == "TRUE");
        if(peer){
            if(!industry) treePath.push_back("Peer Reviewed");
            else treePath.push_back("Peer Reviewed and Industry Sponsored");
        }
        else{
            if(industry) treePath.push_back("Industry Sponsored");
            else treePath.push_back("Other");
        }

        treePath.push_back(*csvline->at(6).getField()); //status
        treePath.push_back(*csvline->at(9).getField()); //Role
        treePath.push_back(*csvline->at(0).getField()); //Line number

        treeValues.push_back(1.0); //Number
        treeValues.push_back(stod(*csvline->at(12).getValue())); //Total Ammount
    }
    else if(t == PRESENTATION){
        treePath.push_back(*csvline->at(1).getField()); //Date
        treePath.push_back(*csvline->at(2).getField()); //Name
        treePath.push_back(*csvline->at(4).getField()); //Type
        treePath.push_back(*csvline->at(5).getField()); //Role
        treePath.push_back(*csvline->at(0).getField()); //Line number

        treeValues.push_back(1.0);
    }
    else{
        treePath.push_back(*csvline->at(1).getField()); //Start Date
        treePath.push_back(*csvline->at(3).getField()); //Name
        treePath.push_back(*csvline->at(5).getField()); //Program

        treeValues.push_back(stod(*csvline->at(10).getValue()));//Hours
        //# Students
        try{
            treeValues.push_back(stod(*csvline->at(11).getValue()));
        }
        catch(invalid_argument){
            treeValues.push_back(0.0);
        }
    }
}

vector<string> *TreeListAdapter::getTreePath()
{
    return &treePath;
}


vector<double> *TreeListAdapter::getTreeValues()
{
    return &treeValues;
}
