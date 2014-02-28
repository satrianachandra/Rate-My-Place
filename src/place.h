#ifndef PLACE_H
#define PLACE_H

#include <QObject>

class Place : public QObject
{
    Q_OBJECT
public:
    explicit Place(QObject *parent = 0);

    QString address;
    QString LatLong;

signals:

public slots:

};

#endif // PLACE_H
