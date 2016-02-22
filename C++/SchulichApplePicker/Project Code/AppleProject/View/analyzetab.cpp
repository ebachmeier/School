#include "analyzetab.h"
#include "ui_analyzetab.h"

AnalyzeTab::AnalyzeTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeTab)
{
    ui->setupUi(this);
}

AnalyzeTab::~AnalyzeTab()
{
    delete ui;
}
