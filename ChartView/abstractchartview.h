#ifndef ABSTRACTCHARTVIEW_H
#define ABSTRACTCHARTVIEW_H

#include <QGraphicsView>
#include <QChart>
#include <QtCharts/QChartGlobal>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QGraphicsSimpleTextItem>
#include <QLabel>
#include "extendedseries.h"
struct SeriesData
{
    SeriesData(uint &inCountData, QStringList &inNameSeries, QStringList &inNameUnit, QList<QList<QPointF>> &inPointsSeries) :
        countData(inCountData), nameSeries(inNameSeries), nameUnit(inNameUnit), pointsSeries(inPointsSeries)
    {
        Q_ASSERT(countData == nameSeries.size() && countData == nameUnit.size() && countData == pointsSeries.size());
    }
    uint countData = 0;
    QStringList nameSeries;
    QStringList nameUnit;
    QList<QList<QPointF>> pointsSeries;
};

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
class QChart;
QT_END_NAMESPACE
class AbstractChartView : public QGraphicsView
{
public:
    explicit AbstractChartView(QWidget *parent = nullptr);
    virtual ~AbstractChartView() = default;
    virtual SeriesData allSeriesData() const = 0;
    virtual SeriesData availabelSeriesData() const = 0;
private slots:
    virtual void addLineToChart(ExtendedSeries *series, const bool axisXtime = true) = 0;
};

#endif // ABSTRACTCHARTVIEW_H
