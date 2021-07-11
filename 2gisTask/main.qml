import QtQuick 2.12
import QtQuick.Window 2.12

//import BackLogic 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Top15")

//    TopItem {
//        word: "Amelie"
//        num: 65
//    }
    //        ListElement{
    //            word: "Keks"
    //            num: 5
    //        }
    //        ListElement{
    //            word: "Salo"
    //            num: 23
    //        }
    //        ListElement{
    //            word: "masjanja"
    //            num: 1
    //        }
    //        ListElement{
    //            word: "palo"
    //            num: 50
    //        }

    ListModel{
        id: topModel
    }

    Rectangle {
        id: histogram
        anchors.fill: parent
        color: "green"
        property int maxTopNum: 50

        Column {
            id: column
            property int bord: 10
            x: column.bord; y: column.bord
            spacing: column.bord

            Repeater {
                model: topModel

                GistRow {
                    width: histogram.width - column.bord * 2
                    height: ((histogram.height - column.bord) / topModel.count) - column.bord

                    maximum: histogram.maxTopNum
                    value: model.num
                    word: model.word
//                    ColorAnimation on secondColor { duration: r; from: "steelblue"; to: "#CD96CD"; loops: Animation.Infinite }
                }
            }
        }
    }

    WorkerScript{
        id: myWorker
        source: "WorkScripts.mjs"

        onMessage: myText.text = messageObject.reply
    }

    function updateNumOfWord(word, num){
        myWorker.sendMessage({'action': 'updateNumOfWord', 'model': topModel,
                             'word': word, 'num': num});
    }
    function changeTopElem(oldWord, word, num){
        myWorker.sendMessage({'action': 'changeTopElem', 'model': topModel,
                             'oldWord': oldWord, 'word': word, 'num': num});
    }
    function sortTop(){
        myWorker.sendMessage({'action': 'sortTop', 'model': topModel});
    }
    Component.onCompleted: {
        changedNum.connect(updateNumOfWord);
        changedTopElem.connect(changeTopElem);
        endOfFile.connect(sortTop);
    }
}
