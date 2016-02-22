#include "bargraph.h"

#include <QString>
#include <QGraphicsScene>
#include <QPushButton>

#include <algorithm>

#include "Tab-Objects/qcustomplot.h"
#include "Tab-Objects/dtofilter.h"
#include "DTO/csvdto.h"
#include "DTO/bargraphadapter.h"
#include "View/analyze_csv.h"

using namespace std;

BarGraph::BarGraph(QGraphicsView *v, AnalyzeCSV *p, TabSubject *s, QPushButton *btn):
    TabObserver(s)
{
    dto = 0;
    plot = 0;
    view = v;
    an = p;

    connect(p, SIGNAL(resizeEvent(QResizeEvent*)),
            this, SLOT(onResize()));
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(saveGraph()));
}

void BarGraph::setDTO(CSVDTO *dto){
    this->dto = dto;
}

void BarGraph::update(){    
    loadValues(&years, &types, &values);
    if(years.size() == 0) return;
    makeGraph(&years, &types, &values);

    years.clear();
    types.clear();
    values.clear();
}

void BarGraph::loadValues(QVector<QString> *years, QVector<QString> *types, QVector<QVector<double> > *values ){
    vector<string> filterValues = subject->getState();
    DTOFilter filter(&filterValues);
    vector<FilterAdapter> *fdtos = dto->getFilterDTOs();
    vector<BarGraphAdapter> *bgdtos = dto->getBarGraphDTOs();
    vector<BarGraphAdapter *> filteredDtos;

    //-----------------------------------Pull all relevant data from the csv dtos
    for(size_t i = 0; i < bgdtos->size(); ++i){
        //Make sure the dto is in our filter ranges
        if(filter.filter(&fdtos->at(i))){
            BarGraphAdapter *dto = &bgdtos->at(i);
            if(*dto->getValue() <= 0) continue;
            filteredDtos.push_back(dto);

            QString year = QString::fromStdString(*dto->getYear());
            QString type = QString::fromStdString(*dto->getType());

            QVector<QString>::iterator i;
            //Add the year if it is not in the list
            i = std::find(years->begin(), years->end(), year);
            if(i == years->end()) years->push_back(year);

            //Add the type if it is not in the list
            i = std::find(types->begin(), types->end(), type);
            if(i == types->end()) types->push_back(type);
        }
    }

    std::sort(years->begin(), years->end());
    std::sort(types->begin(), types->end());

    for(int i = 0; i < types->size(); ++i){
        QVector<double> row;
        for(int j = 0; j < years->size(); ++j){
            row.push_back(0.0);
        }
        values->push_back(row);
    }

    //Sum the values for each year x type
    for(size_t i = 0; i < filteredDtos.size(); ++i){
        BarGraphAdapter *dto = filteredDtos.at(i);

        QString year = QString::fromStdString(*dto->getYear());
        QString type = QString::fromStdString(*dto->getType());
        double *value = dto->getValue();

        size_t j,k;
        j = std::find(types->begin(), types->end(), type) - types->begin();
        k = std::find(years->begin(), years->end(), year) - years->begin();
        (*values)[j][k] += *value;
    }
}

void BarGraph::makeGraph(QVector<QString> *years, QVector<QString> *types, QVector<QVector<double> > *values ){
    vector<string> state = subject->getState();
    delete plot;
    plot = new QCustomPlot();

    //Add the title
    plot->plotLayout()->insertRow(0);
    QString title = QString::fromStdString(state[2] + " - " + state[3]
            + "\n" + state[0] + " - " + state[1]);
    plot->plotLayout()->addElement(0,0, new QCPPlotTitle(plot, title));

    //Set the ticks for the x axis and find the max value
    int maxY = 0;
    QVector<double> yearTick;

    int nYears = years->size();
    int nTypes = types->size();

    for(int i = 0; i < nYears; ++i){
        yearTick.push_back((nTypes + 1)*i + 1);

        for(int j = 0; j < nTypes; ++j){
            if((*values)[j][i] > maxY)  maxY = (*values)[j][i];
        }
    }

    QCPBarsGroup *group = new QCPBarsGroup(plot);
    group->setSpacing(1);

    //Add each set of data to the bargroup
    for(int i = 0; i < nTypes; ++i){
        QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
        bars->setData(yearTick, (*values)[i] );
        //Change color of bars based on number of them
        bars->setBrush(QColor(  (i*21)%255  ,(i*11)%255 ,255-(i*21)%255,50));
        bars->setPen(QColor( (i*21)%255, (i*2)%255 , 255-(i*21)%255));
        bars->setWidth(1.0);
        bars->setBarsGroup(group);
        plot->addPlottable(bars);
    }

    //Set the labels of the xaxis
    plot->xAxis->setAutoTicks(false);
    plot->xAxis->setAutoTickLabels(false);
    plot->xAxis->setAutoTickStep(false);
    plot->xAxis->setRange(0, yearTick.last() + 1);
    plot->xAxis->setTickVector(yearTick);
    plot->xAxis->setTickVectorLabels(*years);
    plot->xAxis->setTickLabelRotation(-45.0);
    plot->xAxis->setLabel(QString::fromStdString("Years"));

    //Find the correct tick size and range for the yaxis
    double yTick;
    for(yTick = 1.0; yTick*10 < maxY; yTick *= 10);
    for(;(maxY/yTick + 1) < 4; yTick /= 2);
    if(yTick < 1) yTick = 1;

    //Set up the axis tick labels
    QVector<double> valueTick;
    QVector<QString> valueLables;
    for(double i = 0.0; i <= (maxY + yTick); i += yTick){
        valueTick.push_back(i);
        string label = getYTickLabel(i);
        valueLables.push_back(QString::fromStdString(label));
    }

    //Set the labels of the yaxis
    plot->yAxis->setAutoTicks(false);
    plot->yAxis->setAutoTickLabels(false);
    plot->yAxis->setAutoTicks(false);
    plot->yAxis->setRange(0, maxY + yTick);
    plot->yAxis->setTickVector(valueTick);
    plot->yAxis->setTickVectorLabels(valueLables);
    plot->yAxis->setTickStep(yTick);
    plot->yAxis->setLabel(QString::fromStdString(getYLabel())); //Fix this later

    plot->setGeometry(0,0, view->geometry().width() - 20, view->geometry().height() - 20);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(plot);
    view->setScene(scene);
}

void BarGraph::resize(){
    this->update();
}

void BarGraph::onResize(){
    if(dto != 0) this->resize();
}

string BarGraph::getYLabel(){
    switch(dto->getType()){
        case(0): return "# Publications";
        case(1): return "Total Funding\n(in $)";
        case(2): return "# of Presentations";
        case(3): return "# of Hours";
    }
    return "Type";
}

string BarGraph::getYTickLabel(double v){
    string result;
    if(v >= 10000000000){
        result = "B";
        v /= 1000000000;
    }
    else if(v >= 10000000){
        result = "M";
        v /= 1000000;
    }
    else if(v >= 10000){
        result = "K";
        v /= 1000;
    }
    else{
        result = "";
    }

    result = to_string((unsigned long long) v) + result;
    return result;
}

void BarGraph::saveGraph(){
    if(plot == 0) return;

    QString f = QFileDialog::getSaveFileName(an,
                                            tr("Save File"),        // Dialog for prompt
                                            "C://",                 // Default folder to open
                                            "PNG Files (*.png)"     // File extension to filter for
                                            );
    if(f.toStdString() == "") return;

    plot->savePng(f);
}
