#include "filedata.h"
#include <QFile>

FileData::FileData(QObject *parent)
    : QObject{parent}
{}

QList<ExtendedSeries *> FileData::readLas(const QString &patch)
{
    QFile f(patch);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file not open" << patch;
    }
    QTextStream stream(&f);
    stream.setEncoding(QStringConverter::System);
    return fromFile(stream);
}

QList<ExtendedSeries *> FileData::readLas(QTextStream &stream)
{
    QStringList data;
    while (!stream.atEnd()) {
        data.append(stream.readLine().trimmed());
    }
    return parsingLas(data);
}

QList<ExtendedSeries *> FileData::parsingLas(QStringList &data)
{
    if(data.size() < 25) return QList<ExtendedSeries *>();
    QList<ExtendedSeries *> series;
    int i = 24;
    while(!data.at(i).contains("~A")){
        series.append(new ExtendedSeries(nullptr, data.at(i).mid(0, data.at(i).indexOf(".")), data.at(i).mid(data.at(i).indexOf(".") + 1, data.at(i).indexOf(" ") - 1).remove(" ")));
        i++;
    }
    i++;
    for (; i < data.size(); ++i) {
        QList<float> temp(stringToListFloat(data.at(i)));
        for (int j = 1; j - 1 < series.size() && j < temp.size(); ++j) {
            series.at(j - 1)->append(temp.at(0), temp.at(j));
        }
    }
    return series;
}

QList<float> FileData::stringToListFloat(const QString &values)
{
    QStringList temp(values.split(" ", Qt::SkipEmptyParts));
    QList<float> result;
    foreach (QString v, temp) {
        result.append(v.toFloat());
    }
    return result;
}

QList<ExtendedSeries *> FileData::fromFile(QTextStream &stream)
{
    QList<ExtendedSeries *> series;
    QString line = readLineFromStream(stream);
    while (!stream.atEnd()) {
        if (line.contains("~V"))
            line = processingVersionInformation(stream);
        else if (line.contains("~W"))
            line = processingWellInformation(stream);
        else if (line.contains("~C"))
            line = processingCurveInformation(stream, series);
        else if (line.contains("~A"))
            processingASCIIInformation(stream, series);
        else
            line = readLineFromStream(stream);
    }
    return series;
}

QString FileData::readLineFromStream(QTextStream &stream)
{
    QString line = stream.readLine().trimmed();
    while (line.contains("#"))
        line = stream.readLine().trimmed();
    return line;
}

QString FileData::processingVersionInformation(QTextStream &stream)
{
    QString line;
    while (!stream.atEnd()) {
        line = readLineFromStream(stream);
        if (line.contains("~"))
            break;
        else if (line.indexOf("VERS") != -1)
            takeLineBetweenPointAndColon(line).toDouble();
        else if (line.indexOf("WRAP") != -1)
            takeLineBetweenPointAndColon(line).indexOf("NO") == -1;
    }
    return line;
}

QString FileData::processingWellInformation(QTextStream &stream)
{
    QString line;
    while (!stream.atEnd()) {
        line = readLineFromStream(stream);
        if (line.indexOf("~") != -1)
            break;
        else if (line.indexOf("NULL") != -1) {
            takeLineBetweenPointAndColon(line).toDouble();
        }
    }
    return line;
}

QString FileData::processingCurveInformation(QTextStream &stream, QList<ExtendedSeries *> &series)
{
    QString line = readLineFromStream(stream);
    while (!stream.atEnd()) {
        line = readLineFromStream(stream);
        if (line.contains("~")) {
            break;
        }
        else {
            series.append(new ExtendedSeries(nullptr, takeLineBetweenBeginAndPoint(line), takeLineBetweenPointAndColon(line)));
        }
    }
    return line;
}

void FileData::processingASCIIInformation(QTextStream &stream, QList<ExtendedSeries *> &series)
{
    QStringList listData;
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine().trimmed();
        if (line.contains("~")) break;
        listData.append(line);
    }
    for (int i = 0; i < listData.size(); ++i) {
        QList<float> temp(stringToListFloat(listData.at(i)));
        for (int j = 1; j - 1 < series.size() && j < temp.size(); ++j) {
            series.at(j - 1)->append(temp.at(0), temp.at(j));
        }
    }
}

QString FileData::takeLineBetweenBeginAndPoint(const QString &line)
{
    return line.mid(0, line.indexOf(".")).toUpper().trimmed();
}

QString FileData::takeLineBetweenPointAndColon(const QString &line)
{
    const int dotIndex = line.indexOf(".") + 1;
    return line.mid(dotIndex, line.indexOf(":") - dotIndex).trimmed();
}
