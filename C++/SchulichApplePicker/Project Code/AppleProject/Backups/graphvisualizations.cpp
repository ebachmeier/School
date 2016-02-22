#include "graphvisualizations.h"
/*
Graphvisualizations::Graphvisualizations()
{
    // default constructor
}


/**
 * @brief Graphvisualizations::plot_grants_vs_type takes 1 (ONE) funding type and graphs it
 * @param customPlot    is the plot being generated (constructed in analyze_csv.cpp)
 * @param bargraph_vo is the grantVO being graphed. This is either a VO for grants or clinical trials
 */


/*void Graphvisualizations::plot_grants_vs_trials(QCustomPlot* customPlot, Grant_BarGraph1_VO* bargraph_vo){

    QCPBarsGroup *group = new QCPBarsGroup(customPlot);
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    //Sort the year strings to int values
    QVector<double> xvalues;

    for (int i = 0; i < bargraph_vo->years.size(); i ++)    // Iterate through years, assign double values
    {
        xvalues.push_back(std::stod(bargraph_vo->years.at(i)) );
        cout <<"ixvalues: " << xvalues.at(i)<<endl;
    }   // Successfully stores string years into a set of doubles

    QVector<QVector<double>> yvalues; // Contains converted double vector of QVector type
    for (int i = 0; i < bargraph_vo->values.size(); i ++)   // Iterate through # Publications [13]
    {
        vector<int> y_add;          // Load the set of years from the bargraph_vo object
        y_add = bargraph_vo->values.at(i);

        QVector<double> y_add_to_yval;  // retrieve QVector<double> ytemp
        for (int j = 0; j < bargraph_vo->years.size(); j ++) // Iterate  through #years per Publication [11]
        {
            y_add_to_yval.push_back(y_add.at(j));
        }
        yvalues.push_back(y_add_to_yval);   // Add the converted set to final double vector of QVector type
    }

    int maxY = 0;   // Save the maximum value for y range

    // Add each component, with the colour changing based on index
    for (int i = 0; i < bargraph_vo->grantTypes.size(); i ++)
    {
        bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        customPlot->addPlottable(bars);
        QVector<double> y_component = yvalues.at(i);
        bars->setData(xvalues,y_component);
        bars->setBrush(QColor(  (i*21)%255  ,(i*11)%255 ,255-(i*21)%255,50));  // 255/12 ~= 21 (21 gives best coverage)
        bars->setPen(QColor( (i*21)%255, (i*2)%255 , 255-(i*21)%255));
        bars->setWidth(0.3);
        bars->setBarsGroup(group);
    }

    //Title = first name in the list
    customPlot->plotLayout()->insertRow(0);
    char * x = &bargraph_vo->name[0];           // Set the name of the first author, can be modified later to select for a certain author
    QString str = x;

    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, str)); //title of the graph
    customPlot->xAxis->setRange((xvalues.at(0))-1, (xvalues.at(xvalues.size()-1))+1);   // Set range of graph   +/-3 so bars wont be on edges

    customPlot->yAxis->setAutoTickStep(false);  // force integer for Y only (be wary of doing this with grants)
    customPlot->yAxis->setTickStep(1);  // force integer for Y only (be wary of doing this with grants)

    customPlot ->yAxis->setRange(0,maxY);
    customPlot->xAxis->setLabel("Year");
    customPlot->yAxis->setLabel("Publications");
}

void Graphvisualizations::plot_teaching_vs_course(QCustomPlot* customPlot, Teach_BarGraph1_VO* bargraph_vo)
{
    /*
    Eric/Emily

    I commented this out because when you do the teaching_vs_course graphs, you need
    to be passing all the vo's to it (PME, UME, CME, and Other)

    i.e. I think the function header needs to be changed to
    Graphvisualizations::plot_teaching_vs_course(QCustomPlot* customPlot, Teach_BarGraph1_VO* PME, Teach_BarGraph1_VO* UME, Teach_BarGraph1_VO* CME, Teach_BarGraph1_VO* other))

    With these VO's you need to iterate through each one separately and add its values
    to the bar graph

    This is gonna be kinda challenging because my example plot_pub_vs_type() only plots a Publications type;
    I think you guys can adapt to it though, let me know if theres any hiccups implementing this part - Jerry
    */


    /*
    QCPBarsGroup *group = new QCPBarsGroup(customPlot);
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    //Sort the year strings to int values
    QVector<double> xvalues;

    for (int i = 0; i < bargraph_vo->years.size(); i ++)    // Iterate through years, assign double values
    {
        xvalues.push_back(std::stod(bargraph_vo->years.at(i)) );
        cout <<"ixvalues: " << xvalues.at(i)<<endl;
    }   // Successfully stores string years into a set of doubles

    QVector<QVector<double>> yvalues; // Contains converted double vector of QVector type
    for (int i = 0; i < bargraph_vo->values.size(); i ++)   // Iterate through number of teaching programs
    {
        vector<int> y_add;          // Load the set of years from the bargraph_vo object
        y_add = bargraph_vo->values.at(i);

        QVector<double> y_add_to_yval;  // retrieve QVector<double> ytemp
        for (int j = 0; j < bargraph_vo->years.size(); j ++) // Iterate  through hours put into each course / program taught
        {
            y_add_to_yval.push_back(y_add.at(j));
        }
        yvalues.push_back(y_add_to_yval);   // Add the converted set to final double vector of QVector type
    }

    // Add each component, with the colour changing based on index
    for (int i = 0; i < bargraph_vo->teachingTypes.size(); i ++)
    {
        bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        customPlot->addPlottable(bars);
        QVector<double> y_component = yvalues.at(i);
        bars->setData(xvalues,y_component);
        bars->setBrush(QColor(  (i*21)%255  ,(i*11)%255 ,255-(i*21)%255,50));  // 255/12 ~= 21 (21 gives best coverage)
        bars->setPen(QColor( (i*21)%255, (i*2)%255 , 255-(i*21)%255));
        bars->setWidth(0.3);
        bars->setBarsGroup(group);
    }

    customPlot->plotLayout()->insertRow(0);
    char * x = &bargraph_vo->name[0];
    QString str = x;

    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, str)); //title of the graph
    customPlot->xAxis->setRange((xvalues.at(0))-3, (xvalues.at(xvalues.size()-1))+3);   // Set range of graph   +/-3 so bars wont be on edges
    customPlot ->yAxis->setRange(0,maxY);
    customPlot->xAxis->setLabel("Program / Course");
    customPlot->yAxis->setLabel("Number of Hours");
    */
//}
