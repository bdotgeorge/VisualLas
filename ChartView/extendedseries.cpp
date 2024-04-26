#include "extendedseries.h"

ExtendedSeries::ExtendedSeries(QObject *parent, QString name, QString unitName,
                               int depthOffSet, int countSimbolAfterComma) : QLineSeries(parent)
{
    this->setName(name + " " + unitName);
    setUnitName(unitName);
    setDepthOffSet(depthOffSet);
    setCountSimbolAfterComma(countSimbolAfterComma);
    setNameLine(name);
}

ExtendedSeries::~ExtendedSeries()
{

}

int ExtendedSeries::depthOffSet() const
{
    return m_depthOffSet;
}

void ExtendedSeries::setDepthOffSet(int newDepthOffSet)
{
    m_depthOffSet = newDepthOffSet;
}

int ExtendedSeries::countSimbolAfterComma() const
{
    return m_countSimbolAfterComma;
}

void ExtendedSeries::setCountSimbolAfterComma(int newCountSimbolAfterComma)
{
    m_countSimbolAfterComma = newCountSimbolAfterComma;
}

const QString &ExtendedSeries::unitName() const
{
    return m_unitName;
}

void ExtendedSeries::setUnitName(const QString &newUnitName)
{
    m_unitName = newUnitName;
}

void ExtendedSeries::setNameLine(const QString &newNameLine)
{
    m_nameLine = newNameLine;
}

const QString &ExtendedSeries::nameLine() const
{
    return m_nameLine;
}

void ExtendedSeries::backupData()
{
    if(m_originalBackup) return;
    m_backup = this->points();
    m_originalBackup = true;
}

const QList<QPointF> &ExtendedSeries::backup() const
{
    return m_backup;
}

bool ExtendedSeries::isOriginalBackup() const
{
    return m_originalBackup;
}
