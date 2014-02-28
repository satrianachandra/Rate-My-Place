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

import QtWebKit 3.0
//import "OpenLayers.js" as OSM



Page {
    id: page


    property string latit;
    property string longit;

    property string stringDetails;
    property string toShow;

    Component.onCompleted: {
        stringDetails = rating.AddressToRate;
        var stringDetailsArray = stringDetails.split("@");
        toShow = ""



        var atmString = stringDetailsArray[0];
        var hospitalString = stringDetailsArray[1];
        var restaurantString = stringDetailsArray[2];
        var universityString = stringDetailsArray[3];
        var busStopString = stringDetailsArray[4];
        var municipalityString = stringDetailsArray[5];
        var smarketString = stringDetailsArray[6];


        //parsing busStop
        toShow+="Bus Stop\n"
            //if not found anything: |score:5|distance:300
        var busStopStringArray = busStopString.split("$");
        for (var i=1;i<busStopStringArray.length;i++)
        {
            //single element: lat:63|lon:53
            //last element will be like:lat:63|lon:53|score:1|distance:2000
            var latlongArray = busStopStringArray[i].split("|");
            var latit = latlongArray[0].split(":")[1];
            var longit = latlongArray[1].split(":")[1];
            //toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
            if (busStopStringArray.length===2){
                toShow+=rating.getAddress(latit,longit)+"\n";
            }else{
                toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
            }
            if (i==busStopStringArray.length-1){
                toShow+=latlongArray[2]+" "+latlongArray[3];
            }
         }

            //parsing ATM
            toShow+="\n\nATM\n"
                //if not found anything: |score:5|distance:300
            var atmStringArray = atmString.split("$");
            for (i=1;i<atmStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = atmStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];

                //toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                if (atmStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (i==atmStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }


            //parsing Grocery Shop
            toShow+="\n\nGrocery Store\n"
                //if not found anything: |score:5|distance:300
            var sMarketStringArray = smarketString.split("$");
            for (i=1;i<sMarketStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = sMarketStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];
                //toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (sMarketStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                if (i==sMarketStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }


            //parsing Hospital
            toShow+="\n\nHospital\n"
                //if not found anything: |score:5|distance:300
            var hospitalStringArray = hospitalString.split("$");
            for (i=1;i<hospitalStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = hospitalStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];
                //toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (hospitalStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                if (i==hospitalStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }

            //parsing Restaurants
            toShow+="\n\nRestaurant\n"
                //if not found anything: |score:5|distance:300
            var restaurantStringArray = restaurantString.split("$");
            for (i=1;i<restaurantStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = restaurantStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];
                //toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (restaurantStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                if (i==restaurantStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }


            //parsing University
            toShow+="\n\nRestaurant\n"
                //if not found anything: |score:5|distance:300
            var universityStringArray = universityString.split("$");
            for (i=1;i<universityStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = universityStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];
               // toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (universityStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                if (i==universityStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }

            //parsing Municipality
            toShow+="\n\nMunicipality\n"
                //if not found anything: |score:5|distance:300
            var municipalityStringArray = municipalityString.split("$");
            for (i=1;i<municipalityStringArray.length;i++)
            {
                //single element: lat:63|lon:53
                //last element will be like:lat:63|lon:53|score:1|distance:2000
                latlongArray = municipalityStringArray[i].split("|");
                latit = latlongArray[0].split(":")[1];
                longit = latlongArray[1].split(":")[1];
               // toShow+=i+". Lat:"+latit+" Long:"+longit+"\n";
                //toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                if (municipalityStringArray.length===2){
                    toShow+=rating.getAddress(latit,longit)+"\n";
                }else{
                    toShow+=i+". "+rating.getAddress(latit,longit)+"\n";
                }
                if (i==municipalityStringArray.length-1){
                    toShow+=latlongArray[2]+" "+latlongArray[3];
                }
            }


        }




        //parsing atm
        //var atmStringArray = atmString.split("$");









    SilicaListView {
        id:slv
        anchors.fill: parent
        VerticalScrollDecorator {}


        header: PageHeader {
            title: "Details"

        }


       Row{
        Label{
            text:toShow
            x:25
            y:70

        }
       }

    }



}




