#include "load_window.h"
#include "ui_load_window.h"

LoadWindow::LoadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);
    ui->verify_btn->setDisabled(true);
    ui->analyze_btn->setDisabled(true);
    filename = "";
    csvType = 0;

    recentFilesModel = new QStringListModel(this);
    ui->recent_files_list->setSelectionRectVisible(false);
    ui->recent_files_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

LoadWindow::~LoadWindow()
{
    delete ui;
}

void addRecentFile(Ui::LoadWindow *ui, QString file, QStringList recentFilesList, QStringListModel recentFilesModel)
{
    recentFilesList.insert(0,file);
    recentFilesModel.setStringList(recentFilesList);
    ui->recent_files_list->setModel(recentFilesModel);
}

QString load_file(LoadWindow *ui, string csvType, QStringList recentFilesList, QStringListModel recentFilesModel)
{
    QString filename = QFileDialog::getOpenFileName(
                                          this,
                                          tr("Open File"),        // Dialog for prompt
                                          "C://",                 // Default folder to open
                                          "CSV Files (*.csv)"     // File extension to filter for
                                          );
    ui->verify_btn->setDisabled(false);
    addRecentFile(ui, csvType + filename, recentFilesList, recentFilesModel);
    return filename;8
}

void LoadWindow::on_load_pub_btn_clicked()
{
    ui->file_name_load->setText(load_file(ui, "Publications: ", recentFilesList, recentFilesModel));
    csvType = 1;
}

void LoadWindow::on_load_grnt_btn_clicked()
{
    ui->file_name_load->setText(load_file(ui, "Grants: "));
    csvType = 6;
}

void LoadWindow::on_load_teach_btn_clicked()
{
    ui->file_name_load->setText(load_file(ui, "Teaching: "));
    csvType = 5;
}

void LoadWindow::on_load_pres_btn_clicked()
{
    ui->file_name_load->setText(load_file(ui, "Presentations: "));
    csvType = 4;
}

void LoadWindow::on_recent_files_btn_clicked()
{
    QString selectedString = recentFilesList[ui->recent_files_list->currentIndex().row()];
    QStringList splitList = selectedString.split(": ");

    if (!QString::compare(splitList[0],"Publications"))
        csvType = 1;
    else if (!QString::compare(splitList[0],"Presentations"))
        csvType = 4;
    else if (!QString::compare(splitList[0],"Teaching"))
        csvType = 5;
    else if (!QString::compare(splitList[0],"Grants"))
        csvType = 6;
    else
        csvType = 0;

    filename = splitList[1];
    ui->selected_file_lbl->setText(filename);
}

void LoadWindow::on_verif_btn_clicked()
{
    verify_csv_page = new VerifyCSV(filename, csvType);
    this->setCentralWidget(verify_csv_page);
}
