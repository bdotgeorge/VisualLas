#ifndef FILEDATA_H
#define FILEDATA_H

#include "ChartView/extendedseries.h"
#include <QObject>

class FileData : public QObject
{
    Q_OBJECT
public:
    explicit FileData(QObject *parent = nullptr);
    QList<ExtendedSeries*> readLas(const QString &patch);
private:
    QList<ExtendedSeries*> readLas(QTextStream &stream);
    QList<ExtendedSeries*> parsingLas(QStringList &data);
    QList<float> stringToListFloat(const QString &values);
    QList<ExtendedSeries *> fromFile(QTextStream &stream);
    QString readLineFromStream(QTextStream &stream);
    QString processingVersionInformation(QTextStream &stream);
    QString processingWellInformation(QTextStream &stream);
    QString processingCurveInformation(QTextStream &stream, QList<ExtendedSeries*> &series);
    void processingASCIIInformation(QTextStream &stream, QList<ExtendedSeries*> &series);
    QString takeLineBetweenBeginAndPoint(const QString &line);
    QString takeLineBetweenPointAndColon(const QString &line);
signals:
};

#endif // FILEDATA_H
