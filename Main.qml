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

            ProgressBar {
                width: parent.width - 40
                height: 30
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50  // Примерный прогресс
            }
        }
    }

    Rectangle {
        objectName: "ErrorMessageDialog"
        id: errorDialog
        width: 300
        height: 180
        color: "#ffffff"
        radius: 12
        visible: false
        z: 2
        anchors.centerIn: parent
        border.color: "#d32f2f"
        border.width: 2
        layer.enabled: true

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Иконка и заголовок
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 8

                Image {
                    source: "qrc:/icons/error.png"  // или замени на локальный путь
                    width: 24
                    height: 24
                }

                Label {
                    text: "Ошибка"
                    font.bold: true
                    font.pointSize: 14
                    color: "#d32f2f"
                }
            }

            // Текст ошибки
            Label {
                objectName: "errorText"
                text: "Произошла непредвиденная ошибка"
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }

            // Кнопка "Ок"
            Button {
                text: "Ок"
                Layout.alignment: Qt.AlignHCenter
                onClicked: errorDialog.visible = false
            }
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
