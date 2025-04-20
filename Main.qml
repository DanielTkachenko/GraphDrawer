import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import plotview

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Graph Drawer")

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Rectangle{
            id: header
            Layout.fillWidth: true
            height: 60
            color: "#38e7a0"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10
                anchors.left: parent.left
                anchors.leftMargin: 10

                Button {
                    height: 30
                    text: "Загрузить файл"
                    onClicked: fileDialog.open()
                }

                Text {
                    text: fileDialog.selectedFile !== "" ? fileDialog.selectedFile : "Файл не выбран"
                    wrapMode: Text.WrapAnywhere
                    color: "white"
                    font.pixelSize: 10
                    verticalAlignment: Text.AlignHCenter
                }
            }
        }

        Rectangle{
            id: body
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "black"

            PlotView{
                objectName: "PlotView"
                anchors.fill: parent
                anchors.margins: 0
                id: graph
            }
        }

        Rectangle{
            id: footer
            Layout.fillWidth: true
            height: 50
            color: "#cccccc"
        }
    }

    FileDialog {
        id: fileDialog
        title: "Выберите файл с данными"
        nameFilters: ["S1p files (*.s1p)","Text files (*.txt)",  "All files (*)"]
        onAccepted: function() {
            plotController.buildPlot(fileDialog.selectedFile)
        }
    }


}
