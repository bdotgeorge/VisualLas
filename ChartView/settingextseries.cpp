#include "settingextseries.h"
#include "ui_settingextseries.h"
#include <QColorDialog>
#include <QDoubleValidator>
#include <iostream>

SettingExtSeries::SettingExtSeries(QLegendMarker *marker,
                                   ExtendedSeries *series,
                                   QValueAxis *axis,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingExtSeries),
    m_marker(marker),
    m_series(series),
    m_axis(axis)
{
    ui->setupUi(this);
    setModal(true);
    setWindowIcon(QIcon("images/Btn/settingLine.png"));
    startSettings();
    show();
}

SettingExtSeries::~SettingExtSeries()
{
    delete ui;
}

void SettingExtSeries::setColorLine()
{
    stylebtn = "background-color: %1;"
               "border-style: inset;";
    ui->colorBtn->setStyleSheet(stylebtn.arg(m_series->color().name()));
    QColor color = QColorDialog::getColor();
    if(!color.isValid()){
        stylebtn = "background-color: %1;"
                   "border-style: outset;"
                   "border-width: 1px;"
                   "border-radius: 10px;"
                   "border-color: beige;"
                   "font: bold 12px;"
                   "min-width: 10em;"
                   "padding: 6px;";
        ui->colorBtn->setStyleSheet(stylebtn.arg(m_series->color().name()));
        return;
    }
    m_colorLine = color;
    stylebtn = "background-color: %1;"
               "border-style: outset;"
               "border-width: 1px;"
               "border-radius: 10px;"
               "border-color: beige;"
               "font: bold 12px;"
               "min-width: 10em;"
               "padding: 6px;";
    ui->colorBtn->setStyleSheet(stylebtn.arg(m_colorLine.name()));
}

void SettingExtSeries::visibleChangeAdvSettings()
{
    ui->advSettingsGroupBox->setVisible(!ui->advSettingsGroupBox->isVisible());
}

void SettingExtSeries::onOffSeries()
{
    m_series->setVisible(!m_series->isVisible());
    m_axis->setVisible(!m_axis->isVisible());
    m_marker->setVisible(true);
    qreal alpha = 1.0;
    if (!m_marker->series()->isVisible()) alpha = 0.5;
    QColor color;
    QBrush brush = m_marker->labelBrush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    m_marker->setLabelBrush(brush);
    brush = m_marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    m_marker->setBrush(brush);
    QPen pen = m_marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    m_marker->setPen(pen);
}

void SettingExtSeries::shiftAxisSeries()
{
    bool ok;
    bool coorect = false;
    float shift = ui->shiftAxisLineEdit->text().replace(",", ".").toFloat(&ok);
    if(ok && m_series->points().size() > shift){
        shift = shift * 1000;
        if(shift > 0){
            coorect = leftShift(shift);
        } else{
            coorect = rightShift(shift);
        }
    }
    if(coorect) ui->valueShiftLbl->setText(tr("Correct"));
    else ui->valueShiftLbl->setText(tr("Error"));
}

bool SettingExtSeries::leftShift(float &shift)
{
    m_series->backupData();
    QList<QPointF> original = m_series->points();
    QList<QPointF> shiftData;
    int size = original.size();
    QPointF firstpoint = original.first();
    int indexTake = 0;
    qint64 step = original.at(1).x() - original.first().x();
    for (int i = 0; i < size; ++i) {
        if((firstpoint.x() + shift) <= original.at(i).x()){
            shiftData.append(QPointF(original.at(indexTake).x(), original.at(i).y()));
            indexTake++;
        }
    }

    for (int i = shiftData.size(); i < size; ++i){
        shiftData.append(QPointF(shiftData.last().x() + step, 0));
    }
    if(shiftData.size() == m_series->backup().size()){
        m_series->replace(shiftData);
        return true;
    }
    return false;
}

bool SettingExtSeries::rightShift(float &shift)
{
    m_series->backupData();
    QList<QPointF> original = m_series->points();
    QList<QPointF> shiftData;
    int size = original.size();
    QPointF firstpoint = original.first();
    int indexTake = 0;
    qint64 step = original.at(1).x() - original.first().x();
    while(firstpoint.x() >= original.at(indexTake).x() + shift && indexTake < size){
        shiftData.append(QPointF(original.at(indexTake).x(), 0));
        indexTake++;
    }
    for (int i = 0; i < size - indexTake; ++i) {
        shiftData.append(QPointF(shiftData.last().x() + step, original.at(i).y()));
    }
    if(shiftData.size() == m_series->backup().size()){
        m_series->replace(shiftData);
        return true;
    }
    return false;
}

bool SettingExtSeries::resetShiftAxisSeries()
{
    if(m_series->isOriginalBackup()){
        m_series->replace(m_series->backup());
        ui->valueShiftLbl->setText(tr("Reset shift. Initial data"));
        return true;
    }
    return false;
}

void SettingExtSeries::apply()
{
    bool ok;
    m_Ymax = ui->maxLineEdit->text().replace(",", ".").toFloat(&ok);
    if(ok) m_axis->setMax(m_Ymax);
    m_Ymin = ui->minLineEdit->text().replace(",", ".").toFloat(&ok);
    if(ok) m_axis->setMin(m_Ymin);

    if(ui->advSettingsGroupBox->isVisible()){
        m_bias = ui->depthOffsetLineEdit->text().toInt(&ok);
        m_symbAftComma = ui->numDecPlacesLineEdit->text().toInt(&ok);
        if(ok) m_series->setDepthOffSet(m_bias);
        if(ok) m_series->setCountSimbolAfterComma(m_symbAftComma);
        m_series->setNameLine(ui->nameChangeLineEdit->text());
        m_series->setUnitName(ui->unitLineEdit->text());
        m_series->setName(ui->nameChangeLineEdit->text() + ", " + ui->unitLineEdit->text());
        m_axis->setTitleText(QString("<span style=\" color:%1;\">%2</span>")
                             .arg(m_colorLine.name())
                             .arg(m_series->name()));
    }
    if(m_series->color() != m_colorLine){
        m_axis->setLabelsColor(m_colorLine);
        m_axis->setLinePenColor(m_colorLine);
        m_axis->setTitleText(QString("<span style=\" color:%1;\">%2</span>")
                          .arg(m_colorLine.name())
                          .arg(m_series->name()));
        m_series->setColor(m_colorLine);
        m_marker->setBrush(QBrush(m_colorLine));
    }
    this->~SettingExtSeries();
}

void SettingExtSeries::initStartingConnecting()
{
    connect(ui->applyBtn, &QPushButton::clicked,
            this, &SettingExtSeries::apply);
    connect(ui->colorBtn, &QPushButton::clicked,
            this, &SettingExtSeries::setColorLine);
    connect(ui->advSetCcheckBox, &QCheckBox::stateChanged,
            this, &SettingExtSeries::visibleChangeAdvSettings);
    connect(ui->seriesOnOffCheckBox, &QCheckBox::stateChanged,
            this, &SettingExtSeries::onOffSeries);
    connect(ui->resetShiftBtn, &QPushButton::clicked,
            this, &SettingExtSeries::resetShiftAxisSeries);
    connect(ui->executeShiftAxisBtn, &QPushButton::clicked,
            this, &SettingExtSeries::shiftAxisSeries);
}

void SettingExtSeries::startSettings()
{
    m_colorLine = m_series->color();
    m_Ymax = m_axis->max();
    m_Ymin = m_axis->min();
    m_unitName = m_series->unitName();
    m_nameLine = m_series->name();
    m_symbAftComma = m_series->countSimbolAfterComma();
    m_bias = m_series->depthOffSet();
    ui->nameSeriesLbl->setText(m_series->name());
    QDoubleValidator *validatorMin = new QDoubleValidator(ui->minLineEdit);
    validatorMin->setLocale(QLocale::c());
    validatorMin->setNotation(QDoubleValidator::StandardNotation);
    ui->minLineEdit->setValidator(validatorMin);
    ui->minLineEdit->setText(QString::number(m_axis->min()));

    QDoubleValidator *validatorMax = new QDoubleValidator(ui->maxLineEdit);
    validatorMax->setLocale(QLocale::c());
    validatorMax->setNotation(QDoubleValidator::StandardNotation);
    ui->maxLineEdit->setValidator(validatorMax);
    ui->maxLineEdit->setText(QString::number(m_axis->max()));

    if(m_series->isVisible()) ui->seriesOnOffCheckBox->setCheckState(Qt::CheckState::Checked);
    else ui->seriesOnOffCheckBox->setCheckState(Qt::CheckState::Unchecked);
    ui->advSetCcheckBox->setCheckState(Qt::CheckState::Unchecked);
    ui->advSettingsGroupBox->setVisible(false);
    ui->nameChangeLineEdit->setText(m_series->name().mid(0, m_series->name().indexOf(",")));
    ui->unitLineEdit->setText(m_series->unitName());

    QIntValidator *validatorDepth = new QIntValidator(0, 200, ui->depthOffsetLineEdit);
    validatorDepth->setLocale(QLocale::c());
    ui->depthOffsetLineEdit->setValidator(validatorDepth);
    QIntValidator *validatorDecPlaces = new QIntValidator(0, 4, ui->numDecPlacesLineEdit);
    validatorDepth->setLocale(QLocale::c());
    ui->numDecPlacesLineEdit->setValidator(validatorDecPlaces);

    ui->depthOffsetLineEdit->setText(QString::number(m_series->depthOffSet()));
    ui->numDecPlacesLineEdit->setText(QString::number(m_series->countSimbolAfterComma()));
    int limit = m_series->points().size();
    QDoubleValidator *validatorShift = new QDoubleValidator(-limit, limit, 1, ui->shiftAxisLineEdit);
    validatorMax->setLocale(QLocale::c());
    validatorMax->setNotation(QDoubleValidator::StandardNotation);
    ui->shiftAxisLineEdit->setValidator(validatorShift);
    ui->valueShiftLbl->setText("0");
    stylebtn = "background-color: %1;"
                       "border-style: outset;"
                       "border-width: 1px;"
                       "border-radius: 10px;"
                       "border-color: beige;"
                       "font: bold 12px;"
                       "min-width: 10em;"
                       "padding: 6px;";
    ui->colorBtn->setStyleSheet(stylebtn.arg(m_series->color().name()));
    initStartingConnecting();
}
