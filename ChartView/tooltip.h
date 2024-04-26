#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>
#include <QOpenGLWidget>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QChart;
class QAbstractSeries;
QT_END_NAMESPACE
class ToolTip : public QGraphicsItem
{
public:
    ToolTip(QChart *chart, QAbstractSeries *series);
    void setTextToolTip(const QString &text);
    void setAnchorPoint(QPointF point);
    void updateGeometry();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setSeries(QAbstractSeries *series);
    void setAllValues(bool newAllValues);
protected:
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
signals:
private:
    QString m_text;
    QRectF m_textRect;
    QRectF m_rect;
    QPointF m_anchor;
    QFont m_font;
    QChart *m_chart;
    QAbstractSeries *m_series;
    bool allValues = false;
};

#endif // TOOLTIP_H
