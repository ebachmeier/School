#include "Maintenance.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <stdio.h>

using namespace std;

Maintenance::Maintenance(int ID) {
    id = ID;
}

Maintenance::Maintenance() {
    id = 0;
}

Maintenance::~Maintenance() {
}

int Maintenance::getID() {
    return id;
}
void Maintenance::setID(int newID) {
    id = newID;
}
