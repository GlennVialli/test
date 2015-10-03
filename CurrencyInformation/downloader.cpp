#include "downloader.h"

downloader::downloader(QString toCurrency)
{
    accessManager = new QNetworkAccessManager(this);
    url = QString("http://www.x-rates.com/table/?from=%1&amount=1").arg(toCurrency);
    path = QString("C:/Users/gvlam/Desktop/New Folder (2)/Index3333.html");
    firstAttempt = true;

    connect(accessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishDownload(QNetworkReply*)));
    connect(this,SIGNAL(startDonwload()), this, SLOT(reDownload()));

    downloadCount = 0;
}

void downloader::run()
{
    emit startDonwload();
}

void downloader::doDownload()
{
    accessManager->get(QNetworkRequest(QUrl(url)));
}

void downloader::reDownload()
{
    if(!firstAttempt)
    {
        this->msleep(1000);
        firstAttempt = false;
    }
    doDownload();
}

void downloader::finishDownload(QNetworkReply *reply)
{
    QByteArray rawData =  reply->readAll();
    reply->destroyed(this);
    QString rawHtml(rawData), HtmlToProcess;

    QFile *file = new QFile(path);

    if(file->open(QFile::Append))
    {
        file->write(rawData);
        file->flush();
        file->close();
    }

    HtmlToProcess = HTMLRemover(rawHtml,"script");
    render(HtmlToProcess);
}

void downloader::render(QString rawHtml)
{
    currencyLoaded.clear();
    rateLoaded.clear();
    QWebFrame *mainFrame = webPage.mainFrame();
    mainFrame->setHtml(rawHtml);
    QWebElement documentElement = mainFrame->documentElement();
    QWebElementCollection elements = documentElement.findAll("#content > div:nth-child(1) > div > div.col2.pull-right.module.bottomMargin > div.moduleContent > table:nth-child(4) > tbody > tr");

    int i = 0;
    foreach (QWebElement element, elements)
    {
        currency.push_back(element.findFirst("td:nth-child(1)").toInnerXml());
        rate.push_back(element.findFirst("td:nth-child(3) > a").toInnerXml());
//        qDebug()<< currency[i+(elements.count()*downloadCount)]+"\t\t"+rate[i+(elements.count()*downloadCount)]+"\n";

        currencyLoaded.push_back(currency[i+(elements.count()*downloadCount)]);
        rateLoaded.push_back(rate[i+(elements.count()*downloadCount)]);
        i++;
    }
    totalElements = elements.count();
    downloadCount++;
    emit showCurrenyAndRate();
    emit startDonwload();
}

QString downloader::HTMLRemover(QString Data, QString ToRemove)
{
    QString ToCompare;
    QString result;
    bool Done = false;
    int TruthCount = 0;

    /*the variable value will consist of whatever data inside of whatever element and whatever class from ToRemove*/
    for(int i = 0; i<Data.size(); i++)
    {
        if(Data[i] == '<')
        {
            ToCompare.push_back(Data[i]);
            for(i = i+1;Data[i]!='>';i++)
                ToCompare.push_back(Data[i]);
            if(ToCompare.contains("<"+ToRemove,Qt::CaseInsensitive))
            {
                for(i = i+1; i<Data.size(); i++)
                {
                    if(Data[i] == '/')
                    {
                        for(int ElIter = 0; ElIter<ToRemove.size();ElIter++)
                        {
                            if(ToRemove[ElIter] == Data[++i])
                                TruthCount++;

                            if(TruthCount == ToRemove.size())
                                Done = true;
                        }
                        TruthCount = 0;
                    }
                    if(Done)
                    {
                        Done = false;
                        ToCompare.clear();
                        i++;
                        break;
                    }
                }
            }
            else
            {
                result.push_back(ToCompare);
                result.push_back(Data[i]);
                ToCompare.clear();
            }
        }
        else
        {
            result.push_back(Data[i]);
        }
    }
    return result;
}

QVector<QString> downloader::getLoadedCurrency()
{
    return currencyLoaded;
}

QVector<QString> downloader::getLoadedRate()
{
    return rateLoaded;
}
