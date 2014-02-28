#ifndef RATING_H
#define RATING_H

#include <QObject>

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "scoredistance.h"

class Rating : public QObject
{
    Q_OBJECT


    Q_PROPERTY(QString AddressToRate READ AddressToRate WRITE setAddressToRate NOTIFY onAddressToRateChanged )
    Q_PROPERTY(QString LatLong READ LatLong WRITE setLatLong)

    Q_PROPERTY(QString Dummy READ Dummy WRITE setDummy)

    Q_PROPERTY(QString TotalScore READ TotalScore WRITE setTotalScore)
    /*
    Q_PROPERTY(QString Score1 READ Score1 WRITE setScore1)
    Q_PROPERTY(QString Score2 READ Score2 WRITE setScore2)
    Q_PROPERTY(QString Score3 READ Score3 WRITE setScore3)
    Q_PROPERTY(QString Score4 READ Score4 WRITE setScore4)
    Q_PROPERTY(QString Score5 READ Score5 WRITE setScore5)
    Q_PROPERTY(QString Score6 READ Score6 WRITE setScore6)
    */


    Q_PROPERTY(ScoreDistance MyATM READ MyATM WRITE setMyATM)
    Q_PROPERTY(QString MyBusStop READ MyBusStop WRITE setMyBusStop)




public:
    explicit Rating(QObject *parent = 0);


    void setDummy(QString addr);
    QString Dummy() const;

    void setAddressToRate(QString addr);
    QString AddressToRate() const;

    void setTotalScore(QString totscore);
    QString TotalScore() const;



    void setLatLong(QString latlong);
    QString LatLong() const;

    QString getLatLong() const;


    void setMyATM(ScoreDistance myATMparam);
    ScoreDistance MyATM() const;

    void setMyBusStop(QString myBusStop);
        QString MyBusStop() const;


    QString latit;
    QString longit;




signals:
   void onAddressToRateChanged();

public slots:
    void beginRating(const QString address);

    QString getAddress(const QString lat,const QString longit);

void fileIsReady();

private:
    QString testAddressToRate;
    QString latLong;
    QString testTotalScore;

    ScoreDistance theATM;
    QString theBusStop;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QString justDummy;

};

#endif // RATING_H
