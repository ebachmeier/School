#include "tabsubject.h"

using namespace std;

void TabSubject::attach(TabObserver *o)
{
    observers.push_back(o);
}

void TabSubject::notify(){
    for(size_t i = 0; i < observers.size(); i++){
        observers.at(i)->update();
    }
}

vector<string> TabSubject::getState(){
    return state;
}

TabSubject::~TabSubject(){}
