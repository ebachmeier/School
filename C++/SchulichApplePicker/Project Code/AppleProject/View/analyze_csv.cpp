#include "View/analyze_csv.h"
#include "View/ui_analyze_csv.h"

#include "DTO/data.h"
#include "DTO/csvdto.h"
#include "View/load_csv.h"
#include "Tab-Objects/combobox.h"
#include "Tab-Objects/bargraph.h"
#include "Tab-Objects/qcustomplot.h"
#include "Tab-Objects/treelist.h"
#include "CSV-Data/csvtype.h"

using namespace std;

AnalyzeCSV::AnalyzeCSV(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AnalyzeCSV)
{
    ui->setupUi(this);
    ui->verify_btn->setDisabled(true);

    data = Data::Instance();

    for(size_t i = 0; i < NTAB; ++i){
        ui->tab_widget->setTabEnabled(i, false);

        QComboBox *startY = getCmbStartYear(i);
        QComboBox *endY = getCmbEndYear(i);
        QComboBox *name = getCmbName(i);
        QComboBox *type = getCmbType(i);
        QGraphicsView *bar = getBarGraph(i);
        QTreeWidget *tree = getTreeList(i);
        QPushButton *btn =  getBtnExportGraph(i)  ;

        ComboBox *sy = new ComboBox(startY, FILTERYEAR);
        ComboBox *ey = new ComboBox(endY, FILTERYEAR, sy);
        ComboBox *n = new ComboBox(name, FILTERNAME, ey);
        ComboBox *ty = new ComboBox(type, FILTERTYPE, n);        

        vector<ComboBox *> boxes;
        boxes.push_back(sy);
        boxes.push_back(ey);
        boxes.push_back(n);
        boxes.push_back(ty);
        cmbBoxes.push_back(boxes);

        BarGraph *b = new BarGraph(bar, this, ty, btn);
        barGraphs.push_back(b);

        TreeList *t = new TreeList(tree, ey);
        treeLists.push_back(t);

        connect(ui->tab_widget, SIGNAL(currentChanged(int)), b, SLOT(onResize()));
    }
}

void AnalyzeCSV::loadTab(size_t i){
    ui->analyze_btn->setEnabled(true);
    ui->tab_widget->setTabEnabled(i, true);

    CSVDTO *dto = data->getDTO(i);
    getLblDomain(i)->setText(QString::fromStdString(*dto->getDomain()));

    vector<ComboBox *> *boxes = &cmbBoxes.at(i);
    for(size_t j = 0; j < boxes->size(); ++j){
        ComboBox *box = boxes->at(j);
        box->setDTO(dto);
    }
    BarGraph *bar = barGraphs.at(i);
    bar->setDTO(dto);

    TreeList *tree = treeLists.at(i);
    tree->setDTO(dto);

    ComboBox *box = boxes->at(0);
    box->update();

    box = boxes->at(1);
    box->setLast();
    box->update();

    ui->tab_widget->setCurrentIndex(i);
}

void AnalyzeCSV::doneloading(){
    emit resizeEvent(0);
}

AnalyzeCSV::~AnalyzeCSV()
{
    for(size_t i = 0; i < cmbBoxes.size(); ++i){
        vector<ComboBox *> boxes = cmbBoxes.at(i);
        for(size_t j = 0; j < NTAB; ++j){
            delete boxes.at(j);
        }
    }
    for(size_t i = 0; i < barGraphs.size(); ++i){
        delete barGraphs[i];
    }
    for(size_t i = 0; i < treeLists.size(); ++i){
        delete treeLists[i];
    }

    delete ui;
}

void AnalyzeCSV::on_load_btn_clicked()
{
    emit gotoLoad();
}

QPushButton *AnalyzeCSV::getBtnExportGraph(std::size_t i){
    switch(i){
    case(0): return ui->btnExportGraphPub;
    case(1): return ui->btnExportGraphGrant;
    case(2): return ui->btnExportGraphPres;
    case(3): return ui->btnExportGraphTeach;
    }
    return 0;
}

QPushButton *AnalyzeCSV::getBtnExportCSV(std::size_t i){
    switch(i){
    case(0): return ui->btnExportCSVPub;
    case(1): return ui->btnExportCSVGrant;
    case(2): return ui->btnExportCSVPres;
    case(3): return ui->btnExportCSVTeach;
    }
    return 0;
}

QTreeWidget *AnalyzeCSV::getTreeList(size_t i){
    switch(i){
    case(0): return ui->tree_list_pub;
    case(1): return ui->tree_list_grnt;
    case(2): return ui->tree_list_pres;
    case(3): return ui->tree_list_teach;
    }
    return 0;
}

QComboBox *AnalyzeCSV::getCmbStartYear(size_t i){
    switch(i){
    case(0): return ui->start_date_combo_pub;
    case(1): return ui->start_date_combo_grnt;
    case(2): return ui->start_date_combo_pres;
    case(3): return ui->start_date_combo_teach;
    }
    return 0;
}

QComboBox *AnalyzeCSV::getCmbEndYear(size_t i){
    switch(i){
    case(0): return ui->end_date_combo_pub;
    case(1): return ui->end_date_combo_grnt;
    case(2): return ui->end_date_combo_pres;
    case(3): return ui->end_date_combo_teach;
    }
    return 0;
}

QComboBox *AnalyzeCSV::getCmbName(size_t i){
    switch(i){
    case(0): return ui->name_combo_pub;
    case(1): return ui->name_combo_grnt;
    case(2): return ui->name_combo_pres;
    case(3): return ui->name_combo_teach;
    }
    return 0;
}

QComboBox *AnalyzeCSV::getCmbType(size_t i){
    switch(i){
    case(0): return ui->type_combo_pub;
    case(1): return ui->type_combo_grnt;
    case(2): return ui->type_combo_pres;
    case(3): return ui->program_combo_teach;
    }
    return 0;
}

QLabel *AnalyzeCSV::getLblDomain(size_t i){
    switch(i){
    case(0): return ui->domain_lbl_pub;
    case(1): return ui->domain_lbl_grnt;
    case(2): return ui->domain_lbl_pres;
    case(3): return ui->domain_lbl_teach;
    }
    return 0;
}

QGraphicsView *AnalyzeCSV::getBarGraph(size_t i){
    switch(i){
    case(0): return ui->graph_area_pub;
    case(1): return ui->graph_area_grnt;
    case(2): return ui->graph_area_pres;
    case(3): return ui->graph_area_teach;
    }
    return 0;
}

void AnalyzeCSV::on_btnExportCSVTeach_clicked()
{
    exportCSV(TEACHING);
}

void AnalyzeCSV::on_btnExportCSVPres_clicked()
{
    exportCSV(PRESENTATION);
}

void AnalyzeCSV::on_btnExportCSVGrant_clicked()
{
    exportCSV(GRANTS);
}

void AnalyzeCSV::on_btnExportCSVPub_clicked()
{
    exportCSV(PUBLICATION);
}

void AnalyzeCSV::exportCSV(CSVType t){
    QString f = QFileDialog::getSaveFileName(this,
                                            tr("Save File"),        // Dialog for prompt
                                            "C://",                 // Default folder to open
                                            "CSV Files (*.csv)"     // File extension to filter for
                                            );
    string fname = f.toStdString();
    if(fname == "") return;

    Data::Instance()->saveCSV(&fname, t);
}
