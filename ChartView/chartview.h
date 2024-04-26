#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include "abstractchartview.h"
#include "tooltip.h"
#include "linetochart.h"

class ChartView : public AbstractChartView
{
    Q_OBJECT
public:
    explicit ChartView(QList<ExtendedSeries *> seriesLst, const bool axisXtime = true, QWidget *parent = nullptr);
    explicit ChartView(ExtendedSeries *series, const bool axisXtime = true, QWidget *parent = nullptr);
    ~ChartView() override;
    QString titelChart() const;
    SeriesData allSeriesData() const override;
    SeriesData availabelSeriesData() const override;
    QList<QAbstractSeries *> availableSeries();
    QList<QAbstractSeries *> allSeries();
    static bool sortQPointFByX(const QPointF &a, const QPointF &b);
public slots:
    void stretchChart(qreal value);
    void chartShift(int direction);
    void autoScale();
    void setLinesToChart(QList<ExtendedSeries *> &seriesLst, const bool &axisXtime = true);
    void setLineToChart(ExtendedSeries *series);
    void setTitel(const QString &titel);
signals:
    void scrollBarChangePosition(unsigned int value);
    void scrollBarMaxValue(int max);
    void stepScrollBarChange(int value);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *keyEvent) override;
private slots:
    void addLineToChart(ExtendedSeries *series, const bool axisXtime) override;
    void startingSettings();
    void connectMarket();
    void settingsCurves();
    void toolTipPoint(QPointF point, bool state);
    void curvesDataShow(const QPointF &p);
    void legendSetting();
    bool containtPositionSeries(QPointF p);
    int containtPositionSeries(bool &end, const quint64 &key);//overload
    QString currentDataValue(const QPointF &p);
    void checkSeriesName(QList<QAbstractSeries *> currnetSeries, QList<ExtendedSeries *> &addedSeries);
private:
    QAbstractAxis *m_xAxis = nullptr;
    QChart *chart = nullptr;
    ToolTip *m_prompt = nullptr;
    QGraphicsSimpleTextItem *m_currentXValue = nullptr;
    QGraphicsSimpleTextItem *m_currentData = nullptr;
    ToolTip *m_currentValue = nullptr;
    QLabel *m_infoLabel = nullptr;
    LineToChart *m_line = nullptr;
};
#endif // CHARTVIEW_H
