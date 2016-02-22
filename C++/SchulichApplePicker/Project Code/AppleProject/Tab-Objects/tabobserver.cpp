#include "tabobserver.h"

TabObserver::TabObserver(TabSubject *s)
{
    subject = s;
    if(this->subject) this->subject->attach(this);
}

TabObserver::~TabObserver(){}
