/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

//import com.mycompany.rating 1.0


Page {
    id: page
    property string score:"5"
    property int textAlignment: Text.AlignLeft;
    property string addressToRate;
    property string latlong;
    property string resultXML:"";

    //signal qmlSignal(QString msg)

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        id:sf

        anchors.fill: parent;

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        VerticalScrollDecorator {}
        PullDownMenu {
            MenuItem {
                text: "Show Page 2"
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height





        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: "UI Template"
            }
            Label {
                 x: Theme.paddingLarge
                text: "Rate My Place"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge

            }


            TextField {
                id:tf1
                width: parent.width
                label: "Address"
                placeholderText: "Input your address"
                focus: true


                horizontalAlignment: Text.AlignLeft
               Keys.onReturnPressed:
               {
                parent.focus=true;
                   //column.qmlSignal(text);
                //page.qmlSignal(text)
                //page.addressToRate = text;


                //   rating.beginRating(text);


               }


            }


            /*
            Rating{
                id:theRating


            }*/




            Label {
                id:labelLog
                x: Theme.paddingLarge
                //text: theRating.AddressToRate
               // text:rating.AddressToRate
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge

            }

            function showRequestInfo(text)  {
                   //log.text = log.text + "\n" + text
                   //console.log(text)
                   page.resultXML = page.resultXML+text

               }



            function getTheRate(addressToRate){
                //1. get the lat,long of the center
                page.resultXML = page.resultXML+"testingGetTheRate"




                //2. get if there's any closest atm
                //within 100m

                //within 200m
                //within 400m
                //within 600m
                //within 800m





               // addressToRate


               // return score
            }

        }
    }
}

