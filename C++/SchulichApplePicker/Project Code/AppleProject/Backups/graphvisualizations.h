#ifndef GRAPHVISUALIZATIONS_H
#define GRAPHVISUALIZATIONS_H
/*
#include <qcustomplot.h>
#include <memory>

#include "bargraph_vo.h"

class Teach_BarGraph1_VO;   // To add by Eric + Emily
class Grant_BarGraph1_VO;   // to add by Jaisen/Jennifer
//class Pres_BarGraph1_VO;        // To add for Jerry

class Graphvisualizations
{
    //

public:
    Graphvisualizations();

    //Bar Graph Creator
    template <class DTOType> void plot_bargraph(QCustomPlot* customPlot, std::shared_ptr<BarGraph_VO<DTOType>> vo, QString xAxis, QString yAxis, string subtitle);

    // Add support for shared pointer afterwards
    //1)  For faculty member (name), graph publications by type
    // ^ For a certain date range

    


    //2)For faculty member (name), graph funded research(grants/trials)
        // ^ For a certain date range
    void plot_grants_vs_trials(QCustomPlot *plot, Grant_BarGraph1_VO *bargraph_vo);

    //3)For faculty name, graph publication types by date (bar chart?)
    void plot_pubtype_vs_date(QCustomPlot* plot);

    //4)For faculty name, graph teaching by program level
        // ^ for a certain date range
    void plot_teaching_vs_course(QCustomPlot* customPlot, Teach_BarGraph1_VO* bargraph_vo);

    //5)For faculty name, graph course/activity by program level
        // ^ For a certain date range

private:
    void bar_plot(QCustomPlot* plot);        // Deal with later
    void pie_chart(QCustomPlot* plot);      // Implement later
};


template <class DTOType>
void Graphvisualizations::plot_bargraph(QCustomPlot* customPlot, std::shared_ptr<BarGraph_VO<DTOType>> vo, QString xAxis, QString yAxis, string subtitle){

    QCPBarsGroup *group = new QCPBarsGroup(customPlot);
    group->setSpacing(.025);

    QCPBars *bars;

    // Add each component, with the colour changing based on index
    for (int i = 0; i < vo->field2.size(); i++)
    {
        bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        customPlot->addPlottable(bars);
        bars->setData(vo->yearTick, vo->values.at(i));
        bars->setBrush(QColor(  (i*21)%255  ,(i*11)%255 ,255-(i*21)%255,50));  // 255/12 ~= 21 (21 gives best coverage)
        bars->setPen(QColor( (i*21)%255, (i*2)%255 , 255-(i*21)%255));
        bars->setWidth(.6);
        bars->setBarsGroup(group);
    }

    //Title = faculty name
    customPlot->plotLayout()->insertRow(0);
    QString str = QString::fromStdString(vo->name + "\n" + subtitle);  // Set the name of the author

    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, str)); //title of the graph

    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setAutoTicks(false);

    if (vo->yearTick.size() != 0)   // Check to ensure no out of bound year ranges
    {
        customPlot->xAxis->setRange(0, (vo->yearTick.at(vo->yearTick.size()-1))+1);
        customPlot->xAxis->setTickVector(vo->yearTick);
        customPlot->xAxis->setTickVectorLabels(vo->yearLabel);
    }
    else    // Default year range is 0-3000
    {
        customPlot ->xAxis -> setRange(0, 3000);    // Set this default year
    }
    customPlot->xAxis->setTickLabelRotation(90);
    customPlot->xAxis->setTickStep(3);
    customPlot->xAxis->setLabel(xAxis);

    int ytick = 1;
    for(;ytick*10 < (vo->maxY);ytick*=10);
    customPlot->yAxis->setAutoTickStep(false);
    customPlot->yAxis->setTickStep(ytick);
    customPlot ->yAxis->setRange(0,vo->maxY + ytick/2);
    customPlot->yAxis->setLabel(yAxis);
}
*/
#endif // GRAPHVISUALIZATIONS_H

