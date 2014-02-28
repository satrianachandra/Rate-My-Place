#include "filedownloader.h"


FileDownloader::FileDownloader(QObject *parent):
    QObject(parent)
{

}

FileDownloader::FileDownloader(QUrl theUrl,QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                   SLOT(fileDownloaded(QNetworkReply*)));
       QNetworkRequest request(theUrl);
       m_WebCtrl.get(request);
}


FileDownloader::~FileDownloader(){}


void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
