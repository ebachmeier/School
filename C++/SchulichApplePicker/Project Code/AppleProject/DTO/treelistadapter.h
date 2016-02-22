#ifndef TREELISTADAPTER_H
#define TREELISTADAPTER_H

/* An adaptor that transforms a csv line into a form that we can
 * easily create the tree list from. This contains a tree path
 * which represents the path we would take from the node of the
 * tree to a child. (each line represents it's own child).
 *
 * The path is built from the tier list that the customer provided us with.
 *
 * The tree values are the values to be tracked at that node of the tree.
 * (usually 1, for each entry, but may be $ for grants, etc)
 */

#include <vector>
#include <string>

#include "CSV-Data/csvfield.h"
#include "DTO/csvdto.h" //CSVType

enum CSVType: unsigned int;

class TreeListAdapter
{
    std::vector<std::string> treePath;
    std::vector<double> treeValues;
public:
    TreeListAdapter(std::vector<CSVField> *csvline, CSVType t);
    std::vector<std::string> *getTreePath();
    std::vector<double> *getTreeValues();
};

#endif // TREELISTADAPTER_H
