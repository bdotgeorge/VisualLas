#include "tooltip.h"

#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>
#include <QDebug>

ToolTip::ToolTip(QChart *chart, QAbstractSeries *series):
        QGraphicsItem(chart),
        m_chart(chart),
        m_series(series)
{

}

void ToolTip::setTextToolTip(const QString &text)
{
    m_text = text;
    QFontMetrics metrics(m_font);
    m_textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, m_text);
    m_textRect.translate(5, 5);
    prepareGeometryChange();
    m_rect = m_textRect.adjusted(-5, -5, 5, 5);
}

void ToolTip::setAnchorPoint(QPointF point)
{
    m_anchor = point;
}

void ToolTip::updateGeometry()
{
    prepareGeometryChange();
    setPos(m_chart->mapToPosition(m_anchor, m_series) + QPoint(10, -50));
}

QRectF ToolTip::boundingRect() const
{
    QPointF anchor = mapFromParent(m_chart->mapToPosition(m_anchor, m_series));
    QRectF rect;
    rect.setLeft(qMin(m_rect.left(), anchor.x()));
    rect.setRight(qMax(m_rect.right(), anchor.x()));
    rect.setTop(qMin(m_rect.top(), anchor.y()));
    rect.setBottom(qMax(m_rect.bottom(), anchor.y()));
    return rect;
}

void ToolTip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPainterPath path;
    path.addRoundedRect(m_rect, 5, 5);
    QPointF anchor = mapFromParent(m_chart->mapToPosition(m_anchor, m_series));
    if(allValues) anchor = mapFromParent(m_chart->mapToPosition(m_anchor));
    if (!m_rect.contains(anchor) && !m_anchor.isNull()) {
        QPointF point1, point2;

        // установить положение точки привязки по отношению к m_rect
        bool above = anchor.y() <= m_rect.top();
        bool aboveCenter = anchor.y() > m_rect.top() && anchor.y() <= m_rect.center().y();
        bool belowCenter = anchor.y() > m_rect.center().y() && anchor.y() <= m_rect.bottom();
        bool below = anchor.y() > m_rect.bottom();

        bool onLeft = anchor.x() <= m_rect.left();
        bool leftOfCenter = anchor.x() > m_rect.left() && anchor.x() <= m_rect.center().x();
        bool rightOfCenter = anchor.x() > m_rect.center().x() && anchor.x() <= m_rect.right();
        bool onRight = anchor.x() > m_rect.right();

        // получить ближайший угол m_rect
        qreal x = (onRight + rightOfCenter) * m_rect.width();
        qreal y = (below + belowCenter) * m_rect.height();
        bool cornerCase = (above && onLeft) || (above && onRight) || (below && onLeft) || (below && onRight);
        bool vertical = qAbs(anchor.x() - x) > qAbs(anchor.y() - y);

        qreal x1 = x + leftOfCenter * 10 - rightOfCenter * 20 + cornerCase * !vertical * (onLeft * 10 - onRight * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20 + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftOfCenter * 20 - rightOfCenter * 10 + cornerCase * !vertical * (onLeft * 20 - onRight * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10 + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        if(!allValues){
            path.lineTo(anchor);
            path.lineTo(point2);
        }
        path = path.simplified();
    }
    //painter->beginNativePainting();
    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->drawText(m_textRect, m_text);
    //painter->endNativePainting();
}

void ToolTip::setSeries(QAbstractSeries *series)
{
    m_series = series;
}

void ToolTip::setAllValues(bool newAllValues)
{
    allValues = newAllValues;
}

//void ToolTip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    if (event->buttons() & Qt::LeftButton && allValues){
//        setPos(m_chart->mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
//        event->setAccepted(true);
//    } else {
//        event->setAccepted(false);
//    }
//}
