import QtQuick 2.0
import Sailfish.Silica 1.0




Page {
    property int seconds : 0
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: parent.width

            PageHeader {
                id: ph
                title: "Rate My Place" }

            SectionHeader {
                id:sh
                text: "Searching for result..." }
            Row {
                spacing: Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter

                BusyIndicator {
                    id:indicator1
                    running: true
                    size: BusyIndicatorSize.Small
                    anchors.verticalCenter: parent.verticalCenter
                }
                BusyIndicator {
                    id:indicator2
                    running: true
                    size: BusyIndicatorSize.Medium
                    anchors.verticalCenter: parent.verticalCenter
                }
                BusyIndicator {
                    id:indicator3
                    running: true
                    size: BusyIndicatorSize.Large
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Timer{
                interval: 5
                running:true
                repeat:true
                onTriggered:
                {
                    seconds= seconds+1;
                    if(seconds==3){pageStack.push(Qt.resolvedUrl("SecondPage.qml"))}
                    if(seconds>500){

                        indicator1.opacity=0.0
                        indicator2.opacity=0.0
                        indicator3.opacity=0.0
                        ph.opacity=0.0
                        sh.opacity=0.0

                    }
                         else{
                             indicator1.running=true
                         }
                     }
            }

        }
    }
}
