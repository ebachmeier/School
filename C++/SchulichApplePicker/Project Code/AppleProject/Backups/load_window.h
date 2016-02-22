#ifndef LOAD_WINDOW_H
#define LOAD_WINDOW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QString>
#include <string.h>
#include "verify_csv.h"

namespace Ui {
class LoadWindow;
}

class LoadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = 0);
    ~LoadWindow();

private slots:
    void on_load_pub_btn_clicked();

    void on_load_grnt_btn_clicked();

    void on_load_teach_btn_clicked();

    void on_load_pres_btn_clicked();

    void on_recent_files_btn_clicked();

    void on_verif_btn_clicked();

    void on_analyze_btn_clicked();

private:
    Ui::LoadWindow *ui;
    VerifyCSV *verify_csv_page;
    QString filename;
    QStringListModel *recentFilesModel;
    QStringList recentFilesList;
    int csvType;

protected:
    void addRecentFile(Ui::LoadWindow *ui, QString file, QStringList recentFilesList, QStringListModel recentFilesModel);

    QString load_file(Ui::LoadWindow *ui, string csvType, QStringList recentFilesList, QStringListModel recentFilesModel);
};

#endif // LOAD_WINDOW_H
