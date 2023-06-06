import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import Qt.labs.folderlistmodel

Item {

    function setfilesModel() {
        filesModel.clear()
        for(var i = 0; i < arguments[0].length; i++){
            var data = {"filePath": arguments[0][i]};
            filesModel.append(data);
        }
        listMV.model = filesModel
        listMV.currentIndex = 0
    }

    function setfolderModel() {
        folderModel.folder = arguments[0];
        listMV.model = folderModel;
        listMV.currentIndex = 0;
    }

    ListView {
        id: listMV
        anchors.fill: parent
        spacing: 5

        ListModel {
            id: filesModel
        }

        FolderListModel {
            id: folderModel
            nameFilters: ["*.mp3","*.mp4"]
            showDirs: false  //排除文件夹
        }

        //遍历
        delegate:
            Rectangle {
            id: rec
            width: parent.width
            height: 30
            color: ListView.isCurrentItem ? "red" : "lightyellow"
            Label {
                id: label
                //anchors.centerIn: parent
                text: filePath
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listMV.currentIndex = index;
                    mediaPlayer.source = filePath
                    mediaPlayer.play()
                    console.log("Playing: ", filePath)
                }
            }
        }

        MediaPlayer {
            id: mediaPlayer
            source: ""
            audioOutput: audioOutPut
            //metaData:
        }

        AudioOutput {
            id: audioOutPut
            volume: volumeSlider.value
        }

        Slider {
            id: volumeSlider
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 20
            orientation: Qt.Vertical
            value: 0.8
        }

        Item {
            height: 50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 40

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30

                Button {
                    id: button1
                    text: mediaPlayer.playbackState === MediaPlayer.PlayingState ? qsTr("Pause") : qsTr("Play")
                    onClicked:  {
                        switch (mediaPlayer.playbackState) {
                        case MediaPlayer.PlayingState: mediaPlayer.pause(); break;
                        case MediaPlayer.PausedState: mediaPlayer.play(); break;
                        case MediaPlayer.StoppedState: mediaPlayer.play(); break;
                        }
                    }
                }

                Button {
                    text: qsTr("Stop")
                    onClicked: {
                        mediaPlayer.stop()
                        button1.text = "Play"
                    }
                }
            }



            Slider {
                id: progressSlider
                width: parent.width
                anchors.bottom: parent.bottom
                enabled: mediaPlayer.seekable
                value: mediaPlayer.duration > 0 ? mediaPlayer.position / mediaPlayer.duration : 0
                background: Rectangle {
                    implicitHeight: 8
                    color: "white"
                    radius: 3
                    Rectangle {
                        width: progressSlider.visualPosition * parent.width
                        height: parent.height
                        color: "#1D8BF8"
                        radius: 3
                    }
                }

                //handle: Item{}
                onMoved: {
                    mediaPlayer.position = mediaPlayer.duration * progressSlider.position
                    //console.log(mediaPlayer.metaData.Title)
                }
            }

        }

    }//ListView end
}
