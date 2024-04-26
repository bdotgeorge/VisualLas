#include "linetochart.h"
#include <QtCharts/QChart>
#include <QtGui/QPainter>
#include <QtGui/QCursor>
#include <QtGui/QTextDocument>

LineToChart::LineToChart(QChart *chart, Qt::Orientation typeLine) :
    m_line(new QGraphicsLineItem(chart)),
    m_text(new QGraphicsTextItem(chart)),
    m_chart(chart),
    m_typeLine(typeLine)

{
    m_line->setPen(QPen(Qt::red, 2.0));
    m_line->setZValue(11);
    m_text->setZValue(11);
    m_text->document()->setDocumentMargin(0);
    m_text->setDefaultTextColor(Qt::white);
}

void LineToChart::updatePosition(QPointF position, bool contain)
{
    QLineF line;//(position.x(), m_chart->plotArea().top(), position.x(), m_chart->plotArea().bottom());
    switch (m_typeLine) {
    case Qt::Vertical:
        line.setLine(position.x(), m_chart->plotArea().top(), position.x(), m_chart->plotArea().bottom());
        break;
    default:
        line.setLine(m_chart->plotArea().left(), position.y(), m_chart->plotArea().right(), position.y());
        break;
    }
    m_line->setLine(line);
//    QString xText = QString("%1").arg(m_chart->mapToValue(position).x());
//    m_text->setHtml(QString("<div style='background-color: #ff0000;'>") + xText + "</div>");
//    m_text->setPos(position.x() + 10, position.y() - 15);
    if (contain){
        m_line->show();
//        m_text->show();
    }
    else{
        m_line->hide();
//        m_text->hide();
    }
}
