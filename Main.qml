import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import filereader

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Graph Drawer")

    Column {
            anchors.fill: parent
            spacing: 10
            padding: 20

            Row {
                spacing: 10

                Button {
                    text: "Загрузить файл"
                    onClicked: fileDialog.open()
                }

                Text {
                    text: fileDialog.fileUrl !== "" ? fileDialog.fileUrl : "Файл не выбран"
                    wrapMode: Text.WrapAnywhere
                    width: 500
                }
            }
        }

    FileReader{
        id: fileReader
    }

    /*Connections {
        target: fileReader
        onDataLoaded: function(points) {
            lineSeries.clear()
            for (var i = 0; i < points.length; i++) {
                lineSeries.append(points[i].x, points[i].y)
            }
        }
    }*/

    FileDialog {
        id: fileDialog
        title: "Выберите файл с данными"
        nameFilters: ["S1p files (*.s1p)","Text files (*.txt)",  "All files (*)"]
        onAccepted: fileReader.load(fileDialog.selectedFile)
    }

}
//}
