import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
//import QtLocation 5.5


/**
  * Implements the left side info with: 1.) reach
  *                                     2.) internal temperature
  *                                     3.) tirepressure
  *                                     4.) mileage
  *                                     5.) outside temperatur
  *
  */
Item{
    id: hfuInfoLeft

    Image{
        x: 168
        y: 5
        z: -3
        source: "bilder/Info.png"
    }

    Text{
        id: reach
        x: 417
        y: 24
        z: 2

        text: "500 km"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: internaltemperature
        x: 350
        y: 126
        z: 2

        text: "20 °C"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: tirepressure
        x: 315
        y: 230
        z: 2

        text: "2.5 bar"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: mileage
        x: 355
        y: 333
        z: 2

        text: "100 km"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: outsidetemperature
        x: 430
        y: 437
        z: 2

        text: "25 °C"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

}
