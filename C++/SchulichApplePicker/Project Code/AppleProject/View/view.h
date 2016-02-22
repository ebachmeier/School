#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <QStackedWidget>

class AnalyzeCSV;
class LoadCSV;
class VerifyCSV;
class MainWindow;

enum CSVType: unsigned int;
enum ErrorType: unsigned int;

class View: public QStackedWidget
{
    Q_OBJECT

    AnalyzeCSV *analyze;
    LoadCSV *load = 0;
    VerifyCSV *verify = 0;
    MainWindow *m = 0;

    void gotoLoad(ErrorType t);
public:
    View();
    ~View();

private slots:
    //Go from start window to loading window
    void mainToLoad(std::string);
    void gotoVerify(CSVType t);
    void verToLoad(ErrorType t, CSVType ct);
    void gotoAnalyze(CSVType t);
    void gotoAnalyze();
    void gotoLoad();
};

#endif // VIEW_H
