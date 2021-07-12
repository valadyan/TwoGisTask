import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Top15")

    Rectangle {
        id: histogram
        anchors.fill: parent
        color: "green"
        property int maxTopNum: 0

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
                }
            }
        }
    }

    ListModel{
        id: topModel
    }

    WorkerScript{
        id: myWorker
        source: "WorkScripts.mjs"

        onMessage: histogram.maxTopNum = histogram.maxTopNum < messageObject.maxNum ?
                       messageObject.maxNum : histogram.maxTopNum
    }

    function updateNumOfWord(word, num){
        myWorker.sendMessage({'action': 'updateNumOfWord', 'model': topModel,
                             'word': word, 'num': num});
        histogram.update()
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
