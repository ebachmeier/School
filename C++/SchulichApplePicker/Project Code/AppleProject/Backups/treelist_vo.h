#ifndef TREELIST_VO_H
#define TREELIST_VO_H
/*
#include <QTreeWidgetItem>

#include <string>
#include <vector>
#include <memory>


struct TreeList_Node
{
public:
    std::string label;
    std::vector<double> values;
    std::vector<TreeList_Node> children;
};

template <class DTOType>
class TreeList_VO
{
    void addbranch(TreeList_Node *node, DTOType dto, std::size_t depth);
    template <class QType> void makeQTreeNode(QType *parent, TreeList_Node node);
public:
    std::size_t nCol;
    TreeList_Node root;
    TreeList_VO();
    TreeList_VO(std::shared_ptr<CSVData<DTOType>> data,
                               int start, int end, int type = 1);
    bool makeQTree(QTreeWidget *tree);
    bool isEmpty();
};

//Build the tree list VO
template <class DTOType>
TreeList_VO<DTOType>::TreeList_VO(std::shared_ptr<CSVData<DTOType>> data, int start, int end, int type){
    if(data->dtos->size() == 0) return;

    for(std::size_t i = 0; i < data->dtos->at(0).getTreeValues().size(); i++)
        root.values.push_back(0.0);

    //Loop through all the DTOs
    for(std::size_t i = 0; i < data->dtos->size(); i++){

        //Get the DTO
        DTOType dto = data->dtos->at(i);

        //If the dto is in the correct range;
        int year = dto.getYear(type);
        if((start <= year)&&(year <= end))
            addbranch(&root, dto, 0);

    }

    //Number of columns is the number of tracked values + 1
    nCol = root.values.size() + 1;
}

//Recursively add the path from root to leaf to the tree
template <class DTOType>
void TreeList_VO<DTOType>::
addbranch(TreeList_Node *node, DTOType dto, std::size_t depth){


    //Check if the parent has a label
    std::string label = dto.getTreePath().at(depth);
    if(node->label == "") node->label = label;

    //Update the node values
    for(std::size_t i = 0; i < dto.getTreeValues().size(); i++)
        node->values.at(i) += (dto.getTreeValues().at(i));

    //Check if we are at a leaf
    if( (depth + 1) == dto.getTreePath().size()) return;

    std::string nextLabel = dto.getTreePath().at(depth + 1);

    TreeList_Node *child;
    std::size_t index;
    //Check to see if a child with that label already exist.
    for(index = 0; index < (*node).children.size(); index++)
        if(nextLabel == (*node).children.at(index).label) break;


    //If the child exists use that
    if(index < (*node).children.size()) child = &(node->children.at(index));
    //Otherwise create a new child with that label
    else{
        child = new TreeList_Node;
        for(std::size_t i = 0; i < dto.getTreeValues().size(); i++)
            child->values.push_back(0.0);
    }
    addbranch(child, dto, depth + 1);
    if(index >= node->children.size()){
        node->children.push_back(*child);
    }
}

//Recusively makes a QTree from the TreeList VO
template <class DTOType>
template <class QType>
void TreeList_VO<DTOType>::makeQTreeNode(QType *parent, TreeList_Node node){

    QStringList value_list;

    //Add the values to the tree
    value_list << QString::fromStdString(node.label);
    for(size_t i = 0; i < node.values.size(); i++)
       value_list << QString::fromStdString(std::to_string((unsigned long long)node.values.at(i)));

    QTreeWidgetItem *child = new QTreeWidgetItem(parent, value_list);

    //Add all the children
    for(size_t i = 0; i < node.children.size(); i++){
        makeQTreeNode(child, node.children.at(i));
    }
}

//Build the tree list from the tree list vo
template <class DTOType>
bool TreeList_VO<DTOType>::makeQTree(QTreeWidget *tree){
    //If root is empty no valid DTOs were found
    if(root.children.size() == 0) return false;

    makeQTreeNode(tree, root);

    return true;
}

template <class DTOType>
bool TreeList_VO<DTOType>::isEmpty(){
    return (root.children.size() == 0);
}
*/
#endif // TREELIST_VO_H

