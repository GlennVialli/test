#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "downloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int tambah;
    ~MainWindow();

Q_SIGNALS:
    void startDownload();

private:
    Ui::MainWindow *ui;
    downloader*d;
    QString toCurrency;
    QPainter *scalar;

private slots:
    void showCurrencyAndRate();
};

#endif // MAINWINDOW_H
