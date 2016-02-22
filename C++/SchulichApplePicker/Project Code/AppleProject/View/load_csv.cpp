#include "View/load_csv.h"
#include "View/ui_load_csv.h"

#include <QPushButton>
#include <QString>
#include <QStringListModel>
#include <QFileDialog>

#include "CSV-Data/csvtype.h"
#include "DTO/data.h"
#include "View/verify_csv.h"
#include "View/analyze_csv.h"

using namespace std;

LoadCSV::LoadCSV(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::LoadCSV)
{
    ui->setupUi(this);
    ui->verify_btn->setDisabled(true);
    ui->analyze_btn->setDisabled(true);
    data = Data::Instance();

    //Set up the mouse over listener
    for(size_t t = 0; t < NBUT; t++){
        this->getCSVButton((CSVType)t)->installEventFilter(this);
    }

}

LoadCSV::~LoadCSV()
{
    delete ui;
}

//Hover over button (or other things) listener.
bool LoadCSV::eventFilter(QObject *obj, QEvent *event)
{
    // This function repeatedly call for those QObjects
    // which have installed eventFilter (Step 2)

    for(std::size_t i = 0; i < NBUT; i++){
        CSVType t = (CSVType)i;
        if(obj == (QObject*)(this->getCSVButton(t)))
        {
            if (event->type() == QEvent::Enter)
            {
                setMouseOverBtnTxt(t);
            }
            else if(event->type() == QEvent::Leave){
                resetBtnTxt(t);
            }
            else if(event->type() == QEvent::MouseButtonPress){
                this->loadCSV(t);
            }
        }
    }
    // pass the event on to the parent class
    return QWidget::eventFilter(obj, event);
}

QPushButton *LoadCSV::getCSVButton(CSVType t){
    switch(t){
        case(PUBLICATION): return ui->publication_btn;
        case(GRANTS): return ui->grant_btn;
        case(PRESENTATION): return ui->presentation_btn;
        case(TEACHING): return ui->teaching_btn;
    }
    return 0;
}

void LoadCSV::setMouseOverBtnTxt(CSVType t){
    if(!data->isEmpty(t)) this->getCSVButton(t)->setText("Warning: This will\n""overwrite data");
}

void LoadCSV::resetBtnTxt(CSVType t){
    this->getCSVButton(t)->setText(defaultBtntxt.at(t));
}

void LoadCSV::setDefaultBtnTxt(){
    defaultBtntxt.clear();
    std::string def[] = {"PUBLICATIONS", "GRANTS", "PRESENTATIONS", "TEACHING"};
    for(std::size_t i = 0; i < NBUT; i++){
        std::string s = def[i];
        defaultBtntxt.push_back(QString::fromStdString(s));

        CSVType t = (CSVType)i;
        QString tooltip = QString::fromStdString((data->isEmpty(t))?"":data->getShortFileName(t));
        this->getCSVButton(t)->setToolTip(tooltip);
    }
}

void LoadCSV::loadCSV(CSVType t){
    try{
        string file = this->getFile();
        data->loadDTO(&file, t);

        //If there are errors move to the analyze page
        if(data->hasErrors(t)){
            ui->analyze_btn->setEnabled(true);
            emit gotoVerify(t);
        }
        else{
            //If there are valid lines go to analyze
            if(data->isEmpty(t)){
                setError(NODATA);
            }
            else{               
                ui->analyze_btn->setEnabled(true);
                emit gotoAnalyze(t);
            }
        }
    }
    catch(error::missing_header_error){
        setError(MISSINGHEADER);
    }
    catch(io::error::can_not_open_file){
        setError(CANTREADFILE);
    }
    catch(error::csv_format_error){
        setError(CSVFORMAT);
    }
    catch(error::duplicate_header_error){
        setError(DUPLICATEHEADER);
    }
}

//Later add last file path chosen?
string LoadCSV::getFile(){
    QString f = QFileDialog::getOpenFileName(this,
                                            tr("Open File"),        // Dialog for prompt
                                            "C://",                 // Default folder to open
                                            "CSV Files (*.csv)"     // File extension to filter for
                                            );
    return f.toStdString();
}

void LoadCSV::on_analyze_btn_clicked()
{
    emit gotoAnalyze();
}

void LoadCSV::setError(ErrorType t){
    QLabel *err = ui->lblError;
    switch(t){
        case NODATA:
            err->setText("  Error: CSV has no valiad data. File Removed.");
            break;
        case MISSINGHEADER:
            err->setText("  Error: File is missing mandatory headers.");
            break;
        case CANTREADFILE:
            err->setText("  Error: Cannot read from file.");
            break;
        case CSVFORMAT:
            err->setText("  Error: CSV formatting is not as expcectd.");
            break;
        case DUPLICATEHEADER:
            err->setText("  Error: CSV has duplicate header");
            break;
        case NONE:
            err->setText("");
            break;
    }
}
