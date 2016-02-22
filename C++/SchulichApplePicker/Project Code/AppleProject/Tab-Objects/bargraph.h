#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QVector>
#include <QObject>

#include <vector>
#include <string>

#include "Tab-Objects/tabobserver.h"

class TabSubject;
class CSVDTO;
class QGraphicsView;
class QCustomPlot;
class AnalyzeCSV;
class QPushButton;

class BarGraph:public QObject, public TabObserver
{
    Q_OBJECT

    QVector<QString> years, types;
    QVector<QVector<double>> values;

    AnalyzeCSV *an;
    QGraphicsView *view;
    QCustomPlot *plot = 0;
    CSVDTO *dto;

    void loadValues(QVector<QString> *years, QVector<QString> *types, QVector<QVector<double> > *values );
    void makeGraph(QVector<QString> *years, QVector<QString> *types, QVector<QVector<double> > *values );
    std::string getYLabel();
    std::string getYTickLabel(double v);
public:
    BarGraph(QGraphicsView *v, AnalyzeCSV *p, TabSubject *s, QPushButton *btn);
    void resize();
    void update();
    void setDTO(CSVDTO *dto);
public slots:
    void onResize();
    void saveGraph();
};

#endif // BARGRAPH_H
