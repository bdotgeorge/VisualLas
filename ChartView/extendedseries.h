#ifndef EXTENDEDSERIES_H
#define EXTENDEDSERIES_H

#include <QLineSeries>

class ExtendedSeries : public QLineSeries
{
public:
    explicit ExtendedSeries(QObject *parent = nullptr, QString name = "",
                            QString unitName = "", int depthOffSet = 0, int countSimbolAfterComma = 1);
    ~ExtendedSeries() override;
    int depthOffSet() const;
    void setDepthOffSet(int newDepthOffSet);
    int countSimbolAfterComma() const;
    void setCountSimbolAfterComma(int newCountSimbolAfterComma);
    const QString &unitName() const;
    void setUnitName(const QString &newUnitName);
    void setFilePatch(const QString &newUrl);
    void setNameDevice(const QString &newDevice);
    const QString &deviceName() const;
    const QString &filePatch() const;
    void setNameLine(const QString &newNameLine);
    const QString &nameLine() const;
    void backupData();
    const QList<QPointF> &backup() const;
    bool isOriginalBackup() const;
    void setAddedToChart(bool newAddedToChart);
    bool addedToChart() const;
    bool adminData() const;
    void setAdminData(bool newAdminData);

private:
    int m_depthOffSet = 0;//смещение по глубине
    int m_countSimbolAfterComma = 1; // количество знаков после запятой
    QString m_unitName = ""; //единицы измерения
    QString m_nameLine = ""; // имя без единиц измерения
    QString m_url = ""; //адрес файла
    QString m_device = ""; // имя прибора
    QList<QPointF> m_backup; //исходные значения
    bool m_originalBackup = false;//оригинальные backup исходные данные(true оригинальные)
    bool m_addedToChart = false;
    bool m_adminData = false;
};

#endif // EXTENDEDSERIES_H
