#ifndef DTOASSEMBLER_H
#define DTOASSEMBLER_H

#include "publicationdto.h"
#include "presentationdto.h"
#include "grantdto.h"
#include "teachingdto.h"
#include <sstream>
#include <sstream>



void assembleDTO(PublicationDTO *dto, vector<string> f);
void assembleDTO(PresentationDTO *dto, vector<string> f);
void assembleDTO(TeachingDTO *dto, vector<string> f);   // Eric + Emily add
void assembleDTO(GrantDTO *dto, vector<string> f);   // Jaisen + Jennifer add ==> added by JX 11.14.15


#endif // DTOASSEMBLER_H
