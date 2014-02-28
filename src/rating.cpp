#include "rating.h"
#include <QEventLoop>
#include <QTextStream>
#include <QFile>
#include <QtXml/QDomDocument>

QDomElement docElem ;
QDomNodeList nodeList;

Rating::Rating(QObject *parent) :QObject(parent)
{
    testAddressToRate = "";
    latLong="";
    testTotalScore="";

    //beginRating("Karankokatu 4");

}

void Rating::setAddressToRate(QString addr){testAddressToRate =addr; }
QString Rating::AddressToRate() const{return testAddressToRate;}

void Rating::setLatLong(QString latlong){latLong=latlong;}
QString Rating::LatLong() const{return latLong;}

void Rating::setTotalScore(QString totscore){testTotalScore =totscore; }
QString Rating::TotalScore() const{return testTotalScore;}

void Rating::setDummy(QString laDummy){justDummy=laDummy;}
QString Rating::Dummy()const {return justDummy;}

QString Rating::getLatLong() const{
        return "fcuk";
}

void Rating::setMyATM(ScoreDistance myATMparam){theATM = myATMparam;}
ScoreDistance Rating::MyATM() const{return theATM;}

void Rating::setMyBusStop(QString myBusStop){theBusStop = myBusStop;}
QString Rating::MyBusStop() const{return theBusStop;}



void Rating::fileIsReady()
{
    //not used, will be deleted

   //setAddressToRate("LOLOL");
   QByteArray ba = reply->readAll();
   QString batoQString = ba;
   setLatLong(batoQString);
   //setAddressToRate(batoQString);
}


void Rating::beginRating(const QString address){

    setMyBusStop(address);

    QString urlString = "http://nominatim.openstreetmap.org/search.php?q="+address+"&viewbox=28.13$2C61.05$2C28.14$2C61.04&format=xml";
    //QString urlString = "http://www.google.com";


    //Getting the XML for the user's address
    manager = new QNetworkAccessManager(this);
    reply = manager->get(QNetworkRequest(urlString));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    //Parsing the XML to get the coordinate of the user's address
    QDomDocument *doc = new QDomDocument();
    doc->setContent(reply);


    //Get the root element
      QDomElement docElem = doc->documentElement();
      QDomNodeList nodeList = docElem.elementsByTagName("place");

      //Check each node one by one.
          //for(int ii = 0;ii < nodeList.count(); ii++)
      for(int ii = 0;ii < 1; ii++)
          {
              QDomElement el = nodeList.at(ii).toElement();
              latit = el.attribute("lat");
              longit = el.attribute("lon");
          }

      setLatLong(latit+"|"+longit);

//GettingATM++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      //1. Getting ATM list
      //within 300m
      QString atmString = "(node(around:300,"+latit+","+longit+")[\"amenity\"=\"atm\"];>;);out;";
      atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
      //Getting the XML
      //manager = new QNetworkAccessManager(this);
      reply = manager->get(QNetworkRequest(atmString));
      connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
      loop.exec();

        doc->setContent(reply);
      //Get the root element
        docElem = doc->documentElement();
        nodeList = docElem.elementsByTagName("node");

        QString atmResult="";
        long atmResulti=0;

        QString busStopResult="";
        long busStopResulti=0;

        QString hospitalResult="";
        long hospitalResulti=0;

        QString restaurantResult="";
        long restaurantResulti=0;

        QString universityResult="";
        long universityResulti=0;

        QString municipalityResult="";;
        long municipalityResulti=0;

        QString smarketResult="";
        long smarketResulti=0;

        if (nodeList.count()>0){

            //theATM.score = "5";
            //theATM.distance="300";
            //setAddressToRate("Score"+theATM.score);
            for(int ii=0;ii<nodeList.count();ii++){
                // get the current one as QDomElement
                QDomElement el = nodeList.at(ii).toElement();

                atmResult = atmResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
            }
            atmResult=atmResult+"|score:5|distance:300";
            atmResulti=5;
        }else{
            //within 500m
            //1. Getting ATM list
            QString atmString = "(node(around:500,"+latit+","+longit+")[\"amenity\"=\"atm\"];>;);out;";
            atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
            //Getting the XML
            //manager = new QNetworkAccessManager(this);
            reply = manager->get(QNetworkRequest(atmString));
            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();

              doc->setContent(reply);
            //Get the root element
              docElem = doc->documentElement();
              nodeList = docElem.elementsByTagName("node");
              if (nodeList.count()>0){
                  //setAddressToRate("ada di <500m");
                  theATM.score = "4";
                  theATM.distance="500";

                //  setAddressToRate("Score"+theATM.score);
                  for(int ii=0;ii<nodeList.count();ii++){
                      // get the current one as QDomElement
                      QDomElement el = nodeList.at(ii).toElement();

                      atmResult = atmResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                  }
                  atmResult=atmResult+"|score:4|distance:500";
                  atmResulti=4;
                }else{
                  //within 800m
                  //1. Getting ATM list
                  QString atmString = "(node(around:800,"+latit+","+longit+")[\"amenity\"=\"atm\"];>;);out;";
                  atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                  //Getting the XML
                  //manager = new QNetworkAccessManager(this);
                  reply = manager->get(QNetworkRequest(atmString));
                  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                  loop.exec();

                    doc->setContent(reply);
                  //Get the root element
                    docElem = doc->documentElement();
                    nodeList = docElem.elementsByTagName("node");
                    if (nodeList.count()>0){
                        //setAddressToRate("ada di <800m");
                        theATM.score = "3";
                        theATM.distance="800";
                       // setAddressToRate("Score"+theATM.score);
                        for(int ii=0;ii<nodeList.count();ii++){
                            // get the current one as QDomElement
                            QDomElement el = nodeList.at(ii).toElement();

                            atmResult = atmResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                        }
                        atmResult=atmResult+"|score:3|distance:800";
                        atmResulti=3;
                      }else{
                        //within 1100m
                        //1. Getting ATM list
                        QString atmString = "(node(around:1100,"+latit+","+longit+")[\"amenity\"=\"atm\"];>;);out;";
                        atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                        //Getting the XML
                        //manager = new QNetworkAccessManager(this);
                        reply = manager->get(QNetworkRequest(atmString));
                        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                        loop.exec();

                          doc->setContent(reply);
                        //Get the root element
                          docElem = doc->documentElement();
                          nodeList = docElem.elementsByTagName("node");
                          if (nodeList.count()>0){
                              //setAddressToRate("ada di <800m");
                              theATM.score = "2";
                              theATM.distance="1100";
                            //  setAddressToRate("Score"+theATM.score);
                              for(int ii=0;ii<nodeList.count();ii++){
                                  // get the current one as QDomElement
                                  QDomElement el = nodeList.at(ii).toElement();

                                  atmResult = atmResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                              }
                                atmResult=atmResult+"|score:2|distance:1100";
                                atmResulti=2;
                            }else{
                              //within 1100m
                              //1. Getting ATM list
                              QString atmString = "(node(around:2000,"+latit+","+longit+")[\"amenity\"=\"atm\"];>;);out;";
                              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                              //Getting the XML
                              //manager = new QNetworkAccessManager(this);
                              reply = manager->get(QNetworkRequest(atmString));
                              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                              loop.exec();

                                doc->setContent(reply);
                              //Get the root element
                                docElem = doc->documentElement();
                                nodeList = docElem.elementsByTagName("node");
                                if (nodeList.count()>0){
                                    //setAddressToRate("ada di <800m");
                                    theATM.score = "1";
                                    theATM.distance="2000";
                                 //   setAddressToRate("Score"+theATM.score);
                                    for(int ii=0;ii<nodeList.count();ii++){
                                        // get the current one as QDomElement
                                        QDomElement el = nodeList.at(ii).toElement();

                                        atmResult = atmResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                    }
                                    atmResult=atmResult+"|score:1|distance:2000";
                                    atmResulti=1;
                                   }
                          }




                    }

              }

        }


//GettingBusStop++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
              //within 300m
              atmString = "(node(around:300,"+latit+","+longit+")[\"highway\"=\"bus_stop\"];>;);out;";
              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
              //Getting the XML
              //manager = new QNetworkAccessManager(this);
              reply = manager->get(QNetworkRequest(atmString));
              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
              loop.exec();

                doc->setContent(reply);
              //Get the root element
                docElem = doc->documentElement();
                nodeList = docElem.elementsByTagName("node");

                if (nodeList.count()>0){

                    theATM.score = "5";
                    theATM.distance="300";
                    //setAddressToRate("Score"+theATM.score);
                    for(int ii=0;ii<nodeList.count();ii++){
                        // get the current one as QDomElement
                        QDomElement el = nodeList.at(ii).toElement();
                        busStopResult = busStopResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                    }
                    busStopResult=busStopResult+"|score:5|distance:300";
                    busStopResulti = 5;
                }else{
                    //within 500m
                    //1. Getting ATM list
                    atmString = "(node(around:500,"+latit+","+longit+")[\"highway\"=\"bus_stop\"];>;);out;";
                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                    //Getting the XML
                    //manager = new QNetworkAccessManager(this);
                    reply = manager->get(QNetworkRequest(atmString));
                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                    loop.exec();

                      doc->setContent(reply);
                    //Get the root element
                      docElem = doc->documentElement();
                      nodeList = docElem.elementsByTagName("node");
                      if (nodeList.count()>0){
                          //setAddressToRate("ada di <500m");
                          theATM.score = "4";
                          theATM.distance="500";

                          //setAddressToRate("Score"+theATM.score);
                          for(int ii=0;ii<nodeList.count();ii++){
                              // get the current one as QDomElement
                              QDomElement el = nodeList.at(ii).toElement();

                              busStopResult = busStopResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                          }
                          busStopResult=busStopResult+"|score:4|distance:500";
                          busStopResulti = 4;
                        }else{
                          //within 800m
                          //1. Getting ATM list
                          atmString = "(node(around:800,"+latit+","+longit+")[\"highway\"=\"bus_stop\"];>;);out;";
                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                          //Getting the XML
                          //manager = new QNetworkAccessManager(this);
                          reply = manager->get(QNetworkRequest(atmString));
                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                          loop.exec();

                            doc->setContent(reply);
                          //Get the root element
                            docElem = doc->documentElement();
                            nodeList = docElem.elementsByTagName("node");
                            if (nodeList.count()>0){
                                //setAddressToRate("ada di <800m");
                                theATM.score = "3";
                                theATM.distance="800";
                                //setAddressToRate("Score"+theATM.score);
                                for(int ii=0;ii<nodeList.count();ii++){
                                    // get the current one as QDomElement
                                    QDomElement el = nodeList.at(ii).toElement();

                                    busStopResult = busStopResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                }
                                busStopResult=busStopResult+"|score:3|distance:800";
                            busStopResulti = 3;}
                            else{
                                //within 1100m
                                //1. Getting ATM list
                                atmString = "(node(around:1100,"+latit+","+longit+")[\"highway\"=\"bus_stop\"];>;);out;";
                                atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                //Getting the XML
                                //manager = new QNetworkAccessManager(this);
                                reply = manager->get(QNetworkRequest(atmString));
                                connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                loop.exec();

                                  doc->setContent(reply);
                                //Get the root element
                                  docElem = doc->documentElement();
                                  nodeList = docElem.elementsByTagName("node");
                                  if (nodeList.count()>0){
                                      //setAddressToRate("ada di <800m");
                                      theATM.score = "2";
                                      theATM.distance="1100";
                                      //setAddressToRate("Score"+theATM.score);
                                      for(int ii=0;ii<nodeList.count();ii++){
                                          // get the current one as QDomElement
                                          QDomElement el = nodeList.at(ii).toElement();

                                          busStopResult = busStopResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                      }
                                      busStopResult=busStopResult+"|score:2|distance:1100";
                                      busStopResulti = 2;

                                  }else{
                                      //within 1100m
                                      //1. Getting ATM list
                                      atmString = "(node(around:2000,"+latit+","+longit+")[\"highway\"=\"bus_stop\"];>;);out;";
                                      atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                      //Getting the XML
                                      //manager = new QNetworkAccessManager(this);
                                      reply = manager->get(QNetworkRequest(atmString));
                                      connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                      loop.exec();

                                        doc->setContent(reply);
                                      //Get the root element
                                        docElem = doc->documentElement();
                                        nodeList = docElem.elementsByTagName("node");
                                        if (nodeList.count()>0){
                                            //setAddressToRate("ada di <800m");
                                            theATM.score = "1";
                                            theATM.distance="2000";
                                            //setAddressToRate("Score"+theATM.score);
                                            for(int ii=0;ii<nodeList.count();ii++){
                                                // get the current one as QDomElement
                                                QDomElement el = nodeList.at(ii).toElement();

                                                busStopResult = busStopResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                            }
                                            busStopResult=busStopResult+"|score:1|distance:2000";
                                            busStopResulti = 1;
                                        }
                                  }




                            }

                      }

                }



                //GettingHospital++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                              //within 300m
                              atmString = "(node(around:300,"+latit+","+longit+")[\"amenity\"=\"hospital\"];>;);out;";
                              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                              //Getting the XML
                              //manager = new QNetworkAccessManager(this);
                              reply = manager->get(QNetworkRequest(atmString));
                              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                              loop.exec();

                                doc->setContent(reply);
                              //Get the root element
                                docElem = doc->documentElement();
                                nodeList = docElem.elementsByTagName("node");

                                if (nodeList.count()>0){

                                    theATM.score = "5";
                                    theATM.distance="300";
                                    //setAddressToRate("Score"+theATM.score);
                                    for(int ii=0;ii<nodeList.count();ii++){
                                        // get the current one as QDomElement
                                        QDomElement el = nodeList.at(ii).toElement();

                                        hospitalResult = hospitalResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                    }
                                    hospitalResult=hospitalResult+"|score:5|distance:300";
                                    hospitalResulti=5;
                                }else{
                                    //within 500m
                                    //1. Getting ATM list
                                    atmString = "(node(around:500,"+latit+","+longit+")[\"amenity\"=\"hospital\"];>;);out;";
                                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                    //Getting the XML
                                    //manager = new QNetworkAccessManager(this);
                                    reply = manager->get(QNetworkRequest(atmString));
                                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                    loop.exec();

                                      doc->setContent(reply);
                                    //Get the root element
                                      docElem = doc->documentElement();
                                      nodeList = docElem.elementsByTagName("node");
                                      if (nodeList.count()>0){
                                          //setAddressToRate("ada di <500m");
                                          theATM.score = "4";
                                          theATM.distance="500";

                                         // setAddressToRate("Score"+theATM.score);
                                          for(int ii=0;ii<nodeList.count();ii++){
                                              // get the current one as QDomElement
                                              QDomElement el = nodeList.at(ii).toElement();

                                              hospitalResult = hospitalResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                          }
                                          hospitalResult=hospitalResult+"|score:4|distance:500";
                                          hospitalResulti=4;
                                        }else{
                                          //within 800m
                                          //1. Getting ATM list
                                          atmString = "(node(around:800,"+latit+","+longit+")[\"amenity\"=\"hospital\"];>;);out;";
                                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                          //Getting the XML
                                          //manager = new QNetworkAccessManager(this);
                                          reply = manager->get(QNetworkRequest(atmString));
                                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                          loop.exec();

                                            doc->setContent(reply);
                                          //Get the root element
                                            docElem = doc->documentElement();
                                            nodeList = docElem.elementsByTagName("node");
                                            if (nodeList.count()>0){
                                                //setAddressToRate("ada di <800m");
                                                theATM.score = "3";
                                                theATM.distance="800";
                                                //setAddressToRate("Score"+theATM.score);
                                                for(int ii=0;ii<nodeList.count();ii++){
                                                    // get the current one as QDomElement
                                                    QDomElement el = nodeList.at(ii).toElement();

                                                    hospitalResult = hospitalResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                }
                                                hospitalResult=hospitalResult+"|score:3|distance:800";
                                                hospitalResulti=3;
                                            }else{
                                                //within 1100m
                                                //1. Getting ATM list
                                                atmString = "(node(around:1100,"+latit+","+longit+")[\"amenity\"=\"hospital\"];>;);out;";
                                                atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                //Getting the XML
                                                //manager = new QNetworkAccessManager(this);
                                                reply = manager->get(QNetworkRequest(atmString));
                                                connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                loop.exec();

                                                  doc->setContent(reply);
                                                //Get the root element
                                                  docElem = doc->documentElement();
                                                  nodeList = docElem.elementsByTagName("node");
                                                  if (nodeList.count()>0){
                                                      //setAddressToRate("ada di <800m");
                                                      theATM.score = "2";
                                                      theATM.distance="1100";
                                                    //  setAddressToRate("Score"+theATM.score);
                                                      for(int ii=0;ii<nodeList.count();ii++){
                                                          // get the current one as QDomElement
                                                          QDomElement el = nodeList.at(ii).toElement();

                                                          hospitalResult = hospitalResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                      }
                                                      hospitalResult=hospitalResult+"|score:2|distance:1100";
                                                      hospitalResulti=2;
                                                    }else{
                                                      //within 1100m
                                                      //1. Getting ATM list
                                                      atmString = "(node(around:2000,"+latit+","+longit+")[\"amenity\"=\"hospital\"];>;);out;";
                                                      atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                      //Getting the XML
                                                      //manager = new QNetworkAccessManager(this);
                                                      reply = manager->get(QNetworkRequest(atmString));
                                                      connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                      loop.exec();

                                                        doc->setContent(reply);
                                                      //Get the root element
                                                        docElem = doc->documentElement();
                                                        nodeList = docElem.elementsByTagName("node");
                                                        if (nodeList.count()>0){
                                                            //setAddressToRate("ada di <800m");
                                                            theATM.score = "1";
                                                            theATM.distance="2000";
                                                           // setAddressToRate("Score"+theATM.score);
                                                            for(int ii=0;ii<nodeList.count();ii++){
                                                                // get the current one as QDomElement
                                                                QDomElement el = nodeList.at(ii).toElement();

                                                                hospitalResult = hospitalResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                            }
                                                            hospitalResult=hospitalResult+"|score:1|distance:2000";
                                                            hospitalResulti=1;
                                                          }
                                                  }




                                            }

                                      }

                                }


                                      //GettingRestaurant++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    //within 300m
                                                    atmString = "(node(around:300,"+latit+","+longit+")[\"amenity\"=\"restaurant\"];>;);out;";
                                                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                    //Getting the XML
                                                    //manager = new QNetworkAccessManager(this);
                                                    reply = manager->get(QNetworkRequest(atmString));
                                                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                    loop.exec();

                                                      doc->setContent(reply);
                                                    //Get the root element
                                                      docElem = doc->documentElement();
                                                      nodeList = docElem.elementsByTagName("node");

                                                      if (nodeList.count()>0){

                                                          theATM.score = "5";
                                                          theATM.distance="300";
                                                          //setAddressToRate("Score"+theATM.score);
                                                          for(int ii=0;ii<nodeList.count();ii++){
                                                              // get the current one as QDomElement
                                                              QDomElement el = nodeList.at(ii).toElement();


                                                              restaurantResult = restaurantResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                          }
                                                          restaurantResult=restaurantResult+"|score:5|distance:300";
                                                          restaurantResulti = 5;
                                                      }else{
                                                          //within 500m
                                                          //1. Getting ATM list
                                                          atmString = "(node(around:500,"+latit+","+longit+")[\"amenity\"=\"restaurant\"];>;);out;";
                                                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                          //Getting the XML
                                                          //manager = new QNetworkAccessManager(this);
                                                          reply = manager->get(QNetworkRequest(atmString));
                                                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                          loop.exec();

                                                            doc->setContent(reply);
                                                          //Get the root element
                                                            docElem = doc->documentElement();
                                                            nodeList = docElem.elementsByTagName("node");
                                                            if (nodeList.count()>0){
                                                                //setAddressToRate("ada di <500m");
                                                                theATM.score = "4";
                                                                theATM.distance="500";

                                                               // setAddressToRate("Score"+theATM.score);
                                                                for(int ii=0;ii<nodeList.count();ii++){
                                                                    // get the current one as QDomElement
                                                                    QDomElement el = nodeList.at(ii).toElement();

                                                                    restaurantResult = restaurantResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                }
                                                                restaurantResult=restaurantResult+"|score:4|distance:500";
                                                                restaurantResulti = 4;
                                                            }else{
                                                                //within 800m
                                                                //1. Getting ATM list
                                                                atmString = "(node(around:800,"+latit+","+longit+")[\"amenity\"=\"restaurant\"];>;);out;";
                                                                atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                //Getting the XML
                                                                //manager = new QNetworkAccessManager(this);
                                                                reply = manager->get(QNetworkRequest(atmString));
                                                                connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                loop.exec();

                                                                  doc->setContent(reply);
                                                                //Get the root element
                                                                  docElem = doc->documentElement();
                                                                  nodeList = docElem.elementsByTagName("node");
                                                                  if (nodeList.count()>0){
                                                                      //setAddressToRate("ada di <800m");
                                                                      theATM.score = "3";
                                                                      theATM.distance="800";
                                                                      //setAddressToRate("Score"+theATM.score);
                                                                      for(int ii=0;ii<nodeList.count();ii++){
                                                                          // get the current one as QDomElement
                                                                          QDomElement el = nodeList.at(ii).toElement();

                                                                          restaurantResult = restaurantResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                      }
                                                                      restaurantResult=restaurantResult+"|score:3|distance:800";
                                                                      restaurantResulti = 3;
                                                                  }else{
                                                                      //within 1100m
                                                                      //1. Getting ATM list
                                                                      atmString = "(node(around:1100,"+latit+","+longit+")[\"amenity\"=\"restaurant\"];>;);out;";
                                                                      atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                      //Getting the XML
                                                                      //manager = new QNetworkAccessManager(this);
                                                                      reply = manager->get(QNetworkRequest(atmString));
                                                                      connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                      loop.exec();

                                                                        doc->setContent(reply);
                                                                      //Get the root element
                                                                        docElem = doc->documentElement();
                                                                        nodeList = docElem.elementsByTagName("node");
                                                                        if (nodeList.count()>0){
                                                                            //setAddressToRate("ada di <800m");
                                                                            theATM.score = "2";
                                                                            theATM.distance="1100";
                                                                           // setAddressToRate("Score"+theATM.score);
                                                                            for(int ii=0;ii<nodeList.count();ii++){
                                                                                // get the current one as QDomElement
                                                                                QDomElement el = nodeList.at(ii).toElement();

                                                                                restaurantResult = restaurantResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                            }
                                                                            restaurantResult=restaurantResult+"|score:2|distance:1100";
                                                                            restaurantResulti = 2;
                                                                        }else{
                                                                            //within 1100m
                                                                            //1. Getting ATM list
                                                                            atmString = "(node(around:2000,"+latit+","+longit+")[\"amenity\"=\"restaurant\"];>;);out;";
                                                                            atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                            //Getting the XML
                                                                            //manager = new QNetworkAccessManager(this);
                                                                            reply = manager->get(QNetworkRequest(atmString));
                                                                            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                            loop.exec();

                                                                              doc->setContent(reply);
                                                                            //Get the root element
                                                                              docElem = doc->documentElement();
                                                                              nodeList = docElem.elementsByTagName("node");
                                                                              if (nodeList.count()>0){
                                                                                  //setAddressToRate("ada di <800m");
                                                                                  theATM.score = "1";
                                                                                  theATM.distance="2000";
                                                                                 // setAddressToRate("Score"+theATM.score);
                                                                                  for(int ii=0;ii<nodeList.count();ii++){
                                                                                      // get the current one as QDomElement
                                                                                      QDomElement el = nodeList.at(ii).toElement();

                                                                                      restaurantResult = restaurantResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                  }
                                                                                  restaurantResult=restaurantResult+"|score:1|distance:2000";
                                                                                  restaurantResulti = 1;
                                                                              }
                                                                        }




                                                                  }

                                                            }

                                                      }



                                                            //GettingSupermarket++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                                  //1. Getting ATM list
                                                                  //within 300m
                                                                  atmString = "(node(around:300,"+latit+","+longit+")[\"shop\"=\"supermarket\"];>;);out;";
                                                                  atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                  //Getting the XML
                                                                  //manager = new QNetworkAccessManager(this);
                                                                  reply = manager->get(QNetworkRequest(atmString));
                                                                  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                  loop.exec();

                                                                    doc->setContent(reply);
                                                                  //Get the root element
                                                                    docElem = doc->documentElement();
                                                                    nodeList = docElem.elementsByTagName("node");
                                                                    if (nodeList.count()>0){

                                                                        theATM.score = "5";
                                                                        theATM.distance="300";
                                                                       // setAddressToRate("Score"+theATM.score);
                                                                        for(int ii=0;ii<nodeList.count();ii++){
                                                                            // get the current one as QDomElement
                                                                            QDomElement el = nodeList.at(ii).toElement();

                                                                            smarketResult = smarketResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                        }
                                                                        smarketResult=smarketResult+"|score:5|distance:300";
                                                                        smarketResulti=5;
                                                                    }else{
                                                                        //within 500m
                                                                        //1. Getting ATM list
                                                                        QString atmString = "(node(around:500,"+latit+","+longit+")[\"shop\"=\"supermarket\"];>;);out;";
                                                                        atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                        //Getting the XML
                                                                        //manager = new QNetworkAccessManager(this);
                                                                        reply = manager->get(QNetworkRequest(atmString));
                                                                        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                        loop.exec();

                                                                          doc->setContent(reply);
                                                                        //Get the root element
                                                                          docElem = doc->documentElement();
                                                                          nodeList = docElem.elementsByTagName("node");
                                                                          if (nodeList.count()>0){
                                                                              //setAddressToRate("ada di <500m");
                                                                              theATM.score = "4";
                                                                              theATM.distance="500";

                                                                             // setAddressToRate("Score"+theATM.score);
                                                                              for(int ii=0;ii<nodeList.count();ii++){
                                                                                  // get the current one as QDomElement
                                                                                  QDomElement el = nodeList.at(ii).toElement();

                                                                                  smarketResult = smarketResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                              }
                                                                              smarketResult=smarketResult+"|score:4|distance:500";
                                                                               smarketResulti=4;
                                                                          }else{
                                                                              //within 800m
                                                                              //1. Getting ATM list
                                                                              QString atmString = "(node(around:800,"+latit+","+longit+")[\"shop\"=\"supermarket\"];>;);out;";
                                                                              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                              //Getting the XML
                                                                              //manager = new QNetworkAccessManager(this);
                                                                              reply = manager->get(QNetworkRequest(atmString));
                                                                              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                              loop.exec();

                                                                                doc->setContent(reply);
                                                                              //Get the root element
                                                                                docElem = doc->documentElement();
                                                                                nodeList = docElem.elementsByTagName("node");
                                                                                if (nodeList.count()>0){
                                                                                    //setAddressToRate("ada di <800m");
                                                                                    theATM.score = "3";
                                                                                    theATM.distance="800";
                                                                                    //setAddressToRate("Score"+theATM.score);
                                                                                    for(int ii=0;ii<nodeList.count();ii++){
                                                                                        // get the current one as QDomElement
                                                                                        QDomElement el = nodeList.at(ii).toElement();

                                                                                        smarketResult = smarketResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                    }
                                                                                    smarketResult=smarketResult+"|score:3|distance:800";
                                                                                    smarketResulti=3;
                                                                                }else{
                                                                                    //within 1100m
                                                                                    //1. Getting ATM list
                                                                                    QString atmString = "(node(around:1100,"+latit+","+longit+")[\"shop\"=\"supermarket\"];>;);out;";
                                                                                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                    //Getting the XML
                                                                                    //manager = new QNetworkAccessManager(this);
                                                                                    reply = manager->get(QNetworkRequest(atmString));
                                                                                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                    loop.exec();

                                                                                      doc->setContent(reply);
                                                                                    //Get the root element
                                                                                      docElem = doc->documentElement();
                                                                                      nodeList = docElem.elementsByTagName("node");
                                                                                      if (nodeList.count()>0){
                                                                                          //setAddressToRate("ada di <800m");
                                                                                          theATM.score = "2";
                                                                                          theATM.distance="1100";
                                                                                         // setAddressToRate("Score"+theATM.score);
                                                                                          for(int ii=0;ii<nodeList.count();ii++){
                                                                                              // get the current one as QDomElement
                                                                                              QDomElement el = nodeList.at(ii).toElement();

                                                                                              smarketResult = smarketResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");

                                                                                          }
                                                                                          smarketResult=smarketResult+"|score:2|distance:1100";
                                                                                          smarketResulti=2;
                                                                                        }else{
                                                                                          //within 1100m
                                                                                          //1. Getting ATM list
                                                                                          QString atmString = "(node(around:2000,"+latit+","+longit+")[\"shop\"=\"supermarket\"];>;);out;";
                                                                                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                          //Getting the XML
                                                                                          //manager = new QNetworkAccessManager(this);
                                                                                          reply = manager->get(QNetworkRequest(atmString));
                                                                                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                          loop.exec();

                                                                                            doc->setContent(reply);
                                                                                          //Get the root element
                                                                                            docElem = doc->documentElement();
                                                                                            nodeList = docElem.elementsByTagName("node");
                                                                                            if (nodeList.count()>0){
                                                                                                //setAddressToRate("ada di <800m");
                                                                                                theATM.score = "1";
                                                                                                theATM.distance="2000";
                                                                                               // setAddressToRate("Score"+theATM.score);
                                                                                                for(int ii=0;ii<nodeList.count();ii++){
                                                                                                    // get the current one as QDomElement
                                                                                                    QDomElement el = nodeList.at(ii).toElement();

                                                                                                    smarketResult = smarketResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");

                                                                                                }
                                                                                                smarketResult=smarketResult+"|score:1|distance:2000";
                                                                                                smarketResulti=1;
                                                                                               }
                                                                                      }




                                                                                }

                                                                          }

                                                                    }





                                                                    //GettingUniversity++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                                                  //within 300m
                                                                                  atmString = "(node(around:300,"+latit+","+longit+")[\"amenity\"=\"university\"];>;);out;";
                                                                                  atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                  //Getting the XML
                                                                                  //manager = new QNetworkAccessManager(this);
                                                                                  reply = manager->get(QNetworkRequest(atmString));
                                                                                  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                  loop.exec();

                                                                                    doc->setContent(reply);
                                                                                  //Get the root element
                                                                                    docElem = doc->documentElement();
                                                                                    nodeList = docElem.elementsByTagName("node");

                                                                                    if (nodeList.count()>0){

                                                                                        theATM.score = "5";
                                                                                        theATM.distance="300";
                                                                                        //setAddressToRate("Score"+theATM.score);
                                                                                        for(int ii=0;ii<nodeList.count();ii++){
                                                                                            // get the current one as QDomElement
                                                                                            QDomElement el = nodeList.at(ii).toElement();


                                                                                            universityResult = universityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                        }
                                                                                        universityResult=universityResult+"|score:5|distance:300";
                                                                                        universityResulti=5;
                                                                                    }else{
                                                                                        //within 500m
                                                                                        //1. Getting ATM list
                                                                                        atmString = "(node(around:500,"+latit+","+longit+")[\"amenity\"=\"university\"];>;);out;";
                                                                                        atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                        //Getting the XML
                                                                                        //manager = new QNetworkAccessManager(this);
                                                                                        reply = manager->get(QNetworkRequest(atmString));
                                                                                        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                        loop.exec();

                                                                                          doc->setContent(reply);
                                                                                        //Get the root element
                                                                                          docElem = doc->documentElement();
                                                                                          nodeList = docElem.elementsByTagName("node");
                                                                                          if (nodeList.count()>0){
                                                                                              //setAddressToRate("ada di <500m");
                                                                                              theATM.score = "4";
                                                                                              theATM.distance="500";

                                                                                             // setAddressToRate("Score"+theATM.score);
                                                                                              for(int ii=0;ii<nodeList.count();ii++){
                                                                                                  // get the current one as QDomElement
                                                                                                  QDomElement el = nodeList.at(ii).toElement();

                                                                                                  universityResult = universityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                              }
                                                                                              universityResult=universityResult+"|score:4|distance:500";
                                                                                                universityResulti=4;
                                                                                          }else{
                                                                                              //within 800m
                                                                                              //1. Getting ATM list
                                                                                              atmString = "(node(around:800,"+latit+","+longit+")[\"amenity\"=\"university\"];>;);out;";
                                                                                              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                              //Getting the XML
                                                                                              //manager = new QNetworkAccessManager(this);
                                                                                              reply = manager->get(QNetworkRequest(atmString));
                                                                                              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                              loop.exec();

                                                                                                doc->setContent(reply);
                                                                                              //Get the root element
                                                                                                docElem = doc->documentElement();
                                                                                                nodeList = docElem.elementsByTagName("node");
                                                                                                if (nodeList.count()>0){
                                                                                                    //setAddressToRate("ada di <800m");
                                                                                                    theATM.score = "3";
                                                                                                    theATM.distance="800";
                                                                                                   // setAddressToRate("Score"+theATM.score);
                                                                                                    for(int ii=0;ii<nodeList.count();ii++){
                                                                                                        // get the current one as QDomElement
                                                                                                        QDomElement el = nodeList.at(ii).toElement();

                                                                                                        universityResult = universityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                    }
                                                                                                    universityResult=universityResult+"|score:3|distance:800";
                                                                                                    universityResulti=3;
                                                                                                }else{
                                                                                                    //within 1100m
                                                                                                    //1. Getting ATM list
                                                                                                    atmString = "(node(around:1100,"+latit+","+longit+")[\"amenity\"=\"university\"];>;);out;";
                                                                                                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                    //Getting the XML
                                                                                                    //manager = new QNetworkAccessManager(this);
                                                                                                    reply = manager->get(QNetworkRequest(atmString));
                                                                                                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                    loop.exec();

                                                                                                      doc->setContent(reply);
                                                                                                    //Get the root element
                                                                                                      docElem = doc->documentElement();
                                                                                                      nodeList = docElem.elementsByTagName("node");
                                                                                                      if (nodeList.count()>0){
                                                                                                          //setAddressToRate("ada di <800m");
                                                                                                          theATM.score = "2";
                                                                                                          theATM.distance="1100";
                                                                                                         // setAddressToRate("Score"+theATM.score);
                                                                                                          for(int ii=0;ii<nodeList.count();ii++){
                                                                                                              // get the current one as QDomElement
                                                                                                              QDomElement el = nodeList.at(ii).toElement();

                                                                                                              universityResult = universityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                          }
                                                                                                          universityResult=universityResult+"|score:2|distance:1100";
                                                                                                          universityResulti=2;
                                                                                                        }else{
                                                                                                          //within 1100m
                                                                                                          //1. Getting ATM list
                                                                                                          atmString = "(node(around:2000,"+latit+","+longit+")[\"amenity\"=\"university\"];>;);out;";
                                                                                                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                          //Getting the XML
                                                                                                          //manager = new QNetworkAccessManager(this);
                                                                                                          reply = manager->get(QNetworkRequest(atmString));
                                                                                                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                          loop.exec();

                                                                                                            doc->setContent(reply);
                                                                                                          //Get the root element
                                                                                                            docElem = doc->documentElement();
                                                                                                            nodeList = docElem.elementsByTagName("node");
                                                                                                            if (nodeList.count()>0){
                                                                                                                //setAddressToRate("ada di <800m");
                                                                                                                theATM.score = "1";
                                                                                                                theATM.distance="2000";
                                                                                                               // setAddressToRate("Score"+theATM.score);
                                                                                                                for(int ii=0;ii<nodeList.count();ii++){
                                                                                                                    // get the current one as QDomElement
                                                                                                                    QDomElement el = nodeList.at(ii).toElement();

                                                                                                                    universityResult = universityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                                }
                                                                                                                universityResult=universityResult+"|score:1|distance:2000";
                                                                                                                universityResulti=1;
                                                                                                              }
                                                                                                      }




                                                                                                }

                                                                                          }

                                                                                    }



                                                                                    //GettingMunicipality++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                                                                  //within 300m
                                                                                                  atmString = "(node(around:300,"+latit+","+longit+")[\"place\"=\"municipality\"];>;);out;";
                                                                                                  atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                  //Getting the XML
                                                                                                  //manager = new QNetworkAccessManager(this);
                                                                                                  reply = manager->get(QNetworkRequest(atmString));
                                                                                                  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                  loop.exec();

                                                                                                    doc->setContent(reply);
                                                                                                  //Get the root element
                                                                                                    docElem = doc->documentElement();
                                                                                                    nodeList = docElem.elementsByTagName("node");

                                                                                                    if (nodeList.count()>0){

                                                                                                        theATM.score = "5";
                                                                                                        theATM.distance="300";
                                                                                                        //setAddressToRate("Score"+theATM.score);
                                                                                                        for(int ii=0;ii<nodeList.count();ii++){
                                                                                                            // get the current one as QDomElement
                                                                                                            QDomElement el = nodeList.at(ii).toElement();


                                                                                                            municipalityResult = municipalityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                        }
                                                                                                        municipalityResult=municipalityResult+"|score:5|distance:300";
                                                                                                        municipalityResulti = 5;
                                                                                                    }else{
                                                                                                        //within 500m
                                                                                                        //1. Getting ATM list
                                                                                                        atmString = "(node(around:500,"+latit+","+longit+")[\"place\"=\"municipality\"];>;);out;";
                                                                                                        atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                        //Getting the XML
                                                                                                        //manager = new QNetworkAccessManager(this);
                                                                                                        reply = manager->get(QNetworkRequest(atmString));
                                                                                                        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                        loop.exec();

                                                                                                          doc->setContent(reply);
                                                                                                        //Get the root element
                                                                                                          docElem = doc->documentElement();
                                                                                                          nodeList = docElem.elementsByTagName("node");
                                                                                                          if (nodeList.count()>0){
                                                                                                              //setAddressToRate("ada di <500m");
                                                                                                              theATM.score = "4";
                                                                                                              theATM.distance="500";

                                                                                                             // setAddressToRate("Score"+theATM.score);
                                                                                                              for(int ii=0;ii<nodeList.count();ii++){
                                                                                                                  // get the current one as QDomElement
                                                                                                                  QDomElement el = nodeList.at(ii).toElement();

                                                                                                                  municipalityResult = municipalityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                              }
                                                                                                              municipalityResult=municipalityResult+"|score:4|distance:500";
                                                                                                              municipalityResulti = 4;
                                                                                                            }else{
                                                                                                              //within 800m
                                                                                                              //1. Getting ATM list
                                                                                                              atmString = "(node(around:800,"+latit+","+longit+")[\"place\"=\"municipality\"];>;);out;";
                                                                                                              atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                              //Getting the XML
                                                                                                              //manager = new QNetworkAccessManager(this);
                                                                                                              reply = manager->get(QNetworkRequest(atmString));
                                                                                                              connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                              loop.exec();

                                                                                                                doc->setContent(reply);
                                                                                                              //Get the root element
                                                                                                                docElem = doc->documentElement();
                                                                                                                nodeList = docElem.elementsByTagName("node");
                                                                                                                if (nodeList.count()>0){
                                                                                                                    //setAddressToRate("ada di <800m");
                                                                                                                    theATM.score = "3";
                                                                                                                    theATM.distance="800";
                                                                                                                   // setAddressToRate("Score"+theATM.score);
                                                                                                                    for(int ii=0;ii<nodeList.count();ii++){
                                                                                                                        // get the current one as QDomElement
                                                                                                                        QDomElement el = nodeList.at(ii).toElement();

                                                                                                                        municipalityResult = municipalityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                                    }
                                                                                                                    municipalityResult=municipalityResult+"|score:3|distance:800";
                                                                                                                    municipalityResulti = 3;
                                                                                                                }else{
                                                                                                                    //within 1100m
                                                                                                                    //1. Getting ATM list
                                                                                                                    atmString = "(node(around:1100,"+latit+","+longit+")[\"place\"=\"municipality\"];>;);out;";
                                                                                                                    atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                                    //Getting the XML
                                                                                                                    //manager = new QNetworkAccessManager(this);
                                                                                                                    reply = manager->get(QNetworkRequest(atmString));
                                                                                                                    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                                    loop.exec();

                                                                                                                      doc->setContent(reply);
                                                                                                                    //Get the root element
                                                                                                                      docElem = doc->documentElement();
                                                                                                                      nodeList = docElem.elementsByTagName("node");
                                                                                                                      if (nodeList.count()>0){
                                                                                                                          //setAddressToRate("ada di <800m");
                                                                                                                          theATM.score = "2";
                                                                                                                          theATM.distance="1100";
                                                                                                                        //  setAddressToRate("Score"+theATM.score);
                                                                                                                          for(int ii=0;ii<nodeList.count();ii++){
                                                                                                                              // get the current one as QDomElement
                                                                                                                              QDomElement el = nodeList.at(ii).toElement();

                                                                                                                              municipalityResult = municipalityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                                          }
                                                                                                                          municipalityResult=municipalityResult+"|score:2|distance:1100";
                                                                                                                          municipalityResulti = 2;
                                                                                                                        }else{
                                                                                                                          //within 1100m
                                                                                                                          //1. Getting ATM list
                                                                                                                          atmString = "(node(around:2000,"+latit+","+longit+")[\"place\"=\"municipality\"];>;);out;";
                                                                                                                          atmString = "http://overpass.osm.rambler.ru/cgi/interpreter?data="+atmString;
                                                                                                                          //Getting the XML
                                                                                                                          //manager = new QNetworkAccessManager(this);
                                                                                                                          reply = manager->get(QNetworkRequest(atmString));
                                                                                                                          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                                                                                                                          loop.exec();

                                                                                                                            doc->setContent(reply);
                                                                                                                          //Get the root element
                                                                                                                            docElem = doc->documentElement();
                                                                                                                            nodeList = docElem.elementsByTagName("node");
                                                                                                                            if (nodeList.count()>0){
                                                                                                                                //setAddressToRate("ada di <800m");
                                                                                                                                theATM.score = "1";
                                                                                                                                theATM.distance="2000";
                                                                                                                                //setAddressToRate("Score"+theATM.score);
                                                                                                                                for(int ii=0;ii<nodeList.count();ii++){
                                                                                                                                    // get the current one as QDomElement
                                                                                                                                    QDomElement el = nodeList.at(ii).toElement();

                                                                                                                                    municipalityResult = municipalityResult+"$"+"lat:"+el.attribute("lat")+"|lon:"+el.attribute("lon");
                                                                                                                                }
                                                                                                                                municipalityResult=municipalityResult+"|score:1|distance:2000";
                                                                                                                                municipalityResulti = 1;
                                                                                                                              }
                                                                                                                      }




                                                                                                                }

                                                                                                          }

                                                                                                    }



                                                                                                    setAddressToRate(atmResult+"@"+hospitalResult+"@"+restaurantResult+"@"+universityResult+"@"+busStopResult+"@"+municipalityResult+"@"+smarketResult);
                                                                                                    long totalz = 0;

                                                                                                    //totalz = totalz+atmResulti + municipalityResulti+restaurantResulti + busStopResulti + universityResulti+ smarketResulti + hospitalResulti;
                                                                                                    //totalz = qRound (totalz/7.0);

                                                                                                    totalz = totalz+atmResulti + municipalityResulti+restaurantResulti + busStopResulti + universityResulti+ smarketResulti + hospitalResulti;
                                                                                                                                                                                                        totalz = qRound (totalz/7.0);
                                                                                                                                                                                                        if(busStopResulti==5)
                                                                                                                                                                                                        {if(totalz<3){totalz=3;}}
                                                                                                                                                                                                        if(totalz==5){}

                                                                                                    QString overallRate = QString::number(totalz) ;

                                                                                                    setTotalScore(overallRate);
                                                                                                    setDummy(QString::number(busStopResulti)+"@"+QString::number(atmResulti)+"@"+QString::number(smarketResulti)+"@"+QString::number(hospitalResulti)+"@"+QString::number(restaurantResulti)+"@"+QString::number(universityResulti)+"@"+QString::number(municipalityResulti)+"@");


}



QString Rating::getAddress(const QString lat,const QString longit){
    QString result="";
    QString reverseURL = "http://nominatim.openstreetmap.org/reverse?format=xml&lat="+lat+"&+lon="+longit+"&zoom=18&addressdetails=1";
    QEventLoop loop;

    reply = manager->get(QNetworkRequest(reverseURL));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();

    QDomDocument *doc = new QDomDocument();
      doc->setContent(reply);
    //Get the root element
      docElem = doc->documentElement();
      nodeList = docElem.elementsByTagName("addressparts");
      if (nodeList.count()>0){

              QDomElement el = nodeList.at(0).toElement();
              QDomNode pEntries = el.firstChild();

              QDomElement peData = pEntries.toElement();
              //result+=peData.tagName();
              result+=" "+peData.text();

              pEntries = pEntries.nextSibling();
              peData = pEntries.toElement();
              //result+=peData.tagName();
              result+="\nAddress:"+peData.text();


      }
    return result;
}

