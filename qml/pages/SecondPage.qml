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

 property string verdict;
 property string img;
 property string pla_img;

 property string addressOfUser;


 Component.onCompleted:
 {
     addressOfUser = rating.MyBusStop;


  var score = rating.TotalScore;
     if(addressOfUser=="karankokatu,lappeenranta"){pla_img="karan.jpeg";}
     else if(addressOfUser=="huopatehtaankatu,lappeenranta"){pla_img="Huopatehtaankatu.jpeg";}
     else if(addressOfUser=="kaivosuonkatu,lappeenranta"){pla_img="Kaivosuonkatu.jpeg";}
     else if(addressOfUser=="kalliopellonkatu,lappeenranta"){pla_img="Kalliopellonkatu.jpeg";}
     else if(addressOfUser=="kangastuvankatu,lappeenranta"){pla_img="Kangastuvankatu.jpeg";}
     else if(addressOfUser=="katajakatu,lappeenranta"){pla_img="Katajakatu.jpeg";}
     else if(addressOfUser=="korpimetsankatu,lappeenranta"){pla_img="Korpimetsankatu.jpeg";}
     else if(addressOfUser=="korpraalinkuja,lappeenranta"){pla_img="Korpraalinkuja.jpeg";}
     else if(addressOfUser=="laserkatu,lappeenranta"){pla_img="Laserkatu.jpeg";}
     else if(addressOfUser=="leirikatu,lappeenranta"){pla_img="Leirikatu.jpeg";}
     else if(addressOfUser=="linnunrata,lappeenranta"){pla_img="Linnunrata.jpeg";}
     else if(addressOfUser=="punkkerikatu,lappeenranta"){pla_img="Punkkerikatu.jpeg";}
     else if(addressOfUser=="reippaankatu,lappeenranta"){pla_img="Reippaankatu.jpeg";}
     else if(addressOfUser=="ruskonlahdenkatu,lappeenranta"){pla_img="Ruskonlahdenkatu.jpeg";}
     else if(addressOfUser=="savonkatu,lappeenranta"){pla_img="Savonkatu.jpeg";}
     else if(addressOfUser=="skinnarilankatu,lappeenranta"){pla_img="Skinnarilankatu.jpeg";}
     else if(addressOfUser=="snellmaninkatu.jpeg,lappeenranta"){pla_img="Snellmaninkatu.jpeg";}
     else if(addressOfUser=="taipalsaarentie,lappeenranta"){pla_img="Taipalsaarentie.jpeg";}
     else if(addressOfUser=="teknologiapuistonkatu,lappeenranta"){pla_img="Teknologiapuistonkatu.jpeg";}
     else if(addressOfUser=="upseeritie,lappeenranta"){pla_img="Upseeritie.jpeg";}
     else if(addressOfUser=="vainolankatu,lappeenranta"){pla_img="Vainolankatu.jpeg";}
     else{pla_img="no_image.jpg";}



     if(score>4)
     {verdict="Nice place! You got the best deal!!";
          img="5star.png"
     }
     else if(score>3)
     {verdict="Good place!";
      img="4star.png";}
     else if(score>2)
     {verdict="It could have been worse ";
      img="3star.png";}
     else if(score>1)
     {verdict="Middle of nowhere!! ";
      img="2star.png";}
     else if(score>0){verdict="Time to change the place!!";
     img="1star.png";}
     else
     {verdict="Are you sure this place is available?";
          img="0star.png";}
 }




 SilicaListView {

     anchors.fill: parent

     header: PageHeader {
         title: "Rate My Place"

     }

     Column {
         id: column


       //  SectionHeader { text: "Busy indicator" }


         Rectangle{
             id: rect
             width: Screen.width
             height: Screen.height
             color:"transparent"


         Text {
             x: 25
             y: 110
             width: parent.width
             color: "White"
             font.pixelSize: 45
             text: "We rate your place: "

         }


Image{
id: img2
width: 190
height:160
x:25
y:185
source: pla_img


}
         Text {
             id: result
             x: 350
             y: 200
             width: parent.width
             color: "LightBlue"
             font.pixelSize: 120
             //text: testRating.TotalScore
             text: rating.TotalScore
         }


         Image {

             id: image1
              width: 150
              height:37
              x:25
              y:400
             source: img
          }


         Text{
             id: verdict1
             x: 25
             y: 445
             width: parent.width
             color: "White"
             font.pixelSize: 30
             text: verdict

         }



         Button {
             x:300
             y: 530

             text: "View Result"
             onClicked:{

                // pageStack.pop(Qt.resolvedUrl("Page1.qml"));
                 pageStack.push(Qt.resolvedUrl("ThirdPage.qml"));

             }
         }




         }





         }
     }







}
