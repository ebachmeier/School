/********************************************************************************
** Form generated from reading UI file 'analyzetab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZETAB_H
#define UI_ANALYZETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalyzeTab
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbStartYear;
    QComboBox *cmbEndYear;
    QLabel *lblDomain;
    QTreeWidget *treeList;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *AnalyzeTab)
    {
        if (AnalyzeTab->objectName().isEmpty())
            AnalyzeTab->setObjectName(QStringLiteral("AnalyzeTab"));
        AnalyzeTab->resize(1005, 664);
        horizontalLayoutWidget_2 = new QWidget(AnalyzeTab);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 10, 981, 641));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        cmbStartYear = new QComboBox(horizontalLayoutWidget_2);
        cmbStartYear->setObjectName(QStringLiteral("cmbStartYear"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbStartYear->sizePolicy().hasHeightForWidth());
        cmbStartYear->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cmbStartYear);

        cmbEndYear = new QComboBox(horizontalLayoutWidget_2);
        cmbEndYear->setObjectName(QStringLiteral("cmbEndYear"));
        sizePolicy.setHeightForWidth(cmbEndYear->sizePolicy().hasHeightForWidth());
        cmbEndYear->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cmbEndYear);


        verticalLayout->addLayout(horizontalLayout);

        lblDomain = new QLabel(horizontalLayoutWidget_2);
        lblDomain->setObjectName(QStringLiteral("lblDomain"));
        lblDomain->setFont(font);
        lblDomain->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblDomain);

        treeList = new QTreeWidget(horizontalLayoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeList->setHeaderItem(__qtreewidgetitem);
        treeList->setObjectName(QStringLiteral("treeList"));
        treeList->setAlternatingRowColors(true);
        treeList->setSortingEnabled(true);

        verticalLayout->addWidget(treeList);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2);

        comboBox_2 = new QComboBox(horizontalLayoutWidget_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_5->addWidget(comboBox_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        comboBox = new QComboBox(horizontalLayoutWidget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        graphicsView = new QGraphicsView(horizontalLayoutWidget_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_2->addWidget(graphicsView);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(AnalyzeTab);

        QMetaObject::connectSlotsByName(AnalyzeTab);
    } // setupUi

    void retranslateUi(QWidget *AnalyzeTab)
    {
        AnalyzeTab->setWindowTitle(QApplication::translate("AnalyzeTab", "Form", 0));
        label->setText(QApplication::translate("AnalyzeTab", "Date Filter: ", 0));
        lblDomain->setText(QApplication::translate("AnalyzeTab", "DomainNameGoesHere", 0));
        label_4->setText(QApplication::translate("AnalyzeTab", "Graph Analytics", 0));
        label_2->setText(QApplication::translate("AnalyzeTab", "TextLabel", 0));
        label_3->setText(QApplication::translate("AnalyzeTab", "Type:", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeTab: public Ui_AnalyzeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZETAB_H
