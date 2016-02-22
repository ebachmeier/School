#ifndef TABSUBJECT
#define TABSUBJECT

/* Subject class interface for object in each tab
 */

#include "Tab-Objects/tabobserver.h"

#include <vector>
#include <string>

class TabSubject{
protected:
    std::vector<class TabObserver *> observers;
    std::vector<std::string> state;
public:
    virtual ~TabSubject();
    void attach(TabObserver *o);
    void notify();

    virtual std::vector<std::string> getState();
};

#endif // TABSUBJECT

