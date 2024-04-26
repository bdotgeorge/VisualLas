/********************************************************************************
** Form generated from reading UI file 'settingextseries.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGEXTSERIES_H
#define UI_SETTINGEXTSERIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingExtSeries
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QGroupBox *advSettingsGroupBox;
    QGridLayout *gridLayout_3;
    QLineEdit *numDecPlacesLineEdit;
    QLineEdit *depthOffsetLineEdit;
    QLabel *shiftLbl;
    QLabel *valueShiftLbl;
    QPushButton *resetShiftBtn;
    QLabel *shiftAxisLbl;
    QLineEdit *unitLineEdit;
    QLineEdit *shiftAxisLineEdit;
    QLabel *depthOffsetLbl;
    QLabel *numDecPlacesLbl;
    QPushButton *executeShiftAxisBtn;
    QLabel *unitLbl;
    QLabel *nameChangeLbl;
    QLineEdit *nameChangeLineEdit;
    QGroupBox *settingsGroupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *seriesOnOffCheckBox;
    QPushButton *colorBtn;
    QLineEdit *minLineEdit;
    QLabel *minLbl;
    QLabel *nameLbl;
    QCheckBox *advSetCcheckBox;
    QLineEdit *maxLineEdit;
    QLabel *nameSeriesLbl;
    QLabel *maxLbl;
    QSpacerItem *verticalSpacer;
    QPushButton *applyBtn;

    void setupUi(QDialog *SettingExtSeries)
    {
        if (SettingExtSeries->objectName().isEmpty())
            SettingExtSeries->setObjectName(QString::fromUtf8("SettingExtSeries"));
        SettingExtSeries->resize(374, 508);
        verticalLayout = new QVBoxLayout(SettingExtSeries);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        advSettingsGroupBox = new QGroupBox(SettingExtSeries);
        advSettingsGroupBox->setObjectName(QString::fromUtf8("advSettingsGroupBox"));
        gridLayout_3 = new QGridLayout(advSettingsGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        numDecPlacesLineEdit = new QLineEdit(advSettingsGroupBox);
        numDecPlacesLineEdit->setObjectName(QString::fromUtf8("numDecPlacesLineEdit"));

        gridLayout_3->addWidget(numDecPlacesLineEdit, 2, 1, 1, 1);

        depthOffsetLineEdit = new QLineEdit(advSettingsGroupBox);
        depthOffsetLineEdit->setObjectName(QString::fromUtf8("depthOffsetLineEdit"));

        gridLayout_3->addWidget(depthOffsetLineEdit, 3, 1, 1, 1);

        shiftLbl = new QLabel(advSettingsGroupBox);
        shiftLbl->setObjectName(QString::fromUtf8("shiftLbl"));
        shiftLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(shiftLbl, 5, 0, 1, 1);

        valueShiftLbl = new QLabel(advSettingsGroupBox);
        valueShiftLbl->setObjectName(QString::fromUtf8("valueShiftLbl"));

        gridLayout_3->addWidget(valueShiftLbl, 5, 1, 1, 1);

        resetShiftBtn = new QPushButton(advSettingsGroupBox);
        resetShiftBtn->setObjectName(QString::fromUtf8("resetShiftBtn"));

        gridLayout_3->addWidget(resetShiftBtn, 7, 1, 1, 1);

        shiftAxisLbl = new QLabel(advSettingsGroupBox);
        shiftAxisLbl->setObjectName(QString::fromUtf8("shiftAxisLbl"));
        shiftAxisLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(shiftAxisLbl, 4, 0, 1, 1);

        unitLineEdit = new QLineEdit(advSettingsGroupBox);
        unitLineEdit->setObjectName(QString::fromUtf8("unitLineEdit"));

        gridLayout_3->addWidget(unitLineEdit, 1, 1, 1, 1);

        shiftAxisLineEdit = new QLineEdit(advSettingsGroupBox);
        shiftAxisLineEdit->setObjectName(QString::fromUtf8("shiftAxisLineEdit"));

        gridLayout_3->addWidget(shiftAxisLineEdit, 4, 1, 1, 1);

        depthOffsetLbl = new QLabel(advSettingsGroupBox);
        depthOffsetLbl->setObjectName(QString::fromUtf8("depthOffsetLbl"));
        depthOffsetLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(depthOffsetLbl, 3, 0, 1, 1);

        numDecPlacesLbl = new QLabel(advSettingsGroupBox);
        numDecPlacesLbl->setObjectName(QString::fromUtf8("numDecPlacesLbl"));
        numDecPlacesLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(numDecPlacesLbl, 2, 0, 1, 1);

        executeShiftAxisBtn = new QPushButton(advSettingsGroupBox);
        executeShiftAxisBtn->setObjectName(QString::fromUtf8("executeShiftAxisBtn"));

        gridLayout_3->addWidget(executeShiftAxisBtn, 6, 1, 1, 1);

        unitLbl = new QLabel(advSettingsGroupBox);
        unitLbl->setObjectName(QString::fromUtf8("unitLbl"));
        unitLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(unitLbl, 1, 0, 1, 1);

        nameChangeLbl = new QLabel(advSettingsGroupBox);
        nameChangeLbl->setObjectName(QString::fromUtf8("nameChangeLbl"));
        nameChangeLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(nameChangeLbl, 0, 0, 1, 1);

        nameChangeLineEdit = new QLineEdit(advSettingsGroupBox);
        nameChangeLineEdit->setObjectName(QString::fromUtf8("nameChangeLineEdit"));

        gridLayout_3->addWidget(nameChangeLineEdit, 0, 1, 1, 1);


        gridLayout->addWidget(advSettingsGroupBox, 2, 0, 1, 1);

        settingsGroupBox = new QGroupBox(SettingExtSeries);
        settingsGroupBox->setObjectName(QString::fromUtf8("settingsGroupBox"));
        gridLayout_2 = new QGridLayout(settingsGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        seriesOnOffCheckBox = new QCheckBox(settingsGroupBox);
        seriesOnOffCheckBox->setObjectName(QString::fromUtf8("seriesOnOffCheckBox"));

        gridLayout_2->addWidget(seriesOnOffCheckBox, 4, 0, 1, 1);

        colorBtn = new QPushButton(settingsGroupBox);
        colorBtn->setObjectName(QString::fromUtf8("colorBtn"));

        gridLayout_2->addWidget(colorBtn, 4, 2, 1, 1);

        minLineEdit = new QLineEdit(settingsGroupBox);
        minLineEdit->setObjectName(QString::fromUtf8("minLineEdit"));

        gridLayout_2->addWidget(minLineEdit, 2, 2, 1, 1);

        minLbl = new QLabel(settingsGroupBox);
        minLbl->setObjectName(QString::fromUtf8("minLbl"));
        minLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(minLbl, 2, 0, 1, 1);

        nameLbl = new QLabel(settingsGroupBox);
        nameLbl->setObjectName(QString::fromUtf8("nameLbl"));
        nameLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(nameLbl, 0, 0, 1, 1);

        advSetCcheckBox = new QCheckBox(settingsGroupBox);
        advSetCcheckBox->setObjectName(QString::fromUtf8("advSetCcheckBox"));

        gridLayout_2->addWidget(advSetCcheckBox, 5, 0, 1, 1);

        maxLineEdit = new QLineEdit(settingsGroupBox);
        maxLineEdit->setObjectName(QString::fromUtf8("maxLineEdit"));

        gridLayout_2->addWidget(maxLineEdit, 1, 2, 1, 1);

        nameSeriesLbl = new QLabel(settingsGroupBox);
        nameSeriesLbl->setObjectName(QString::fromUtf8("nameSeriesLbl"));

        gridLayout_2->addWidget(nameSeriesLbl, 0, 2, 1, 1);

        maxLbl = new QLabel(settingsGroupBox);
        maxLbl->setObjectName(QString::fromUtf8("maxLbl"));
        maxLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(maxLbl, 1, 0, 1, 1);


        gridLayout->addWidget(settingsGroupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        applyBtn = new QPushButton(SettingExtSeries);
        applyBtn->setObjectName(QString::fromUtf8("applyBtn"));

        verticalLayout->addWidget(applyBtn);


        retranslateUi(SettingExtSeries);

        QMetaObject::connectSlotsByName(SettingExtSeries);
    } // setupUi

    void retranslateUi(QDialog *SettingExtSeries)
    {
        SettingExtSeries->setWindowTitle(QCoreApplication::translate("SettingExtSeries", "Settings curves", nullptr));
        advSettingsGroupBox->setTitle(QCoreApplication::translate("SettingExtSeries", "Advanced settings", nullptr));
        shiftLbl->setText(QCoreApplication::translate("SettingExtSeries", "Shift:", nullptr));
        valueShiftLbl->setText(QString());
        resetShiftBtn->setText(QCoreApplication::translate("SettingExtSeries", "Reset shift", nullptr));
        shiftAxisLbl->setText(QCoreApplication::translate("SettingExtSeries", "Shift along the time axis:", nullptr));
        depthOffsetLbl->setText(QCoreApplication::translate("SettingExtSeries", "Depth offset, cm:", nullptr));
        numDecPlacesLbl->setText(QCoreApplication::translate("SettingExtSeries", "Number of decimal places:", nullptr));
        executeShiftAxisBtn->setText(QCoreApplication::translate("SettingExtSeries", "Execute", nullptr));
        unitLbl->setText(QCoreApplication::translate("SettingExtSeries", "Unit:", nullptr));
        nameChangeLbl->setText(QCoreApplication::translate("SettingExtSeries", "Name curve:", nullptr));
        settingsGroupBox->setTitle(QCoreApplication::translate("SettingExtSeries", "Settings", nullptr));
        seriesOnOffCheckBox->setText(QCoreApplication::translate("SettingExtSeries", "Visibility curve", nullptr));
        colorBtn->setText(QCoreApplication::translate("SettingExtSeries", "Color curve", nullptr));
        minLbl->setText(QCoreApplication::translate("SettingExtSeries", "min:", nullptr));
        nameLbl->setText(QCoreApplication::translate("SettingExtSeries", "Name:", nullptr));
        advSetCcheckBox->setText(QCoreApplication::translate("SettingExtSeries", "Advanced settings", nullptr));
        nameSeriesLbl->setText(QString());
        maxLbl->setText(QCoreApplication::translate("SettingExtSeries", "max:", nullptr));
        applyBtn->setText(QCoreApplication::translate("SettingExtSeries", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingExtSeries: public Ui_SettingExtSeries {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGEXTSERIES_H
