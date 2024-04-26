#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filedata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initStartingConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(const QString &patchFile)
{
    QFileInfo fi(patchFile);
    QString ext = fi.suffix();
    if (ext != "las")return;
    if(m_chartView){
        delete m_chartView;
        m_chartView = nullptr;
    }
    FileData f;
    QList<ExtendedSeries*> seires(f.readLas(patchFile));
    if(seires.isEmpty()){
        informationMessage("Empty data", "Check file");
        return;
    }
    m_chartView = new ChartView(seires, false, this);
    ui->cViewVLayout->addWidget(m_chartView);
}

void MainWindow::saveAs()
{

}

void MainWindow::informationMessage(QString title, QString information)
{
    QMessageBox::information(this, title, information);

}

void MainWindow::initStartingConnection()
{
    static QString m_lastDir(QStringLiteral("%1/%2/").arg(QDir::currentPath()).arg("FileDev"));
    connect(ui->openFileAct, &QAction::triggered, [this](){
        QString patch = QFileDialog::getOpenFileName(this, tr("Open file"), m_lastDir, tr("LAs File (*.las)"));
        if(!patch.isEmpty()){
            QFileInfo fi(patch);
            m_lastDir = fi.dir().absolutePath();
            openFile(patch);
        }
    });

    connect(ui->saveAsAction, &QAction::triggered,
            this, &MainWindow::saveAs);

    connect(ui->zoomPlusBtn, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->chartShift(10);});

    connect(ui->zoomMinusBtn, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->chartShift(-10);});

    connect(ui->autoScale, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->autoScale();});

}
