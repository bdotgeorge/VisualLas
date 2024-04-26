#ifndef SETTINGEXTSERIES_H
#define SETTINGEXTSERIES_H

#include "extendedseries.h"
#include <QLegendMarker>
#include <QValueAxis>
#include <QDialog>

namespace Ui {
class SettingExtSeries;
}

class SettingExtSeries : public QDialog
{
    Q_OBJECT

public:
    explicit SettingExtSeries(QLegendMarker *marker,
                              ExtendedSeries *series,
                              QValueAxis *axis, QWidget *parent = nullptr);
    ~SettingExtSeries();
public slots:
    void apply();
private slots:
    void setColorLine();
    void visibleChangeAdvSettings();
    void onOffSeries();
    void shiftAxisSeries();
    bool leftShift(float &shift);
    bool rightShift(float &shift);
    bool resetShiftAxisSeries();
private:
    void initStartingConnecting();
    void startSettings();
    Ui::SettingExtSeries *ui;
    QLegendMarker *m_marker;
    ExtendedSeries *m_series;
    QValueAxis *m_axis;
    QColor m_colorLine;
    float m_Ymax;
    float m_Ymin;
    QString m_unitName;
    QString m_nameLine;
    int m_symbAftComma;
    int m_bias;
    QString stylebtn;
};

#endif // SETTINGEXTSERIES_H
