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

void MainWindow::about()
{
    QMessageBox *about = new QMessageBox(this);
    QString aboutInf = QStringLiteral(
                           "About the program\n%1\n\n"
                           "Developer: Bozhedomov G.V.\n"
                           "Version: %2\n"
                           "Developed in 2024 © %3\n"
                           "Developed as part of training on GeekBrains.\n")
                           .arg("VisualLas")
                           .arg("1.0.0")
                           .arg(QDate::currentDate().toString("yyyy"));
    about->setWindowTitle(this->windowTitle());
    about->setText(QStringLiteral("<a href=\"http://www.gb.ru\">GeekBrains</a>"));
    about->setTextFormat(Qt::RichText);
    about->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(about, &QMessageBox::finished, about, &QMessageBox::deleteLater);
    about->setInformativeText(aboutInf);
    about->setIconPixmap(QPixmap("Images/img/iconApp.ico"));
    about->setDefaultButton(QMessageBox::Ok);
    about->show();
    about->exec();
}

void MainWindow::initStartingConnection()
{
    static QString m_lastDir(QStringLiteral("%1/%2/").arg(QDir::currentPath()).arg("FileDev"));
    connect(ui->openFileAct, &QAction::triggered, [this](){
        QString patch = QFileDialog::getOpenFileName(this, tr("Open file"), m_lastDir, tr("LAS File (*.las)"));
        if(!patch.isEmpty()){
            QFileInfo fi(patch);
            m_lastDir = fi.dir().absolutePath();
            openFile(patch);
        }
    });
    connect(ui->scrollPlusBtn, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->chartShift(10);});
    connect(ui->scrollMinusBtn, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->chartShift(-10);});
    connect(ui->autoScale, &QPushButton::clicked, [this](){if(m_chartView) m_chartView->autoScale();});
    connect(ui->actionVisualLas, &QAction::triggered, this, &MainWindow::about);
    ui->scrollPlusBtn->setIcon(QIcon("img/rightBtn.png"));
    ui->scrollMinusBtn->setIcon(QIcon("img/leftBtn.png"));
    ui->openFileAct->setIcon(QIcon("img/openFile.png"));
}
