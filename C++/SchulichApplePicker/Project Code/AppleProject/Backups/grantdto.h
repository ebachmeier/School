#ifndef grantdto_h
#define grantdto_h

#include <string>
#include <vector>
#include <memory>

using namespace std;

class GrantDTO{
public:

    //Mandatory Fields
    string memberName, domain, fundingType, status, role, title, pInvestigator;
    
    unsigned int startDate, endDate;
    
    float totalAmount;

    shared_ptr<vector<string>> cInvestigator;
    

    //Optional Fields
    string shortTitle, applicationSummary, grantPurpose, area, grantNum, administeredBy, fundingSource, project, currency, personnelPaid;

    float proratedAmount, receivedAmount, memberShare, HrPerWk;

    std::vector<std::string> treePath;
    std::vector<double> treeValues;

    //These might not be numbers or bool??
    string peerReviewed, industryGrant, monetary, rpt, rnw, edGrant, dupReported;
    GrantDTO();
    ~GrantDTO();

    std::string getName();
    std::string getBarField1(int btype = 1);
    std::string getBarField2(int btype = 1);
    double getBarValue(int btype = 1);

    std::vector<std::string> getTreePath(int btype = 1);
    std::vector<double> getTreeValues(int btype = 1);
    int getYear(int btype = 1);
};

#endif // PUBLICATIONDTO

