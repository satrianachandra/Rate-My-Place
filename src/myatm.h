#ifndef MYATM_H
#define MYATM_H

#include <QObject>

class myATM : public QObject
{
    Q_OBJECT
public:
    explicit myATM(QObject *parent = 0);

    QString name;
    QString distance;

signals:

public slots:

};

#endif // MYATM_H
