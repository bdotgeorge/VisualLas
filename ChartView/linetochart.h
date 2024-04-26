#ifndef LINETOCHART_H
#define LINETOCHART_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtCharts/QScatterSeries>

class LineToChart
{
public:
    LineToChart(QChart *chart, Qt::Orientation typeLine);
    void updatePosition(QPointF position, bool contain);
private:
    QGraphicsLineItem *m_line = nullptr;
    QGraphicsTextItem *m_text = nullptr;
    QChart *m_chart = nullptr;
    Qt::Orientation m_typeLine;
};

#endif // LINETOCHART_H
