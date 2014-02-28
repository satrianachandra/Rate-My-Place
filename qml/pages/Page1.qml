import QtQuick 2.0
import Sailfish.Silica 1.0


Page {

 id: page1
    property int seconds : 0
  property int textAlignment: Text.AlignLeft
  property string addressToBeRated


 SilicaListView {

     anchors.fill: parent


     header: PageHeader {
         title: "Rate My Place"

     }

     SectionHeader {
         id:sh
         x:0
         y:200
         opacity: 0.0
         text: "Searching for result..." }




     Column {
         id:column


         Label {
             id: displayedName

         }

         Rectangle{
             id: rect
             width: Screen.width
             height: Screen.height
             color:"transparent"

             Row {
                 x:100
                 y:335//spacing: Theme.paddingLarge
                 //anchors.horizontalCenter: parent.horizontalCenter
                 BusyIndicator {
                   //  x:50
                    // y:200
                     id: indicator1
                     running: true
                     opacity: 0.0
                     size: BusyIndicatorSize.Small
                     anchors.verticalCenter: parent.verticalCenter
                 }
                 BusyIndicator {
                   //  x:100
                   //  y:200
                     id: indicator2
                     running: true
                     opacity: 0.0
                     size: BusyIndicatorSize.Medium
                     anchors.verticalCenter: parent.verticalCenter
                 }
                 BusyIndicator {
                   //  x:150
                   //  y:200
                     id: indicator3
                     running: true
                     opacity: 0.0
                     size: BusyIndicatorSize.Large
                     anchors.verticalCenter: parent.verticalCenter
                 }
             }

         TextField {
             id:tfCity
             x: 45
             y: 130
             width: parent.width
            // label: "Text field"
             font.pixelSize: 40
             placeholderText: "Enter Your City"
           //  validator: RegExpValidator { regExp: /./ }
             focus: true
           //  horizontalAlignment: textAlignment
             EnterKey.onClicked: {
              //   text = "Return key pressed";
                 parent.focus = true;
             }
         }

         TextField {
             id:tfLocation
             x: 45
             y: 210
             width: parent.width
           //  label: "Text field"
             font.pixelSize: 40
             placeholderText: "Enter Your Location"
            //    validator: RegExpValidator { regExp: /./ }
             focus: true
            // horizontalAlignment: textAlignment
             EnterKey.onClicked: {
              //   text = "Return key pressed";
                 parent.focus = true;
                 //addressToBeRated = text;
             }
         }



         Button {
             id: but
             x:300
             y: 430

             text: "Rate My Place !"
             onClicked: {

                 tfCity.opacity=0.0;
                 tfLocation.opacity=0.0;

                 indicator3.opacity=1.0;
                 but.opacity=0.0;
                 sh.opacity=1.0;
                 addressToBeRated = tfLocation.text+","+tfCity.text
                 rating.beginRating(addressToBeRated);
                  pageStack.push(Qt.resolvedUrl("SecondPage.qml"));
                 tfCity.opacity=1.0;
                 tfLocation.opacity=1.0;
                 indicator3.opacity=0.0;
                 but.opacity=1.0;
                 sh.opacity=0.0;
                 //Timer.start();

             }
         }

         Timer{
             interval: 10
             running:false
             repeat:false
             onTriggered:
             {


                 }

                  }


         }


         }
     }

}
