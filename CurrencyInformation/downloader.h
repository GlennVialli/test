#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QProcess>
#include <QThread>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebElementCollection>
#include <iostream>

class downloader : public QThread
{
    Q_OBJECT
public:
    downloader(QString toCurrency);
    void doDownload();
    QVector<QString> getLoadedCurrency();
    QVector<QString> getLoadedRate();
    int totalElements;

Q_SIGNALS:
    void startDonwload();
    void showCurrenyAndRate();

private:
    QNetworkAccessManager *accessManager;
    QWebPage webPage;
    QString url;
    QString path;
    QVector<QString> currency, currencyLoaded;
    QVector<QString> rate, rateLoaded;
    int downloadCount;
    bool firstAttempt;
    void render(QString rawHtml);
    void run();
    QString HTMLRemover(QString Data, QString ToRemove);

public slots:
    void finishDownload(QNetworkReply*);
    void reDownload();
};

#endif // DOWNLOADER_H
