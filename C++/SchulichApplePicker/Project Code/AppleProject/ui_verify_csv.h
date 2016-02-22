/********************************************************************************
** Form generated from reading UI file 'verify_csv.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFY_CSV_H
#define UI_VERIFY_CSV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VerifyCSV
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *navigation_area;
    QPushButton *load_btn;
    QPushButton *verify_btn;
    QPushButton *analyze_btn;
    QVBoxLayout *table_area;
    QLabel *instruction_label;
    QTableView *error_table;
    QHBoxLayout *horizontalLayout;
    QLabel *file_name_label;
    QLabel *file_name;
    QPushButton *ignoreall_btn;
    QPushButton *ignore_btn;
    QPushButton *confirm_btn;

    void setupUi(QMainWindow *VerifyCSV)
    {
        if (VerifyCSV->objectName().isEmpty())
            VerifyCSV->setObjectName(QStringLiteral("VerifyCSV"));
        VerifyCSV->resize(1000, 640);
        VerifyCSV->setMinimumSize(QSize(800, 600));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        VerifyCSV->setPalette(palette);
        VerifyCSV->setAutoFillBackground(true);
        centralwidget = new QWidget(VerifyCSV);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        navigation_area = new QHBoxLayout();
        navigation_area->setObjectName(QStringLiteral("navigation_area"));
        navigation_area->setSizeConstraint(QLayout::SetDefaultConstraint);
        load_btn = new QPushButton(centralwidget);
        load_btn->setObjectName(QStringLiteral("load_btn"));
        load_btn->setMaximumSize(QSize(16777215, 50));
        QPalette palette1;
        QBrush brush5(QColor(170, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        QBrush brush6(QColor(120, 120, 120, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        load_btn->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(28);
        font.setBold(true);
        font.setWeight(75);
        load_btn->setFont(font);
        load_btn->setFlat(true);

        navigation_area->addWidget(load_btn);

        verify_btn = new QPushButton(centralwidget);
        verify_btn->setObjectName(QStringLiteral("verify_btn"));
        verify_btn->setMaximumSize(QSize(16777215, 50));
        QPalette palette2;
        QBrush brush7(QColor(255, 213, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        verify_btn->setPalette(palette2);
        verify_btn->setFont(font);
        verify_btn->setFlat(true);

        navigation_area->addWidget(verify_btn);

        analyze_btn = new QPushButton(centralwidget);
        analyze_btn->setObjectName(QStringLiteral("analyze_btn"));
        analyze_btn->setMaximumSize(QSize(16777215, 50));
        QPalette palette3;
        QBrush brush8(QColor(0, 170, 0, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        analyze_btn->setPalette(palette3);
        analyze_btn->setFont(font);
        analyze_btn->setFlat(true);

        navigation_area->addWidget(analyze_btn);


        gridLayout->addLayout(navigation_area, 0, 0, 1, 1);

        table_area = new QVBoxLayout();
        table_area->setObjectName(QStringLiteral("table_area"));
        instruction_label = new QLabel(centralwidget);
        instruction_label->setObjectName(QStringLiteral("instruction_label"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setBold(true);
        font1.setWeight(75);
        instruction_label->setFont(font1);
        instruction_label->setAlignment(Qt::AlignCenter);

        table_area->addWidget(instruction_label);

        error_table = new QTableView(centralwidget);
        error_table->setObjectName(QStringLiteral("error_table"));
        error_table->setAlternatingRowColors(false);
        error_table->setSelectionBehavior(QAbstractItemView::SelectRows);

        table_area->addWidget(error_table);


        gridLayout->addLayout(table_area, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        file_name_label = new QLabel(centralwidget);
        file_name_label->setObjectName(QStringLiteral("file_name_label"));
        file_name_label->setMinimumSize(QSize(90, 40));
        file_name_label->setMaximumSize(QSize(90, 40));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial Black"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        file_name_label->setFont(font2);

        horizontalLayout->addWidget(file_name_label);

        file_name = new QLabel(centralwidget);
        file_name->setObjectName(QStringLiteral("file_name"));
        file_name->setMinimumSize(QSize(0, 40));
        file_name->setMaximumSize(QSize(16777215, 40));

        horizontalLayout->addWidget(file_name);

        ignoreall_btn = new QPushButton(centralwidget);
        ignoreall_btn->setObjectName(QStringLiteral("ignoreall_btn"));
        ignoreall_btn->setMinimumSize(QSize(100, 40));
        ignoreall_btn->setMaximumSize(QSize(100, 40));
        ignoreall_btn->setFont(font2);

        horizontalLayout->addWidget(ignoreall_btn);

        ignore_btn = new QPushButton(centralwidget);
        ignore_btn->setObjectName(QStringLiteral("ignore_btn"));
        ignore_btn->setMinimumSize(QSize(100, 40));
        ignore_btn->setMaximumSize(QSize(100, 40));
        ignore_btn->setFont(font2);

        horizontalLayout->addWidget(ignore_btn);

        confirm_btn = new QPushButton(centralwidget);
        confirm_btn->setObjectName(QStringLiteral("confirm_btn"));
        confirm_btn->setMinimumSize(QSize(150, 40));
        confirm_btn->setMaximumSize(QSize(150, 40));
        confirm_btn->setFont(font2);

        horizontalLayout->addWidget(confirm_btn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        VerifyCSV->setCentralWidget(centralwidget);

        retranslateUi(VerifyCSV);

        QMetaObject::connectSlotsByName(VerifyCSV);
    } // setupUi

    void retranslateUi(QMainWindow *VerifyCSV)
    {
        VerifyCSV->setWindowTitle(QApplication::translate("VerifyCSV", "MainWindow", 0));
        load_btn->setText(QApplication::translate("VerifyCSV", "LOAD >", 0));
        verify_btn->setText(QApplication::translate("VerifyCSV", "VERIFY >", 0));
        analyze_btn->setText(QApplication::translate("VerifyCSV", "ANALYZE >", 0));
        instruction_label->setText(QApplication::translate("VerifyCSV", "<html><head/><body><p><span style=\" font-weight:600;\">CSV file errors must either be corrected or ignored before proceeding to the 'Analyze' page</span></p></body></html>", 0));
        file_name_label->setText(QApplication::translate("VerifyCSV", "FILE NAME: ", 0));
        file_name->setText(QString());
        ignoreall_btn->setText(QApplication::translate("VerifyCSV", "IGNORE ALL", 0));
        ignore_btn->setText(QApplication::translate("VerifyCSV", "IGNORE", 0));
        confirm_btn->setText(QApplication::translate("VerifyCSV", "CONFIRM CHANGES", 0));
    } // retranslateUi

};

namespace Ui {
    class VerifyCSV: public Ui_VerifyCSV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFY_CSV_H
