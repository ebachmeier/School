#include "grantdto.h"

GrantDTO::GrantDTO(){
    
    // Mandatory fields
    memberName = domain = fundingType = status = role = title = pInvestigator = "";

    startDate=endDate=0;
    
    totalAmount=0;

    cInvestigator = shared_ptr<vector<string>>(new vector<string>);

    //Optional fields
    shortTitle = applicationSummary = grantPurpose = area = grantNum = administeredBy = fundingSource, project = currency = personnelPaid = "";
    
    proratedAmount = receivedAmount = memberShare = HrPerWk = 0;

    // bools or string?
    peerReviewed = industryGrant = monetary = rpt = rnw = edGrant = dupReported = "";

}

GrantDTO::~GrantDTO(){

    cInvestigator.reset();
}

std::string GrantDTO::getName(){
    return memberName;
}

std::string GrantDTO::getBarField1(int btype){
    return to_string(endDate);
}

std::string GrantDTO::getBarField2(int btype){
    return fundingType;
}

double GrantDTO::getBarValue(int btype){
    if(status == "Funded") return totalAmount;
    return 0.0;
}

int GrantDTO::getYear(int btype){
    return endDate;
}

std::vector<std::string> GrantDTO::getTreePath(int btype){
    return treePath;
}

std::vector<double> GrantDTO::getTreeValues(int btype){
    return treeValues;
}
