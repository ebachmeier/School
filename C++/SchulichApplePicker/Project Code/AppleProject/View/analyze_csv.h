#ifndef ANALYZE_CSV_H
#define ANALYZE_CSV_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include <vector>

#define NTAB 4

enum FilterValueType: unsigned int;
class Data;
class ComboBox;
class BarGraph;
class QGraphicsScene;
class QCustomPlot;
class QComboBox;
class QLabel;
class QGraphicsView;
class QTreeWidget;
class TreeList;
class QPushButton;

enum CSVType:unsigned int;

namespace Ui {
class AnalyzeCSV;
}

class AnalyzeCSV : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnalyzeCSV(QWidget *parent = 0);
    void doneloading();
    ~AnalyzeCSV();
    void loadTab(std::size_t i);
    QPushButton *getBtnExportCSV(std::size_t i);
    QPushButton *getBtnExportGraph(std::size_t i);
signals:
    //Capture a resize event
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void gotoLoad();
private slots:
    void on_load_btn_clicked();


    void on_btnExportCSVTeach_clicked();

    void on_btnExportCSVPres_clicked();

    void on_btnExportCSVGrant_clicked();

    void on_btnExportCSVPub_clicked();

private:
    Data *data;
    std::vector<std::vector<ComboBox *>> cmbBoxes;
    std::vector<BarGraph *> barGraphs;
    std::vector<TreeList *> treeLists;

    Ui::AnalyzeCSV *ui;
    QGraphicsScene * scene; // Added to display the graph through the graph area
    QCustomPlot *customPlot;

    //Getter methods for constructor
    QTreeWidget *getTreeList(size_t i);
    QComboBox *getCmbStartYear(std::size_t i);
    QComboBox *getCmbEndYear(std::size_t i);
    QComboBox *getCmbName(std::size_t i);
    QComboBox *getCmbType(std::size_t i);
    QLabel *getLblDomain(std::size_t i);
    QGraphicsView *getBarGraph(std::size_t i);

    void exportCSV(CSVType t);
};

#endif // ANALYZE_CSV_H
