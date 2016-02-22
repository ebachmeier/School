#ifndef ANALYZETAB_H
#define ANALYZETAB_H

#include <QWidget>

namespace Ui {
class AnalyzeTab;
}

class AnalyzeTab : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeTab(QWidget *parent = 0);
    ~AnalyzeTab();

private:
    Ui::AnalyzeTab *ui;
};

#endif // ANALYZETAB_H
