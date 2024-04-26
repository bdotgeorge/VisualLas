#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ChartView/chartview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openFile(const QString &patchFile);
    void saveAs();
    void informationMessage(QString title, QString information);

private:
    void initStartingConnection();
    Ui::MainWindow *ui;
    ChartView *m_chartView = nullptr;

};
#endif // MAINWINDOW_H
