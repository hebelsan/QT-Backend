import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
//import QtLocation 5.5

/**
  * Implements the phone on the left side
  *
  * Static image with a list of possible contacts
  *
  */
Item{
    //color: "green"
    id: hfuPhoneLeft

    Image{
        x: 238
        y: 60
        width: 177
        height: 250
        z: 1
        source: "bilder/Phone.png"
    }

    ListView {
        id: listView1
        width: 240
        height: 250
        transformOrigin: Item.Center
        x: 248
        y: 358
        highlightRangeMode: ListView.StrictlyEnforceRange
        currentIndex: canEventSink.selectetContact
        highlightFollowsCurrentItem: true

        highlight: Component{
            Rectangle{
                width: listView1.width
                y: listView1.currentItem.y
                color: Qt.rgba(0,0,0,0)

                Behavior on y{
                    SpringAnimation{
                        spring: 3
                        damping: 0.2

                    }
                    //console.log(ListView1.currentItem)
                }
            }
        }

        onCurrentIndexChanged:{
            for (var i=0; i<6; i+=1){
                listModel.setProperty(i, "Textcolor", "light");
            }
            //listModel.setProperty(listView1.currentIndex, "Textcolor", "red");
        }

        model: ListModel {
            id: listModel
            ListElement {
                name: "Patrick Gonser"
                phone: "015208888888"
                Textcolor: "lightred"
            }

            ListElement {
                name: "Moritz Haas"
                phone: "015208888888"
                Textcolor: "lightred"
            }

            ListElement {
                name: "Andreas Heidenreich"
                phone: "015208888888"
                Textcolor: "white"
            }

            ListElement {
                name: "Matthieu Theurer"
                phone: "015208888888"
                Textcolor: "white"
            }

            ListElement {
                name: "Igor Blum"
                phone: "015208888888"
                Textcolor: "white"
            }
            ListElement {

            }
        }

        delegate: Item {
            width: 240
            height: 60
            Row {
                anchors.verticalCenter: parent.verticalCenter
                id: row1
                Item{

                    anchors.right: row1.right
                    Text {
                        id:nameTxt
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        color: "red"
                    }
                    Text {
                        id: phoneText
                        anchors.top: nameTxt.bottom
                        anchors.topMargin: 5
                        anchors.leftMargin: 20
                        font.pointSize: 9
                        text: phone
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        color: "white"
                    }
                }
            }
        }
    }

}
