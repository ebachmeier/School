/********************************************************************************
** Form generated from reading UI file 'analyze_csv.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZE_CSV_H
#define UI_ANALYZE_CSV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalyzeCSV
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *navigation_area;
    QPushButton *load_btn;
    QPushButton *verify_btn;
    QPushButton *analyze_btn;
    QTabWidget *tab_widget;
    QWidget *pub_tab;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *date_filter_lbl_pub;
    QComboBox *start_date_combo_pub;
    QComboBox *end_date_combo_pub;
    QLabel *domain_lbl_pub;
    QTreeWidget *tree_list_pub;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnExportCSVPub;
    QVBoxLayout *verticalLayout;
    QLabel *graph_lbl_pub;
    QHBoxLayout *horizontalLayout_14;
    QLabel *name_lbl_pub;
    QComboBox *name_combo_pub;
    QHBoxLayout *horizontalLayout_13;
    QLabel *type_lbl_pub;
    QComboBox *type_combo_pub;
    QGraphicsView *graph_area_pub;
    QHBoxLayout *horizontalLayout_25;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnExportGraphPub;
    QWidget *grant_tab;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *date_filter_lbl_grnt;
    QComboBox *start_date_combo_grnt;
    QComboBox *end_date_combo_grnt;
    QLabel *domain_lbl_grnt;
    QTreeWidget *tree_list_grnt;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnExportCSVGrant;
    QVBoxLayout *verticalLayout_12;
    QLabel *graph_lbl_grnt;
    QHBoxLayout *horizontalLayout_2;
    QLabel *name_lbl_grnt;
    QComboBox *name_combo_grnt;
    QHBoxLayout *horizontalLayout_3;
    QLabel *type_lbl_grnt;
    QComboBox *type_combo_grnt;
    QGraphicsView *graph_area_grnt;
    QHBoxLayout *horizontalLayout_24;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnExportGraphGrant;
    QWidget *present_tab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnExportCSVPres;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *date_filter_lbl_pres;
    QComboBox *start_date_combo_pres;
    QComboBox *end_date_combo_pres;
    QLabel *domain_lbl_pres;
    QTreeWidget *tree_list_pres;
    QVBoxLayout *verticalLayout_7;
    QLabel *graph_lbl_pres;
    QHBoxLayout *horizontalLayout_4;
    QLabel *name_lbl_pres;
    QComboBox *name_combo_pres;
    QHBoxLayout *horizontalLayout_5;
    QLabel *type_lbl_pres;
    QComboBox *type_combo_pres;
    QGraphicsView *graph_area_pres;
    QHBoxLayout *horizontalLayout_23;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnExportGraphPres;
    QWidget *teach_tab;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnExportCSVTeach;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *date_filter_lbl_teach;
    QComboBox *start_date_combo_teach;
    QComboBox *end_date_combo_teach;
    QLabel *domain_lbl_teach;
    QTreeWidget *tree_list_teach;
    QVBoxLayout *verticalLayout_8;
    QLabel *graph_lbl_teach;
    QHBoxLayout *horizontalLayout_6;
    QLabel *name_lbl_teach;
    QComboBox *name_combo_teach;
    QHBoxLayout *horizontalLayout_7;
    QLabel *program_lbl_teach;
    QComboBox *program_combo_teach;
    QGraphicsView *graph_area_teach;
    QHBoxLayout *horizontalLayout_20;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnExportGraphTeach;

    void setupUi(QMainWindow *AnalyzeCSV)
    {
        if (AnalyzeCSV->objectName().isEmpty())
            AnalyzeCSV->setObjectName(QStringLiteral("AnalyzeCSV"));
        AnalyzeCSV->resize(1060, 698);
        AnalyzeCSV->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(AnalyzeCSV);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        navigation_area = new QHBoxLayout();
        navigation_area->setObjectName(QStringLiteral("navigation_area"));
        navigation_area->setSizeConstraint(QLayout::SetDefaultConstraint);
        load_btn = new QPushButton(centralwidget);
        load_btn->setObjectName(QStringLiteral("load_btn"));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        load_btn->setPalette(palette);
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
        QPalette palette1;
        QBrush brush2(QColor(229, 191, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        verify_btn->setPalette(palette1);
        verify_btn->setFont(font);
        verify_btn->setFlat(true);

        navigation_area->addWidget(verify_btn);

        analyze_btn = new QPushButton(centralwidget);
        analyze_btn->setObjectName(QStringLiteral("analyze_btn"));
        QPalette palette2;
        QBrush brush3(QColor(0, 170, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        analyze_btn->setPalette(palette2);
        analyze_btn->setFont(font);
        analyze_btn->setFlat(true);

        navigation_area->addWidget(analyze_btn);


        gridLayout->addLayout(navigation_area, 0, 0, 1, 1);

        tab_widget = new QTabWidget(centralwidget);
        tab_widget->setObjectName(QStringLiteral("tab_widget"));
        tab_widget->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        tab_widget->setFont(font1);
        tab_widget->setAutoFillBackground(true);
        tab_widget->setTabPosition(QTabWidget::West);
        tab_widget->setTabShape(QTabWidget::Triangular);
        pub_tab = new QWidget();
        pub_tab->setObjectName(QStringLiteral("pub_tab"));
        QPalette palette3;
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pub_tab->setPalette(palette3);
        pub_tab->setAutoFillBackground(true);
        gridLayout_3 = new QGridLayout(pub_tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        date_filter_lbl_pub = new QLabel(pub_tab);
        date_filter_lbl_pub->setObjectName(QStringLiteral("date_filter_lbl_pub"));
        date_filter_lbl_pub->setMinimumSize(QSize(75, 0));
        date_filter_lbl_pub->setMaximumSize(QSize(75, 16777215));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        date_filter_lbl_pub->setPalette(palette4);

        horizontalLayout->addWidget(date_filter_lbl_pub);

        start_date_combo_pub = new QComboBox(pub_tab);
        start_date_combo_pub->setObjectName(QStringLiteral("start_date_combo_pub"));

        horizontalLayout->addWidget(start_date_combo_pub);

        end_date_combo_pub = new QComboBox(pub_tab);
        end_date_combo_pub->setObjectName(QStringLiteral("end_date_combo_pub"));
        end_date_combo_pub->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(end_date_combo_pub);


        verticalLayout_2->addLayout(horizontalLayout);

        domain_lbl_pub = new QLabel(pub_tab);
        domain_lbl_pub->setObjectName(QStringLiteral("domain_lbl_pub"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        domain_lbl_pub->setPalette(palette5);
        domain_lbl_pub->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(domain_lbl_pub);

        tree_list_pub = new QTreeWidget(pub_tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tree_list_pub->setHeaderItem(__qtreewidgetitem);
        tree_list_pub->setObjectName(QStringLiteral("tree_list_pub"));
        tree_list_pub->setSortingEnabled(true);

        verticalLayout_2->addWidget(tree_list_pub);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer);

        btnExportCSVPub = new QPushButton(pub_tab);
        btnExportCSVPub->setObjectName(QStringLiteral("btnExportCSVPub"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnExportCSVPub->sizePolicy().hasHeightForWidth());
        btnExportCSVPub->setSizePolicy(sizePolicy);
        btnExportCSVPub->setMinimumSize(QSize(150, 0));

        horizontalLayout_11->addWidget(btnExportCSVPub);


        gridLayout_3->addLayout(horizontalLayout_11, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graph_lbl_pub = new QLabel(pub_tab);
        graph_lbl_pub->setObjectName(QStringLiteral("graph_lbl_pub"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        graph_lbl_pub->setPalette(palette6);
        graph_lbl_pub->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(graph_lbl_pub);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        name_lbl_pub = new QLabel(pub_tab);
        name_lbl_pub->setObjectName(QStringLiteral("name_lbl_pub"));
        name_lbl_pub->setMaximumSize(QSize(100, 40));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        name_lbl_pub->setPalette(palette7);

        horizontalLayout_14->addWidget(name_lbl_pub);

        name_combo_pub = new QComboBox(pub_tab);
        name_combo_pub->setObjectName(QStringLiteral("name_combo_pub"));
        name_combo_pub->setMinimumSize(QSize(250, 0));

        horizontalLayout_14->addWidget(name_combo_pub);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        type_lbl_pub = new QLabel(pub_tab);
        type_lbl_pub->setObjectName(QStringLiteral("type_lbl_pub"));
        type_lbl_pub->setMaximumSize(QSize(100, 40));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        type_lbl_pub->setPalette(palette8);

        horizontalLayout_13->addWidget(type_lbl_pub);

        type_combo_pub = new QComboBox(pub_tab);
        type_combo_pub->setObjectName(QStringLiteral("type_combo_pub"));
        type_combo_pub->setMinimumSize(QSize(250, 0));
        type_combo_pub->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_13->addWidget(type_combo_pub);


        verticalLayout->addLayout(horizontalLayout_13);

        graph_area_pub = new QGraphicsView(pub_tab);
        graph_area_pub->setObjectName(QStringLiteral("graph_area_pub"));
        graph_area_pub->setEnabled(true);

        verticalLayout->addWidget(graph_area_pub);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_8);

        btnExportGraphPub = new QPushButton(pub_tab);
        btnExportGraphPub->setObjectName(QStringLiteral("btnExportGraphPub"));
        btnExportGraphPub->setMinimumSize(QSize(150, 0));

        horizontalLayout_25->addWidget(btnExportGraphPub);


        verticalLayout->addLayout(horizontalLayout_25);


        gridLayout_3->addLayout(verticalLayout, 0, 1, 2, 1);

        tab_widget->addTab(pub_tab, QString());
        grant_tab = new QWidget();
        grant_tab->setObjectName(QStringLiteral("grant_tab"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush5(QColor(0, 85, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        grant_tab->setPalette(palette9);
        grant_tab->setAutoFillBackground(true);
        gridLayout_4 = new QGridLayout(grant_tab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        date_filter_lbl_grnt = new QLabel(grant_tab);
        date_filter_lbl_grnt->setObjectName(QStringLiteral("date_filter_lbl_grnt"));
        date_filter_lbl_grnt->setMinimumSize(QSize(75, 0));
        date_filter_lbl_grnt->setMaximumSize(QSize(75, 16777215));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        date_filter_lbl_grnt->setPalette(palette10);

        horizontalLayout_10->addWidget(date_filter_lbl_grnt);

        start_date_combo_grnt = new QComboBox(grant_tab);
        start_date_combo_grnt->setObjectName(QStringLiteral("start_date_combo_grnt"));

        horizontalLayout_10->addWidget(start_date_combo_grnt);

        end_date_combo_grnt = new QComboBox(grant_tab);
        end_date_combo_grnt->setObjectName(QStringLiteral("end_date_combo_grnt"));
        end_date_combo_grnt->setMinimumSize(QSize(0, 0));

        horizontalLayout_10->addWidget(end_date_combo_grnt);


        verticalLayout_11->addLayout(horizontalLayout_10);

        domain_lbl_grnt = new QLabel(grant_tab);
        domain_lbl_grnt->setObjectName(QStringLiteral("domain_lbl_grnt"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        domain_lbl_grnt->setPalette(palette11);
        domain_lbl_grnt->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(domain_lbl_grnt);

        tree_list_grnt = new QTreeWidget(grant_tab);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        tree_list_grnt->setHeaderItem(__qtreewidgetitem1);
        tree_list_grnt->setObjectName(QStringLiteral("tree_list_grnt"));
        tree_list_grnt->setSortingEnabled(true);

        verticalLayout_11->addWidget(tree_list_grnt);


        gridLayout_4->addLayout(verticalLayout_11, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        btnExportCSVGrant = new QPushButton(grant_tab);
        btnExportCSVGrant->setObjectName(QStringLiteral("btnExportCSVGrant"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnExportCSVGrant->sizePolicy().hasHeightForWidth());
        btnExportCSVGrant->setSizePolicy(sizePolicy1);
        btnExportCSVGrant->setMinimumSize(QSize(150, 0));

        horizontalLayout_12->addWidget(btnExportCSVGrant);


        gridLayout_4->addLayout(horizontalLayout_12, 1, 0, 1, 1);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        graph_lbl_grnt = new QLabel(grant_tab);
        graph_lbl_grnt->setObjectName(QStringLiteral("graph_lbl_grnt"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        graph_lbl_grnt->setPalette(palette12);
        graph_lbl_grnt->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(graph_lbl_grnt);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        name_lbl_grnt = new QLabel(grant_tab);
        name_lbl_grnt->setObjectName(QStringLiteral("name_lbl_grnt"));
        name_lbl_grnt->setMaximumSize(QSize(100, 40));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        name_lbl_grnt->setPalette(palette13);

        horizontalLayout_2->addWidget(name_lbl_grnt);

        name_combo_grnt = new QComboBox(grant_tab);
        name_combo_grnt->setObjectName(QStringLiteral("name_combo_grnt"));

        horizontalLayout_2->addWidget(name_combo_grnt);


        verticalLayout_12->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        type_lbl_grnt = new QLabel(grant_tab);
        type_lbl_grnt->setObjectName(QStringLiteral("type_lbl_grnt"));
        type_lbl_grnt->setMaximumSize(QSize(100, 40));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        type_lbl_grnt->setPalette(palette14);

        horizontalLayout_3->addWidget(type_lbl_grnt);

        type_combo_grnt = new QComboBox(grant_tab);
        type_combo_grnt->setObjectName(QStringLiteral("type_combo_grnt"));

        horizontalLayout_3->addWidget(type_combo_grnt);


        verticalLayout_12->addLayout(horizontalLayout_3);

        graph_area_grnt = new QGraphicsView(grant_tab);
        graph_area_grnt->setObjectName(QStringLiteral("graph_area_grnt"));
        graph_area_grnt->setEnabled(true);

        verticalLayout_12->addWidget(graph_area_grnt);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_7);

        btnExportGraphGrant = new QPushButton(grant_tab);
        btnExportGraphGrant->setObjectName(QStringLiteral("btnExportGraphGrant"));
        sizePolicy1.setHeightForWidth(btnExportGraphGrant->sizePolicy().hasHeightForWidth());
        btnExportGraphGrant->setSizePolicy(sizePolicy1);
        btnExportGraphGrant->setMinimumSize(QSize(150, 0));

        horizontalLayout_24->addWidget(btnExportGraphGrant);


        verticalLayout_12->addLayout(horizontalLayout_24);


        gridLayout_4->addLayout(verticalLayout_12, 0, 1, 2, 1);

        tab_widget->addTab(grant_tab, QString());
        present_tab = new QWidget();
        present_tab->setObjectName(QStringLiteral("present_tab"));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush6(QColor(0, 0, 127, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette15.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette15.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette15.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette15.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette15.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        present_tab->setPalette(palette15);
        present_tab->setAutoFillBackground(true);
        gridLayout_2 = new QGridLayout(present_tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_3);

        btnExportCSVPres = new QPushButton(present_tab);
        btnExportCSVPres->setObjectName(QStringLiteral("btnExportCSVPres"));
        btnExportCSVPres->setMinimumSize(QSize(150, 0));

        horizontalLayout_17->addWidget(btnExportCSVPres);


        gridLayout_2->addLayout(horizontalLayout_17, 1, 0, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        date_filter_lbl_pres = new QLabel(present_tab);
        date_filter_lbl_pres->setObjectName(QStringLiteral("date_filter_lbl_pres"));
        date_filter_lbl_pres->setMinimumSize(QSize(75, 0));
        date_filter_lbl_pres->setMaximumSize(QSize(75, 16777215));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        date_filter_lbl_pres->setPalette(palette16);

        horizontalLayout_8->addWidget(date_filter_lbl_pres);

        start_date_combo_pres = new QComboBox(present_tab);
        start_date_combo_pres->setObjectName(QStringLiteral("start_date_combo_pres"));

        horizontalLayout_8->addWidget(start_date_combo_pres);

        end_date_combo_pres = new QComboBox(present_tab);
        end_date_combo_pres->setObjectName(QStringLiteral("end_date_combo_pres"));
        end_date_combo_pres->setMinimumSize(QSize(0, 0));

        horizontalLayout_8->addWidget(end_date_combo_pres);


        verticalLayout_9->addLayout(horizontalLayout_8);

        domain_lbl_pres = new QLabel(present_tab);
        domain_lbl_pres->setObjectName(QStringLiteral("domain_lbl_pres"));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        domain_lbl_pres->setPalette(palette17);
        domain_lbl_pres->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(domain_lbl_pres);

        tree_list_pres = new QTreeWidget(present_tab);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QStringLiteral("1"));
        tree_list_pres->setHeaderItem(__qtreewidgetitem2);
        tree_list_pres->setObjectName(QStringLiteral("tree_list_pres"));
        tree_list_pres->setSortingEnabled(true);

        verticalLayout_9->addWidget(tree_list_pres);


        gridLayout_2->addLayout(verticalLayout_9, 0, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        graph_lbl_pres = new QLabel(present_tab);
        graph_lbl_pres->setObjectName(QStringLiteral("graph_lbl_pres"));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette18.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette18.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        graph_lbl_pres->setPalette(palette18);
        graph_lbl_pres->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(graph_lbl_pres);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        name_lbl_pres = new QLabel(present_tab);
        name_lbl_pres->setObjectName(QStringLiteral("name_lbl_pres"));
        name_lbl_pres->setMaximumSize(QSize(100, 40));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette19.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette19.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        name_lbl_pres->setPalette(palette19);

        horizontalLayout_4->addWidget(name_lbl_pres);

        name_combo_pres = new QComboBox(present_tab);
        name_combo_pres->setObjectName(QStringLiteral("name_combo_pres"));

        horizontalLayout_4->addWidget(name_combo_pres);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        type_lbl_pres = new QLabel(present_tab);
        type_lbl_pres->setObjectName(QStringLiteral("type_lbl_pres"));
        type_lbl_pres->setMaximumSize(QSize(100, 40));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette20.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette20.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        type_lbl_pres->setPalette(palette20);

        horizontalLayout_5->addWidget(type_lbl_pres);

        type_combo_pres = new QComboBox(present_tab);
        type_combo_pres->setObjectName(QStringLiteral("type_combo_pres"));

        horizontalLayout_5->addWidget(type_combo_pres);


        verticalLayout_7->addLayout(horizontalLayout_5);

        graph_area_pres = new QGraphicsView(present_tab);
        graph_area_pres->setObjectName(QStringLiteral("graph_area_pres"));
        graph_area_pres->setEnabled(true);

        verticalLayout_7->addWidget(graph_area_pres);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_6);

        btnExportGraphPres = new QPushButton(present_tab);
        btnExportGraphPres->setObjectName(QStringLiteral("btnExportGraphPres"));
        btnExportGraphPres->setMinimumSize(QSize(150, 0));

        horizontalLayout_23->addWidget(btnExportGraphPres);


        verticalLayout_7->addLayout(horizontalLayout_23);


        gridLayout_2->addLayout(verticalLayout_7, 0, 1, 2, 1);

        tab_widget->addTab(present_tab, QString());
        teach_tab = new QWidget();
        teach_tab->setObjectName(QStringLiteral("teach_tab"));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush7(QColor(213, 178, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette21.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette21.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette21.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette21.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette21.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        teach_tab->setPalette(palette21);
        teach_tab->setAutoFillBackground(true);
        gridLayout_5 = new QGridLayout(teach_tab);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_4);

        btnExportCSVTeach = new QPushButton(teach_tab);
        btnExportCSVTeach->setObjectName(QStringLiteral("btnExportCSVTeach"));
        btnExportCSVTeach->setMinimumSize(QSize(150, 0));

        horizontalLayout_18->addWidget(btnExportCSVTeach);


        gridLayout_5->addLayout(horizontalLayout_18, 1, 0, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        date_filter_lbl_teach = new QLabel(teach_tab);
        date_filter_lbl_teach->setObjectName(QStringLiteral("date_filter_lbl_teach"));
        date_filter_lbl_teach->setMinimumSize(QSize(75, 0));
        date_filter_lbl_teach->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_9->addWidget(date_filter_lbl_teach);

        start_date_combo_teach = new QComboBox(teach_tab);
        start_date_combo_teach->setObjectName(QStringLiteral("start_date_combo_teach"));

        horizontalLayout_9->addWidget(start_date_combo_teach);

        end_date_combo_teach = new QComboBox(teach_tab);
        end_date_combo_teach->setObjectName(QStringLiteral("end_date_combo_teach"));
        end_date_combo_teach->setMinimumSize(QSize(0, 0));

        horizontalLayout_9->addWidget(end_date_combo_teach);


        verticalLayout_10->addLayout(horizontalLayout_9);

        domain_lbl_teach = new QLabel(teach_tab);
        domain_lbl_teach->setObjectName(QStringLiteral("domain_lbl_teach"));
        domain_lbl_teach->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(domain_lbl_teach);

        tree_list_teach = new QTreeWidget(teach_tab);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setText(0, QStringLiteral("1"));
        tree_list_teach->setHeaderItem(__qtreewidgetitem3);
        tree_list_teach->setObjectName(QStringLiteral("tree_list_teach"));
        tree_list_teach->setSortingEnabled(true);

        verticalLayout_10->addWidget(tree_list_teach);


        gridLayout_5->addLayout(verticalLayout_10, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        graph_lbl_teach = new QLabel(teach_tab);
        graph_lbl_teach->setObjectName(QStringLiteral("graph_lbl_teach"));
        graph_lbl_teach->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(graph_lbl_teach);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        name_lbl_teach = new QLabel(teach_tab);
        name_lbl_teach->setObjectName(QStringLiteral("name_lbl_teach"));
        name_lbl_teach->setMaximumSize(QSize(100, 40));

        horizontalLayout_6->addWidget(name_lbl_teach);

        name_combo_teach = new QComboBox(teach_tab);
        name_combo_teach->setObjectName(QStringLiteral("name_combo_teach"));

        horizontalLayout_6->addWidget(name_combo_teach);


        verticalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        program_lbl_teach = new QLabel(teach_tab);
        program_lbl_teach->setObjectName(QStringLiteral("program_lbl_teach"));
        program_lbl_teach->setMaximumSize(QSize(100, 40));

        horizontalLayout_7->addWidget(program_lbl_teach);

        program_combo_teach = new QComboBox(teach_tab);
        program_combo_teach->setObjectName(QStringLiteral("program_combo_teach"));

        horizontalLayout_7->addWidget(program_combo_teach);


        verticalLayout_8->addLayout(horizontalLayout_7);

        graph_area_teach = new QGraphicsView(teach_tab);
        graph_area_teach->setObjectName(QStringLiteral("graph_area_teach"));
        graph_area_teach->setEnabled(true);

        verticalLayout_8->addWidget(graph_area_teach);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_5);

        btnExportGraphTeach = new QPushButton(teach_tab);
        btnExportGraphTeach->setObjectName(QStringLiteral("btnExportGraphTeach"));
        btnExportGraphTeach->setMinimumSize(QSize(150, 0));

        horizontalLayout_20->addWidget(btnExportGraphTeach);


        verticalLayout_8->addLayout(horizontalLayout_20);


        gridLayout_5->addLayout(verticalLayout_8, 0, 2, 2, 1);

        tab_widget->addTab(teach_tab, QString());

        gridLayout->addWidget(tab_widget, 1, 0, 1, 1);

        AnalyzeCSV->setCentralWidget(centralwidget);

        retranslateUi(AnalyzeCSV);

        tab_widget->setCurrentIndex(3);
        name_combo_grnt->setCurrentIndex(-1);
        name_combo_pres->setCurrentIndex(-1);
        program_combo_teach->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AnalyzeCSV);
    } // setupUi

    void retranslateUi(QMainWindow *AnalyzeCSV)
    {
        AnalyzeCSV->setWindowTitle(QApplication::translate("AnalyzeCSV", "MainWindow", 0));
        load_btn->setText(QApplication::translate("AnalyzeCSV", "LOAD >", 0));
        verify_btn->setText(QApplication::translate("AnalyzeCSV", "VERIFY >", 0));
        analyze_btn->setText(QApplication::translate("AnalyzeCSV", "ANALYZE >", 0));
        date_filter_lbl_pub->setText(QApplication::translate("AnalyzeCSV", "Date Filter:", 0));
        domain_lbl_pub->setText(QString());
        btnExportCSVPub->setText(QApplication::translate("AnalyzeCSV", "Export CSV", 0));
        graph_lbl_pub->setText(QApplication::translate("AnalyzeCSV", "Graph Analytics", 0));
        name_lbl_pub->setText(QApplication::translate("AnalyzeCSV", "Name:", 0));
        type_lbl_pub->setText(QApplication::translate("AnalyzeCSV", "Type:", 0));
        type_combo_pub->clear();
        type_combo_pub->insertItems(0, QStringList()
         << QApplication::translate("AnalyzeCSV", "ALL", 0)
        );
        btnExportGraphPub->setText(QApplication::translate("AnalyzeCSV", "Export Graph", 0));
        tab_widget->setTabText(tab_widget->indexOf(pub_tab), QApplication::translate("AnalyzeCSV", "PUBLICATIONS", 0));
        date_filter_lbl_grnt->setText(QApplication::translate("AnalyzeCSV", "Date Filter:", 0));
        domain_lbl_grnt->setText(QString());
        btnExportCSVGrant->setText(QApplication::translate("AnalyzeCSV", "Export CSV", 0));
        graph_lbl_grnt->setText(QApplication::translate("AnalyzeCSV", "Graph Analytics", 0));
        name_lbl_grnt->setText(QApplication::translate("AnalyzeCSV", "Name:", 0));
        name_combo_grnt->setCurrentText(QString());
        type_lbl_grnt->setText(QApplication::translate("AnalyzeCSV", "Funding Type:", 0));
        type_combo_grnt->clear();
        type_combo_grnt->insertItems(0, QStringList()
         << QApplication::translate("AnalyzeCSV", "ALL", 0)
        );
        btnExportGraphGrant->setText(QApplication::translate("AnalyzeCSV", "Export Graph", 0));
        tab_widget->setTabText(tab_widget->indexOf(grant_tab), QApplication::translate("AnalyzeCSV", "GRANTS", 0));
        btnExportCSVPres->setText(QApplication::translate("AnalyzeCSV", "Export CSV", 0));
        date_filter_lbl_pres->setText(QApplication::translate("AnalyzeCSV", "Date Filter:", 0));
        domain_lbl_pres->setText(QString());
        graph_lbl_pres->setText(QApplication::translate("AnalyzeCSV", "Graph Analytics", 0));
        name_lbl_pres->setText(QApplication::translate("AnalyzeCSV", "Name:", 0));
        type_lbl_pres->setText(QApplication::translate("AnalyzeCSV", "Type:", 0));
        type_combo_pres->clear();
        type_combo_pres->insertItems(0, QStringList()
         << QApplication::translate("AnalyzeCSV", "ALL", 0)
        );
        btnExportGraphPres->setText(QApplication::translate("AnalyzeCSV", "Export Graph", 0));
        tab_widget->setTabText(tab_widget->indexOf(present_tab), QApplication::translate("AnalyzeCSV", "PRESENTATIONS", 0));
        btnExportCSVTeach->setText(QApplication::translate("AnalyzeCSV", "Export CSV", 0));
        date_filter_lbl_teach->setText(QApplication::translate("AnalyzeCSV", "Date Filter:", 0));
        domain_lbl_teach->setText(QString());
        graph_lbl_teach->setText(QApplication::translate("AnalyzeCSV", "Graph Analytics", 0));
        name_lbl_teach->setText(QApplication::translate("AnalyzeCSV", "Name:", 0));
        program_lbl_teach->setText(QApplication::translate("AnalyzeCSV", "Program:", 0));
        program_combo_teach->clear();
        program_combo_teach->insertItems(0, QStringList()
         << QApplication::translate("AnalyzeCSV", "ALL", 0)
        );
        btnExportGraphTeach->setText(QApplication::translate("AnalyzeCSV", "Export Graph", 0));
        tab_widget->setTabText(tab_widget->indexOf(teach_tab), QApplication::translate("AnalyzeCSV", "TEACHING", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeCSV: public Ui_AnalyzeCSV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZE_CSV_H
