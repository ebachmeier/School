#include "dtoassembler.h"

void assembleDTO(PublicationDTO *dto, vector<string> f){
    //Mandatory Fields
    dto->date = atoi(f[0].c_str());
    dto->name = f[1];
    dto->domain = f[2];
    dto->status = f[3];
    dto->type = f[4];
    dto->role = f[5];
    dto->journalName = f[6];
    dto->title = f[7];
    
    //Split up the authors list
    stringstream ss(f[8]);
    string item;
    //Split around ,
    while(getline(ss, item, ',')) dto->authors->push_back(item);
    
    
    //Optional Fields
    dto->pubmedID = f[9];
    dto->peerReviewed = f[10];
    dto->authorNumber = f[11];
    dto->volume = f[12];
    dto->issue = f[13];
    dto->pageRange = f[14];
    dto->DOI = f[15];
    dto->website = f[16];
    dto->impactFactor = f[17];
    dto->international = f[18];
    dto->publisher = f[19];
    dto->presentation = f[20];
    dto->personalRenumeration = f[21];
    dto->traineeDetails = f[22];
    dto->mostSignificant = f[23];
    dto->mostSignificantDetails = f[24];
    dto->education = f[25];
    dto->ISBN = f[26];

    dto->treeValues.push_back(1.0);
    dto->treePath.push_back("Publications");
    dto->treePath.push_back(dto->type);
    dto->treePath.push_back(dto->name);


}

void assembleDTO(GrantDTO *dto, vector<string> f){
    // Mandatory Fields (13)
    dto->startDate = atoi(f[0].c_str());
    dto->endDate=atoi(f[1].c_str());
    dto->memberName = f[2];
    dto->domain = f[3];
    dto->fundingType = f[4];
    dto->status = f[5];
    dto->peerReviewed = f[6];
    dto->industryGrant = f[7];
    dto->role = f[8];
    dto->title = f[9];
    dto->pInvestigator = f[10];
    dto->totalAmount = atof(f[11].c_str());

    //Split up the coinvestigator list
    stringstream ss(f[12]);
    string item;
    //Split around ,
    while(getline(ss, item, ',')) dto->cInvestigator->push_back(item);

    // Optional fields (19)
    dto->shortTitle = f[13];
    dto->applicationSummary = f[14];
    dto->grantPurpose = f[15];
    dto->area = f[16];
    dto->grantNum = f[17];
    dto->proratedAmount = atof(f[18].c_str());
    dto->administeredBy = f[19];
    dto->fundingSource = f[20];
    dto->project = f[21];
    dto->currency = f[22];
    dto->receivedAmount = atof(f[23].c_str());
    dto->memberShare = atof(f[24].c_str());
    dto->monetary = f[25];
    dto->rpt = f[26];
    dto->HrPerWk = atof(f[27].c_str());
    dto->personnelPaid = f[28];
    dto->rnw = f[29];
    dto->edGrant = f[30];
    dto->dupReported = f[31];

    dto->treeValues.push_back(1.0);
    dto->treeValues.push_back(dto->totalAmount);

    dto->treePath.push_back("Grants/Clinical Trials");
    dto->treePath.push_back(dto->fundingType);
    bool peer = (dto->peerReviewed == "TRUE");
    bool industry = (dto->industryGrant == "TRUE");

    if(peer){
        if(!industry){
            dto->treePath.push_back("Peer Reviewed");
        }
        else{
            dto->treePath.push_back("Peer Reviewed and Industry Sponsored");
        }
    }
    else{
        if(industry){
            dto->treePath.push_back("Industry Sponsored");
        }
        else{
            dto->treePath.push_back("Other");
        }
    }
    dto->treePath.push_back(dto->memberName);
}

void assembleDTO(PresentationDTO *dto, vector<string> f){

    //Mandatory Fields
    dto->date = atoi(f[0].c_str());
    dto->name = f[1];
    dto->domain = f[2];
    dto->type = f[3];
    dto->role = f[4];
    dto->title = f[5];

    //Optional Fields
    dto->activityType = f[6];
    dto->geoScope = f[7];
    dto->host = f[8];
    dto->country = f[9];
    dto->province = f[10];
    dto->city = f[11];
    dto->attendeeNum = f[12];
    dto->hours = f[13];
    dto->teachScore = f[14];
    dto->presentation = f[15];
    dto->remarks = f[16];

    //Split up the authors list
    stringstream ss(f[17]);
    string item;
    //Split around ,
    while(getline(ss, item, ',')) dto->authorship->push_back(item);

    dto->citation = f[18];
    dto->personalRenumeration = f[19];
}

void assembleDTO(TeachingDTO *dto, vector<string> f) {
    //mandatory:
    dto->name = f[0];
    dto->domain = f[1];
    dto->startDate = atoi(f[2].c_str());
    dto->endDate = atoi(f[3].c_str());
    dto->program = f[4];
    dto->type = f[5];
    dto->scope = f[6];
    dto->hoursSession = atof(f[7].c_str());
    dto->numberSession = atof(f[8].c_str());
    dto->totalHours = atof(f[9].c_str());

    //optional:
    dto->institution = f[10];
    dto->faculty = f[11];
    dto->department = f[12];
    dto->division = f[13];
    dto->location = f[14];
    dto->facultyComments = f[15];
    dto->students = f[16];
    dto->lecture = f[17];
    dto->development = f[18];
    dto->stipend = f[19];
    dto->comment = f[20];

    dto->treeValues.push_back(1.0);
    dto->treeValues.push_back(dto->totalHours);
    dto->treeValues.push_back(0.0);

    dto->treePath.push_back("Teaching");

    if(dto->program == "Postgraduate Medical Education"){
        dto->treePath.push_back("PME");
    }
    else if(dto->program == "Continuing Medical Education"){
        dto->treePath.push_back("CME");
    }
    else if(dto->program == "Undergraduate Medical Education"){
        dto->treePath.push_back("UME");
    }
    else{
        dto->treePath.push_back("Other");
    }

    dto->treePath.push_back(f[2] + "-" + f[3]);
    dto->treePath.push_back(dto->name);

}
