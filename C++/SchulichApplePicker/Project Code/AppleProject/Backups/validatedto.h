#ifndef VALIDATEDTO_H
#define VALIDATEDTO_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int validatePublication(std::vector<std::string> *fields);
int validateGrant(std::vector<std::string> * fields);
int validateTeaching(std::vector<std::string> * fields);
int validatePresentation(std::vector<std::string> *fields);

#endif // VALIDATEDTO_H
