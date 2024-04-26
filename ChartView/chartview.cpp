#include "chartview.h"
#include "settingextseries.h"
#include <QDateTime>
#include <QLegendMarker>
#include <QPushButton>

ChartView::ChartView(QList<ExtendedSeries *> seriesLst, const bool axisXtime, QWidget *parent) : AbstractChartView(parent)
{
    Q_ASSERT_X(seriesLst.size() != 0, "ChartView", "series is nullptr");
    startingSettings();
    setLinesToChart(seriesLst, axisXtime);
}

ChartView::ChartView(ExtendedSeries *series, const bool axisXtime, QWidget *parent)
{
    Q_ASSERT_X(series, "ChartView", "series is nullptr");
    QList<ExtendedSeries *>seriesList = {series};
    ChartView(seriesList, axisXtime, parent);
}

ChartView::~ChartView()
{
    delete m_prompt;
    chart->removeAllSeries();
    delete m_xAxis;
    delete m_currentXValue;
    delete m_currentData;
    delete m_currentValue;
    delete m_line;
    delete chart;
}

void ChartView::setLinesToChart(QList<ExtendedSeries *> &seriesLst, const bool &axisXtime)
{
    if(seriesLst.empty()) return;
    foreach (auto s, seriesLst) {
        addLineToChart(s, axisXtime);
    }
    if(m_infoLabel != nullptr){
        auto s = seriesLst.constFirst();
        if(s->points().size() > 1) {
            switch (m_xAxis->type()) {
            case QAbstractAxis::AxisTypeDateTime:
                m_infoLabel->setText(QStringLiteral("%1 %2\n:%3 %4\n%5 %6")
                                         .arg(tr("Begin recording:")
                                                  .arg(QDateTime::fromMSecsSinceEpoch(s->points().constFirst().x()).toString("hh:mm:ss   dd.MM.yyyy"))
                                                  .arg(tr("End recording:"))
                                                  .arg(QDateTime::fromMSecsSinceEpoch(s->points().constLast().x()).toString("hh:mm:ss   dd.MM.yyyy"))
                                                  .arg(tr("Measurements:"))
                                                  .arg((QString::number(s->points().size())))));
                break;
            case QAbstractAxis::AxisTypeValue:
                m_infoLabel->setText(QStringLiteral("%1 %2\n:%3 %4\n%5 %6")
                                         .arg(tr("Begin recording:")
                                                  .arg(QString::number(s->points().constFirst().x()))
                                                  .arg(tr("End recording:"))
                                                  .arg(QString::number(s->points().constLast().x()))
                                                  .arg(tr("Measurements:"))
                                                  .arg((QString::number(s->points().size())))));
                break;
            default:
                break;
            }
        }
        else{
            m_infoLabel->setText(QStringLiteral("%1 %2\n:%3 %4\n%5 %6")
                                     .arg(tr("Begin recording:")
                                              .arg(tr("UNKNOW"))
                                              .arg(tr("End recording:"))
                                              .arg(tr("UNKNOW"))
                                              .arg(tr("Measurements:"))
                                              .arg(tr("UNKNOW"))));
        }
        m_infoLabel->adjustSize();
    }
    connectMarket();
}

void ChartView::setLineToChart(ExtendedSeries *series)
{
    QList<ExtendedSeries *> lines = {series};
    setLinesToChart(lines);
}

void ChartView::addLineToChart(ExtendedSeries *series, const bool axisXtime)
{
    if(series == nullptr) return;
    if(m_xAxis == nullptr){
        if(axisXtime) m_xAxis = new QDateTimeAxis(chart);
        else m_xAxis = new QValueAxis(chart);
        m_xAxis->setObjectName("Axis X");
        switch (m_xAxis->type()) {
        case QAbstractAxis::AxisTypeDateTime:
        {
            QDateTimeAxis *xTime = qobject_cast<QDateTimeAxis*>(m_xAxis);
            xTime->setTickCount(11);
            xTime->setFormat("hh:mm:ss");
        }
            break;
        case QAbstractAxis::AxisTypeValue:
        {
            QValueAxis *xValue = qobject_cast<QValueAxis*>(m_xAxis);
            xValue->setTickCount(10);
            m_currentXValue->setText(tr("X: "));
        }
            break;
        default:
            break;
        }
        chart->addAxis(m_xAxis, Qt::AlignBottom);
    }
    series->setParent(chart);
    series->setObjectName("series " + series->nameLine());
    series->setMarkerSize(5);
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setParent(series);
    yAxis->setObjectName("axis " + series->nameLine());
    yAxis->setTickCount(11);
    chart->addAxis(yAxis,  Qt::AlignLeft);
    chart->addSeries(series);
    yAxis->setTitleText(QStringLiteral("<span style=\" color:%1;\">%2</span>").arg(series->color().name()).arg(series->name()));
    yAxis->setLabelsAngle(270);
    yAxis->setLabelsColor(series->color());
    yAxis->setLinePenColor(series->color());
    yAxis->setLabelFormat("%.2f");
    series->attachAxis(m_xAxis);
    series->attachAxis(yAxis);
    connect(series, &ExtendedSeries::hovered,
            this, &ChartView::toolTipPoint);
    if((yAxis->max() - yAxis->min()) < 0.5){
        yAxis->setRange(yAxis->min(), yAxis->max() + 10);
    }
}

void ChartView::startingSettings()
{
    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing, true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chart = new QChart();
    chart->setParent(this);
    legendSetting();
    chart->setAcceptHoverEvents(true);
    chart->setAnimationOptions(QChart::AllAnimations);
    scene()->addItem(chart);
    this->setMouseTracking(true);
    m_currentXValue = new QGraphicsSimpleTextItem(chart);
    m_currentXValue->setPos(chart->size().width() / 2, chart->size().height() - 20);
    m_currentXValue->setText(tr("Time: "));
    m_currentData = new QGraphicsSimpleTextItem(chart);
    m_currentData->hide();
    m_line = new LineToChart(chart, Qt::Vertical);
}

void ChartView::setTitel(const QString &titel)
{
    chart->setTitle(titel);
}

QString ChartView::titelChart() const
{
    return chart->title();
}

void ChartView::stretchChart(qreal value)
{
    qreal zoomValue = 1;
    QDateTimeAxis *xTime = nullptr;
    QValueAxis *xValue = nullptr;
    switch (m_xAxis->type()) {
    case QAbstractAxis::AxisTypeDateTime:
        xTime = qobject_cast<QDateTimeAxis*>(m_xAxis);
        zoomValue = chart->plotArea().width() / xTime->tickCount();
        break;
    case QAbstractAxis::AxisTypeValue:
        xValue = qobject_cast<QValueAxis*>(m_xAxis);
        zoomValue = chart->plotArea().width() / xValue->tickCount();
        break;
    default:
        break;
    }
    value = (value > 0) ? zoomValue : zoomValue - (zoomValue * 2);
    qreal mFactor = 1.0;
    mFactor *=  value > 0 ? 0.5 : 2;
    QRectF rect = chart->plotArea();
    qreal c = chart->plotArea().left();
    rect.setWidth(mFactor * rect.width());
    rect.moveLeft(c);
    chart->zoomIn(rect);
    chart->update(chart->plotArea());
    if(xTime) emit stepScrollBarChange(xTime->max().toSecsSinceEpoch() - xTime->min().toSecsSinceEpoch());
    else emit stepScrollBarChange(xValue->max() - xValue->min());
}

void ChartView::chartShift(int direction)
{
    switch (m_xAxis->type()) {
    case QAbstractAxis::AxisTypeDateTime:
    {
        QDateTimeAxis *xTime = qobject_cast<QDateTimeAxis*>(m_xAxis);
        QDateTime start = QDateTime::fromMSecsSinceEpoch(qobject_cast<QLineSeries*>(chart->series().first())->points().first().x());
        qint64 nextPosition = start.toSecsSinceEpoch() + direction;
        qreal distance = chart->plotArea().width() / 2;
        if (nextPosition == xTime->min().toSecsSinceEpoch()) return;
        else if (nextPosition > xTime->min().toSecsSinceEpoch()) chart->scroll(distance, 0);
        else chart->scroll(-distance, 0);
        if(xTime->min().toSecsSinceEpoch() < start.toSecsSinceEpoch()) m_xAxis->setMin(start);
        chart->update(chart->plotArea());
        emit scrollBarChangePosition(xTime->min().toSecsSinceEpoch() - start.toSecsSinceEpoch());
    }
        break;
    case QAbstractAxis::AxisTypeValue:
    {
        chart->scroll(direction, 0);
        chart->update(chart->plotArea());
    }
        break;
    default:
        break;
    }
}

void ChartView::autoScale()
{
    auto s = chart->series();
    auto a = chart->axes(Qt::Vertical);
    if(s.isEmpty() && a.isEmpty()) return;
    if(chart->isZoomed()){
        chart->zoomReset();
        QDateTime start;
        qreal min = 1;
        switch (m_xAxis->type()) {
        case QAbstractAxis::AxisTypeDateTime:
        {
            QDateTimeAxis *xTime = qobject_cast<QDateTimeAxis*>(m_xAxis);
            start = QDateTime::fromMSecsSinceEpoch(qobject_cast<QLineSeries*>(s.first())->points().first().x());
            if(start != xTime->min())m_xAxis->setMin(start);
            emit scrollBarChangePosition(0);
            emit stepScrollBarChange(xTime->max().toSecsSinceEpoch() - xTime->min().toSecsSinceEpoch());
        }
            break;
        case QAbstractAxis::AxisTypeValue:
        {
            QValueAxis *xValue = qobject_cast<QValueAxis*>(m_xAxis);
            min = qobject_cast<QLineSeries*>(s.first())->points().first().x();
            if(min != xValue->min()) xValue->setMin(min);
            emit scrollBarChangePosition(0);
            emit stepScrollBarChange(xValue->max() - xValue->min());
        }
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < s.size() && a.size(); ++i){
        auto castSeries  = qobject_cast<QLineSeries*>(s.at(i));
        QList<QPointF> poitsSeries = castSeries->points();
        qreal max = INT_MIN;//poitsSeries.first().y();
        qreal min = INT_MAX;
        for (int j = 0; j < castSeries->points().size(); ++j){
            if(max < poitsSeries.at(j).y()) max = poitsSeries.at(j).y();
            if(min > poitsSeries.at(j).y()) min = poitsSeries.at(j).y();
        }
        if(min == max) max += 1;
        a.at(i)->setRange(min, max);
    }
    chart->update(chart->plotArea());
}

QList<QAbstractSeries *> ChartView::availableSeries()
{
    QList<QAbstractSeries *> visibleSeries;
    const auto seriesList =  chart->series();
    foreach (auto s, seriesList) if(s->isVisible()) visibleSeries.append(s);
    return visibleSeries;
}

QList<QAbstractSeries *> ChartView::allSeries()
{
    return chart->series();
}

void ChartView::connectMarket()
{
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        disconnect(marker, &QLegendMarker::clicked,
                   this, &ChartView::settingsCurves);
        connect(marker, &QLegendMarker::clicked, this, &ChartView::settingsCurves);
    }
}

void ChartView::settingsCurves()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    ExtendedSeries *s = static_cast<ExtendedSeries*>(marker->series());
    QValueAxis *axy = nullptr;
    Q_ASSERT(marker);
    Q_ASSERT(s);
    QList<QAbstractAxis *> axis = s->attachedAxes();
    foreach (auto a, axis) {
        if(a->type() != QAbstractAxis::AxisTypeDateTime){
            axy = qobject_cast<QValueAxis*>(a);
            Q_ASSERT(axy);
        }
    }
    SettingExtSeries *sett = new SettingExtSeries(marker, s, axy, this);
    connect(sett, &SettingExtSeries::rejected, sett, &SettingExtSeries::deleteLater);
}

bool ChartView::containtPositionSeries(QPointF p)
{
    auto s = static_cast<ExtendedSeries*>(chart->series().first());
    QList<QPointF> point = s->points();
    int left = 0;
    int right = point.size() - 1;
    int mid = 0;
    quint64 key = (p.x() / 1000) * 1000;//сбросить милисекунды до 0
    bool contain = false;
    while(!contain && left <= right){//binary search
        mid = (left + right) / 2;
        if((quint64)point.at(mid).x() == key) contain = true;
        else if((quint64)point.at(mid).x() > (quint64)p.x()) right = mid - 1;
        else left = mid + 1;
    }
    if(!contain){
        int start = std::min(left, right);
        int size = std::max(left, right);
        for (int i = start; i <= size && i < point.size(); ++i){
            if(point.at(i).x() == key){
                contain = true;
                break;
            }
        }
    }
    return contain;
}

int ChartView::containtPositionSeries(bool &end, const quint64 &key)
{
    auto s = static_cast<ExtendedSeries*>(chart->series().constFirst());
    QList<QPointF> point = s->points();
    int left = 0;
    int right = point.size() - 1;
    int mid = 0;
    while(!end && left <= right){//binary search
        mid = (left + right) / 2;
        if((quint64)point.at(mid).x() == key) end = true;
        else if((quint64)point.at(mid).x() > key) right = mid - 1;
        else left = mid + 1;
    }
    if(!end){
        int start = std::min(left, right);
        int size = std::max(left, right);
        for (int i = std::max(0, start - 2); i <= size && i < point.size(); ++i){
            if(point.at(i).x() == key){
                end = true;
                mid = i;
                break;
            }
        }
    }
    return mid;
}

void ChartView::checkSeriesName(QList<QAbstractSeries *> currnetSeries, QList<ExtendedSeries *> &addedSeries)
{
    if(currnetSeries.isEmpty() || addedSeries.isEmpty()) return;
    foreach (QAbstractSeries *cS, currnetSeries) {
        foreach (ExtendedSeries *aS, addedSeries) {
            if(cS->name() == aS->name()){
                aS->setName(aS->name() + "*");
            }
        }
    }
}

SeriesData ChartView::allSeriesData() const
{
    auto series = chart->series();
    uint countData = series.size(), i = 0;
    QStringList nameSeries;
    nameSeries.resize(countData);
    QStringList nameUnit;
    nameUnit.resize(countData);
    QList<QList<QPointF>> pointsSeries;
    pointsSeries.resize(countData);
    for(auto pS : series){
        ExtendedSeries *s = static_cast<ExtendedSeries*>(pS);
        nameSeries[i] = s->nameLine();
        nameUnit[i] = s->unitName();
        pointsSeries[i] = s->points();
        i++;
    }
    return SeriesData(countData, nameSeries, nameUnit, pointsSeries);
}

SeriesData ChartView::availabelSeriesData() const
{
    auto series = chart->series();
    QStringList nameSeries;
    QStringList nameUnit;
    QList<QList<QPointF>> pointsSeries;
    for(auto pS : series){
        if(pS->isVisible()){
            ExtendedSeries *s = static_cast<ExtendedSeries*>(pS);
            nameSeries.append(s->nameLine());
            nameUnit.append(s->unitName());
            pointsSeries.append(s->points());
        }
    }
    uint countData = nameSeries.size();
    return SeriesData(countData, nameSeries, nameUnit, pointsSeries);
}

void ChartView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        chart->resize(event->size());
        m_currentXValue->setPos(chart->size().width() / 2, chart->size().height() - 20);
        chart->update(chart->plotArea());
    }
    QGraphicsView::resizeEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if(chart->plotArea().contains(event->pos())){
        QPointF point = chart->mapToValue(event->pos());
        switch (m_xAxis->type()) {
        case QAbstractAxis::AxisTypeDateTime:
            m_currentXValue->setText(QStringLiteral("%1 %2")
                                         .arg(tr("Time:"))
                                         .arg(QDateTime::fromMSecsSinceEpoch(point.x()).toString("hh:mm:ss")));

            break;
        case QAbstractAxis::AxisTypeValue:
            m_currentXValue->setText(QStringLiteral("%1 %2")
                                         .arg(tr("X:"))
                                         .arg(QString::number(point.x())));

            break;
        default:
            break;
        }
        m_line->updatePosition(event->pos(), true);
    }
    else
        m_line->updatePosition(QPointF(0, 0), false);
    QGraphicsView::mouseMoveEvent(event);
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    QPoint nAngle = event->angleDelta();
    QPoint nPixel = event->pixelDelta();
    //для mouse
    if (!nAngle.isNull()){
        stretchChart(nAngle.y());
    }
    //для touchbad
    else if(!nPixel.isNull()){
        stretchChart(nPixel.y());
    }
    QGraphicsView::wheelEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *keyEvent)
{
    QGraphicsView::keyPressEvent(keyEvent);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if(chart->plotArea().contains(event->pos()) || containtPositionSeries(chart->mapToValue(event->pos()))){
        if(event->button() == Qt::MouseButton::RightButton && !m_currentData->isVisible()){
            m_currentData->setFont(QFont("Bookman Old Style", 9, QFont::Bold));
            m_currentData->setText(QStringLiteral("%1\n%2\n").arg("<-").arg(currentDataValue(chart->mapToValue(event->pos()))));
            m_currentData->setPos(event->pos());
            m_currentData->setZValue(11);
            m_currentData->show();
        }
        else if(event->button() == Qt::MouseButton::RightButton && m_currentData->isVisible()){
            m_currentData->hide();
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void ChartView::toolTipPoint(QPointF point, bool state)
{
    ExtendedSeries *series = static_cast<ExtendedSeries *>(sender());
    if (m_prompt == nullptr)
        m_prompt = new ToolTip(chart, series);

    if (state){
        switch (m_xAxis->type()) {
        case QAbstractAxis::AxisTypeDateTime:
            m_prompt->setTextToolTip(QStringLiteral("%1\n%2\n%3 %4")
                                         .arg(series->name())
                                         .arg(QString::number(point.y(), 'f', 1))
                                         .arg(tr("Time:"))
                                         .arg(QDateTime::fromMSecsSinceEpoch(point.x()).toString("hh:mm:ss")));
            break;
        case QAbstractAxis::AxisTypeValue:
            m_prompt->setTextToolTip(QStringLiteral("%1\n%2\n%3 %4")
                                         .arg(series->name())
                                         .arg(QString::number(point.y(), 'f', 1))
                                         .arg(tr("X:"))
                                         .arg(QString::number(point.x())));
            break;
        default:
            break;
        }
        m_prompt->setAnchorPoint(point);
        m_prompt->setSeries(series);
        m_prompt->setZValue(11);
        m_prompt->updateGeometry();
        m_prompt->show();
    }
    else{
        m_prompt->hide();
    }
}

void ChartView::legendSetting()
{
    QLegend *legend = chart->legend();
    legend->setShowToolTips(true);
    legend->setBrush(QBrush(QColor(128, 128, 128, 128)));
    legend->setPen(QPen(QColor(192, 192, 192, 192)));
    legend->setInteractive(true);
    legend->setVisible(true);
    legend->setAlignment(Qt::AlignRight);
    connect(legend, &QLegend::attachedToChartChanged, [legend](bool attachedToChart){
        legend->setBackgroundVisible(!attachedToChart);
    });
}

void ChartView::curvesDataShow(const QPointF &p)
{
    if(m_currentValue == nullptr){
        QAbstractSeries *series = chart->series().first();
        m_currentValue = new ToolTip(chart, series);
    }
    if(!m_currentValue->isVisible()){
        m_currentValue->setAllValues(true);
        m_currentValue->setTextToolTip(currentDataValue(p));
        m_currentValue->setAnchorPoint(p);
        m_currentValue->setZValue(11);
        m_currentValue->updateGeometry();
        m_currentValue->show();
    }
    else{
        m_currentValue->hide();
    }
}

QString ChartView::currentDataValue(const QPointF &p)
{
    QString value;
    QString str = "";
    quint64 key = (p.x() / 1000) * 1000;//сбросить милисекунды до 0
    bool searchEnd = false;
    int mid = containtPositionSeries(searchEnd, key);
    if(searchEnd){
        auto s = chart->series();
        QList<QPointF> point = static_cast<ExtendedSeries*>(s.first())->points();
        foreach (auto v, s) {
            if(v->isVisible())
                str.append(v->name() + ": " + QString::number(static_cast<ExtendedSeries*>(v)->at(mid).y(), 'f', 2) + "\n");
        }
        if(m_xAxis->type() == QAbstractAxis::AxisTypeDateTime){
            return QStringLiteral("%1 %2\n%3")
                .arg(tr("Time:"))
                .arg(QDateTime::fromMSecsSinceEpoch(point.at(mid).x()).toString("hh:mm:ss"))
                .arg(str);
        }
        else{
            return QStringLiteral("%1 %2\n%3")
                .arg(tr("X:"))
                .arg(QString::number(point.at(mid).x()))
                .arg(str);
        }
    }
    return QStringLiteral("%1").arg(tr("Data not found"));
}


