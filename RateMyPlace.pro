# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = RateMyPlace

CONFIG += sailfishapp

SOURCES += src/RateMyPlace.cpp \
    src/place.cpp \
    src/myatm.cpp \
    src/scoredistance.cpp \
    src/rating.cpp

OTHER_FILES += qml/RateMyPlace.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/RateMyPlace.spec \
    rpm/RateMyPlace.yaml \
    RateMyPlace.desktop \
    qml/pages/Page1.qml \
    qml/pages/ThirdPage.qml \
    qml/pages/FourthPage.qml \
    qml/pages/Page4.qml \
    qml/pages/OpenLayers.js \
    qml/pages/FifthPage.qml

HEADERS += \
    src/place.h \
    src/myatm.h \
    src/scoredistance.h \
    src/rating.h

QT += xml
QT += webkit
