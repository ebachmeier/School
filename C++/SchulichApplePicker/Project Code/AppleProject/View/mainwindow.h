#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Builds the main window and displays the apple logo
 *
 */

#include <QMainWindow>
#include <QPixmap>

#include "View/load_csv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_open_program_btn_clicked();

signals:

    void gotoLoad(std::string);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
