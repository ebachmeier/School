#include "treelist.h"

#include <QString>
#include <QTreeWidgetItem>

#include "Tab-Objects/tabsubject.h"
#include "DTO/csvdto.h"
#include "Tab-Objects/dtofilter.h"
#include "utility/stringfunctions.h"

using namespace std;

TreeList::TreeList(QTreeWidget *t, TabSubject *s):
    TabObserver(s)
{
    tree = t;

    connect(tree, SIGNAL(collapsed(QModelIndex)),
            this, SLOT(onResize()));
    connect(tree, SIGNAL(expanded(QModelIndex)),
            this, SLOT(onResize()));
}

void TreeList::setDTO(CSVDTO *dto){
    this->dto = dto;
}

void TreeList::update(){    
    vector<string> filterValues = subject->getState();
    DTOFilter filter(&filterValues);
    vector<FilterAdapter> *fdtos = dto->getFilterDTOs();
    vector<TreeListAdapter> *tldtos = dto->getTreeListDTOs();

    QTreeWidgetItem *header = getHeader(&filterValues);
    tree->setHeaderItem(header);

    root.label = "";

    //Initialize the value array for the root vector.
    for(size_t i = 0; i < tldtos->at(0).getTreeValues()->size(); ++i){
        root.values.push_back(0.0);
    }

    //Filter dtos and add valid ones to the tree
    for(size_t i = 0; i < fdtos->size(); ++i){
        if(filter.filter(&fdtos->at(i))){
            addBranch(&root, &tldtos->at(i), 0);
        }
    }

    makeTreeList();

    root.children.clear();
    root.values.clear();
}

void TreeList::makeTreeList(){
    tree->clear();

    QTreeWidgetItem *listroot = new QTreeWidgetItem(tree, getStringList(&root));
    alignColumn(listroot);
    makeList(&root, listroot);

    tree->expandItem(tree->topLevelItem(0));
    for(size_t i = 0; i < NCOL; i++){
        tree->resizeColumnToContents(i);
    }
}

void TreeList::makeList(TreeListNode *node, QTreeWidgetItem *listNode){
    vector<TreeListNode> *children = &node->children;
    if(children->size() == 0) return;

    for(size_t i = 0; i < children->size(); ++i){
        TreeListNode *child = &children->at(i);
        QTreeWidgetItem *listChild =
                new QTreeWidgetItem(listNode, getStringList(child));
        alignColumn(listChild);
        makeList(child, listChild);
    }
}

QStringList TreeList::getStringList(TreeListNode *node){
    QStringList valueList;
    valueList << QString::fromStdString(node->label);

    vector<double> *values = &node->values;
    size_t i;
    for(i = 0; i < values->size(); ++i){
        string value = "  " + formatNumber(values->at(i));
        valueList << QString::fromStdString(value);
    }

    for(;i < NCOL; ++i){
        valueList << "";
    }

    return valueList;
}

void TreeList::addBranch(TreeListNode *root, TreeListAdapter *dto, size_t depth ){
    vector<string> *labels = dto->getTreePath();
    vector<double> *values = dto->getTreeValues();

    //And the values for this branch to the current root
    for(size_t i = 0; i < values->size(); ++i){
        root->values.at(i) += values->at(i);
    }

    //If we are at a leaf node return
    if(depth == labels->size() ) return;

    string label = labels->at(depth);

    //Check to see if a child exists with this label
    vector<TreeListNode> *children = &root->children;
    TreeListNode *child;
    size_t k = 0;
    for(;k < root->children.size(); ++k){
        child = &children->at(k);
        if(label == child->label) break;
    }

    //If a child is not found make a new one
    if(k == children->size()){
        TreeListNode newChild;
        newChild.label = label;
        for(size_t i = 0; i < values->size(); ++i){
            newChild.values.push_back(0.0);
        }
        children->push_back(newChild);
        child = &children->at(k);
    }

    //Add the rest of the branch recusively
    addBranch(child, dto, depth + 1);
}

QTreeWidgetItem *TreeList::getHeader(vector<string> *fv){
    QStringList result;
    result << QString::fromStdString(makeRootHeader(fv));
    switch(dto->getType()){
        case 0:
            result << "\n\n\n\nTotal" << "" << "";
            break;
        case 1:
            result << "\n\n\n\nTotal #" << "\n\n\n\nTotal $" << "";
            break;
        case 2:
            result << "\n\n\n\n# of Presentations" << "" << "";
            break;
        case 3:
            result << "\n\n\n\nHours" << "\n\n\n\nStudents" << "";
            break;
    }

    QTreeWidgetItem *twResult = new QTreeWidgetItem(result);
    alignColumn(twResult);
    return twResult;
}

void TreeList::alignColumn(QTreeWidgetItem *tw){
    for(size_t i = 1; i < NCOL; ++i){
        tw->setTextAlignment(i, Qt::AlignRight);
    }
}

string TreeList::makeRootHeader(vector<string> *fv){
    string result = "";
    switch(dto->getType()){
        case 0:
            result = "Publication Summary                ";
            break;
        case 1:
            result = "Grants and Clinical Funding Summary";
            break;
        case 2:
            result = "Teaching Summary                   ";
            break;
        case 3:
            result = "Presentaion Summary                ";
            break;
    }

    result += "\nDepartment of ";
    result += *dto->getDomain();
    result += "\nDate Range Selected:\n";
    result += fv->at(0);
    result += "-Jan     ";
    result += fv->at(1);
    result += "-Dec\n";

    return result;
}

void TreeList::onResize(){
    tree->resizeColumnToContents(0);
}
