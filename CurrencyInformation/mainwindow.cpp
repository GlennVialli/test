#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tambah = 0;
    toCurrency = "IDR";
    d = new downloader(toCurrency);

    scalar = new QPainter();
    scalar->drawLine(10,200,10,0);
//    scalar->setBackground();
    ui->graphicsView->setBackgroundBrush(scalar->brush());

    connect(this,SIGNAL(startDownload()),d,SLOT(start()));
    connect(d,SIGNAL(showCurrenyAndRate()),this,SLOT(showCurrencyAndRate()));
    emit startDownload();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCurrencyAndRate()
{
    QVector<QString>currencyToShow = d->getLoadedCurrency();
    QVector<QString>rateToShow = d->getLoadedRate();

    int x=0, w=0;

    QStringList TitleHeader;
    TitleHeader<<"Currency"<<QString("Rate to %1").arg(toCurrency);

    ui->tableWidget->setRowCount(d->totalElements);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(TitleHeader);
    for(int i = 0; i<d->totalElements; i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(currencyToShow[i]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(rateToShow[i]));
    }
    QGraphicsScene *scene = new QGraphicsScene(0,0,w=920+tambah,250,this);

    scene->addLine(50,190,/*tambah = */150/*+tambah*/,190,QPen(QColor(255,0,0)));
    scene->addLine(200,190,/*tambah = */300/*+tambah*/,190,QPen(QColor(0,255,0)));
//    scene->addLine(10,200,/*tambah = */10/*+tambah*/,0,QPen(QColor(0,255,0)));
    qDebug("w %d, x %d, tambah %d",w,x,tambah);
    tambah = tambah + 100;
    ui->graphicsView->setScene(scene);
//    ui->graphicsView->setBackgroundBrush();
}
