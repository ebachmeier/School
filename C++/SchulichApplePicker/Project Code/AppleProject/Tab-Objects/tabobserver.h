#ifndef TABOBSERVER_H
#define TABOBSERVER_H

/* Observer class interface for objects in each tab
 */

#include "Tab-Objects/tabsubject.h"

class TabSubject;

class TabObserver
{
protected:
    TabSubject *subject;
public:
    TabObserver(TabSubject *s = 0);
    virtual ~TabObserver();
    virtual void update() = 0;
};

#endif // TABOBSERVER_H
