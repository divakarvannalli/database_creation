import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.2
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.3

ApplicationWindow {
visible: true

ListView{
    model: queryModel
    anchors.fill: parent
    delegate: Item{
        id :del
        height: 100
        width: parent.width
//        anchors.fill: parent
        //text : index
        SwipeView{
            id : swipeview
            anchors.fill: parent
            //height: 100
            //width: parent.width
            currentIndex: 0
            Item {
                Text {
                    text: qno+"."+question
                }
            }
            Item {
                Text {
                    text: description
                }
            }
                        Item {

                            RowLayout {
                                anchors.fill: parent
                                //spacing: 10
                                Repeater {
                                id :rp
                                model: 5
                                RadioButton{
                                    id : rd
                                    height: 10
                                    width: 10
                                    text:(index == 0) ? option1 : ((index == 1) ? option2 :((index == 2) ? option3 :((index == 3) ? option4 :option5)))
                                    visible: (text == "NULL") ? false : true
                                    onClicked: {
                                        console.log(index+1);

                                    }
                                }
                            }
                        }
                    }
        }

        PageIndicator {
            id: indicator

            count: swipeview.count
            currentIndex: swipeview.currentIndex

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
}
