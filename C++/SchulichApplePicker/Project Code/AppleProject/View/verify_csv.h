#ifndef VERIFY_CSV_H
#define VERIFY_CSV_H

#include <QMainWindow>

#include <vector>
#include <string>
#include <memory>

enum CSVType: unsigned int;
enum ErrorType: unsigned int;

namespace Ui {
class VerifyCSV;
}

class Data;
class QStandardItemModel;

class VerifyCSV : public QMainWindow
{
    Q_OBJECT

public:
    explicit VerifyCSV(QWidget *parent = 0);
    void updateTable(CSVType t);

    ~VerifyCSV();

private slots:
    void on_load_btn_clicked();
    void on_analyze_btn_clicked();
    void on_ignoreall_btn_clicked();
    void on_ignore_btn_clicked();
    void on_confirm_btn_clicked();

signals:
    void gotoLoad(ErrorType err, CSVType t);
    void gotoAnalyze(CSVType csvType);

private:
    Ui::VerifyCSV *ui;
    std::size_t col, row;
    CSVType csvType;
    Data *data;

    //Loads the csv error lines into the ui.
    QStandardItemModel* ErrorTableModel();
    //Ignores all error lines and saves the csv
    void ignoreAll();
    void moveForwards();
};

#endif // VERIFY_CSV_H
