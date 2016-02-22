#ifndef TREELIST_H
#define TREELIST_H

#include <string>
#include <vector>
#include <QObject>

#include "Tab-Objects/tabobserver.h"

#define NCOL 3

class TabSubject;
class QTreeWidget;
class CSVDTO;
class TreeListAdapter;
class QTreeWidgetItem;
class QStringList;

//Node class for tree data
struct TreeListNode
{
public:
    std::string label;
    std::vector<double> values;
    std::vector<TreeListNode> children;
};

class TreeList:public QObject, public TabObserver
{
    Q_OBJECT

    QTreeWidget *tree;
    CSVDTO *dto;
    TreeListNode root;

    void addBranch(TreeListNode *root, TreeListAdapter *dto, size_t depth );
    void makeTreeList();
    void makeList(TreeListNode *node, QTreeWidgetItem *listNode);
    QStringList getStringList(TreeListNode *node);
    QTreeWidgetItem *getHeader(std::vector<std::string> *fv);
    std::string makeRootHeader(std::vector<std::string> *fv);
    void alignColumn(QTreeWidgetItem *tw);

public:
    TreeList(QTreeWidget *t, TabSubject *s);
    void update();
    void setDTO(CSVDTO *dto);
public slots:
    void onResize();
};

#endif // TREELIST_H
