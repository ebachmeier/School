#include "View/verify_csv.h"
#include "View/ui_verify_csv.h"


#include <QStandardItemModel>
#include <QMessageBox>

#include "CSV-Data/csvtype.h"
#include "CSV-Data/csvfield.h"
#include "DTO/data.h"
#include "View/load_csv.h"
#include "View/analyze_csv.h"

using namespace std;

VerifyCSV::VerifyCSV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VerifyCSV)
{
    ui->setupUi(this);
    data = Data::Instance();      

    ui->analyze_btn->setEnabled(true);
}

VerifyCSV::~VerifyCSV()
{
    delete ui;
}

void VerifyCSV::updateTable(CSVType t){
    ui->verify_btn->setEnabled(true);
    csvType = t;
    // Set the table model (currently only the publication model possible)
    ui->error_table->setModel(ErrorTableModel());

    //Display the file name
    QString fn = QString::fromStdString(data->getShortFileName(csvType));
    ui->file_name->setText(fn);
}

QStandardItemModel* VerifyCSV::ErrorTableModel()
{
    vector<string> *header = data->getHeaders(csvType);
    col = data->getNMan(csvType);
    vector<vector<CSVField>> *errors = data->getErrorLines(csvType);
    row = errors->size();

    // Define a model with the number of rows as error lines,
    //and columns as mandatory columns
    QStandardItemModel *model = new QStandardItemModel(row,col,NULL);

    for(size_t i = 0; i < col; ++i){
        model->setHorizontalHeaderItem(i,
                    new QStandardItem(QString::fromStdString(header->at(i))));
    }

    // Loop through strings and add each to the table model
    for(size_t i = 0; i < row; ++i){
        vector<CSVField> line = errors->at(i);
        for(size_t j = 0; j < col; j++){
            QString qstr = QString::fromStdString(*line.at(j+1).getField());
            QStandardItem *newfield = new QStandardItem(qstr);
            model->setItem(i,j,newfield);
        };
    }
    return model;
}

/*SLOTS*/

void VerifyCSV::on_load_btn_clicked()
{
    // Show alert, "All unvalidated lines will be ignored. This will not change"
    //Your original file."
    if(data->hasErrors(csvType)){
        QMessageBox::StandardButton reload;
        reload = QMessageBox::question(this, "Load New Data",
                                       "All unvalidated data will be ignored.\n"
                                       "This will not change your original CSV.\n"
                                       "Would you like to continue?",
                                       QMessageBox::Yes|QMessageBox::No);
        if (reload == QMessageBox::No) {
            return;
        }
    }

    ignoreAll();
    ErrorType err = NONE;
    if(data->isEmpty(csvType)){
        err = NODATA;
    }
    ui->verify_btn->setDisabled(true);
    emit gotoLoad(err, csvType);
}


void VerifyCSV::on_analyze_btn_clicked()
{    
    if(data->hasErrors(csvType)){
        QMessageBox::StandardButton leave;
        //warn user that unvalidated data will be deleted
        leave = QMessageBox::question(this, "Analyze Data",
                                       "All unvalidated data will be ignored.\n"
                                       "Would you like to continue?",
                                       QMessageBox::Yes|QMessageBox::No);
        if(leave == QMessageBox::No) return;
    }

    moveForwards();
}

void VerifyCSV::on_ignoreall_btn_clicked()
{    
    moveForwards();
}

void VerifyCSV::on_ignore_btn_clicked()
{
    QModelIndexList selection = ui->error_table->selectionModel()->selectedRows();

    // For each row the user has selected, remove the rows from bottom up
    // Removing bottom up prevents any shifting of indexes
    for(int i = selection.count() - 1; i >= 0; --i)
    {
        QModelIndex index = selection.at(i);
        ui->error_table->model()->removeRow(index.row());
        data->removeErrorLine(i, csvType);
        --row;
    }

    if(row == 0) moveForwards();
}

void VerifyCSV::on_confirm_btn_clicked()
{
    vector<vector<string>> newErrors;
    for(size_t i = 0; i < row; ++i){
        vector<string> line;
        for(size_t j = 0; j < col; ++j){
            QModelIndex k = ui->error_table->model()->index(i, j);
            string str = ui->error_table->model()->data(k).toString().toStdString();
            line.push_back(str);
        };
        newErrors.push_back(line);
    }

    //Try and validate the new lines. If a line is changed update the model;
    if(data->validateNewErrors(&newErrors, csvType)){
        ui->error_table->setModel(ErrorTableModel());
    }

    if(row == 0) moveForwards();
}

void VerifyCSV::ignoreAll(){
    ui->error_table->setModel(NULL);
    data->ignoreAllErrors(csvType);
    ui->verify_btn->setDisabled(true);
}

void VerifyCSV::moveForwards(){
    ignoreAll();
    if(data->isEmpty(csvType)){
        emit gotoLoad(NODATA, csvType);
    }
    else{
        emit gotoAnalyze(csvType);
    }
}
