#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QObject>

#include <vector>
#include <string>
#include <algorithm>

#include "Tab-Objects/tabobserver.h"
#include "Tab-Objects/tabsubject.h"
#include "Tab-Objects/dtofilter.h"
#include "Tab-Objects/filtervalue.h"
#include "DTO/filteradapter.h"

enum FilterValueType: unsigned int;
class CSVDTO;

class ComboBox: public QObject, public TabObserver, public TabSubject
{
    Q_OBJECT

    QComboBox *cmbBox;
    FilterValue *valueGetter;
    CSVDTO *dto;
public:
    ComboBox(){}
    ComboBox(QComboBox *cmb, FilterValueType ft, TabSubject *s = 0);
    void update();
    std::vector<std::string> getState();
    void setDTO(CSVDTO *dto);
    void setLast();
private:
    //Returns the list of filtered values from the csv based on the filter values
    void getValues(std::vector<std::string> *fv, std::vector<std::string> *v);
    //Populates the new combo box with the list of values (tries to preseve selection)
    void populateComboBox(std::vector<std::string> *v);
public slots:
    void indexChanged();
};

#endif // YEARCOMBOBOX_H
