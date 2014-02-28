
import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root
    property string bus;
    property string restaurant;
    property string hospital;
    property string municipality;
    property string supermarket;
    property string atm;
    property string university;


    Component.onCompleted:
    {
     var scoreString = rating.Dummy;
     var scoreStringArray = scoreString.split("@");
        bus = scoreStringArray[0];
        atm = scoreStringArray[1];
        supermarket = scoreString[2];
        hospital = scoreStringArray[3];
        restaurant = scoreStringArray[4];
        university= scoreStringArray[5];
        municipality= scoreStringArray[6];


    }

    SilicaListView {

        id: listView
        anchors.fill: parent
         header: PageHeader { title: "Rate My Place" }





Column {
    id: column

    Text {
        x: 25
        y: 130
        width: parent.width
        color: "White"
        font.pixelSize: 50
        text: "Individual Result "

    }

    Text {
        x: 300
        y: 250
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Scores "

    }

Row {

   BackgroundItem{


       Label {
        x: 25
        y: 290
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Bus Stop "

    }
        onClicked: pageStack.push(Qt.resolvedUrl("FourthPage.qml"))

   }


        }


    Text {
        x: 320
        y: 290
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text:bus

    }


    }
Row {

    Text {
        x: 25
        y: 340
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Atm "

    }
    Text {
        x: 320
        y: 340
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: atm

    }

    }

Row {

    Text {
        x: 25
        y: 390
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Grocery Shop "

    }
    Text {
        x: 320
        y: 390
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: supermarket

    }

    }
Row {

    Text {
        x: 25
        y: 440
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Hospitals "

    }
    Text {
        x: 320
        y: 440
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: hospital

    }

    }
Row {

    Text {
        x: 25
        y: 490
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "Restaurants "

    }
    Text {
        x: 320
        y: 490
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: restaurant

    }

    }
Row {

    Text {
        x: 25
        y: 540
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "University "

    }
    Text {
        x: 320
        y: 540
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: university

    }

    }
Row {

    Text {
        x: 25
        y: 590
        width: parent.width
        color: "White"
        font.pixelSize: 30
        text: "City Centre "

    }
    Text {
        x: 320
        y: 590
        width: parent.width
        color: "LightBlue"
        font.pixelSize: 35
        text: municipality

    }

    }

Button {
    id:btn
    x:300
    y: 630

    text: "View Details"
   onClicked:
   {
       pageStack.push(Qt.resolvedUrl("FifthPage.qml"))

   }
}

Button {
    id:btn2
    x:300
    y: 630+100

    text: "Details Map"
   onClicked:
   {
       pageStack.push(Qt.resolvedUrl("FourthPage.qml"))

   }
}

}

}


