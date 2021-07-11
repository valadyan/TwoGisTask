import QtQuick 2.0

Item {
    id: gistrow

    property int maximum: 0
    property int value: 0
    property string word: ""

    clip: true

    Rectangle {
        id: highlight
        width: Math.floor(gistrow.width * value / maximum)
        height: parent.height
        color: "black"
        Behavior on width { SmoothedAnimation { velocity: 1200 } }
    }

    Text {
        anchors { right: gistrow.right; rightMargin: 6; verticalCenter: parent.verticalCenter }
        color: "white"
        font.bold: true
        text: word + "-" + value
    }
}
