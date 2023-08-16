import QtQuick
import QtQuick.Controls

import QtQuick.Dialogs
import QtMultimedia
import "myjs.js" as Js

ApplicationWindow {
    id: window
    height: 600
    width: 800
    visible: true
    title: qsTr("Window")

    menuBar: MenuBar {
        Menu {
            id: fileMenu
            title: qsTr("File")

            Action { id: openAction; icon.name: "document-open" ;text: qsTr("&Open") }
            MenuSeparator{}
            Action {
                id: quitAction
                icon.name: "application-exit"
                text: qsTr("&Quit")
                onTriggered: close()
            }
        }

        Menu {
            id: editMenu
            title: qsTr("Edit")

            Action {
                id: copyAction
                text: qsTr("&Copy")
                icon.name: "edit-copy"
            }

            Action {
                text: qsTr("&Cut")
                icon.name: "edit-cut"
            }
        }

        Menu {
            id: toolMenu
            title: qsTr("Tool")
        }
    }

    header: ToolBar {
        Row {
            spacing: 5

            ToolButton {
                action: openAction
                text: ""
                onClicked: playerDialog.open()
            }

            ToolButton {
                action: quitAction
                text: ""
            }

        }

    }

//    footer: TabBar {
//        //
//    }

//    StackView {
//        anchors.fill: parent
//    }

//    Image {
//        anchors.fill: parent
//        id: image
//        source: "start.png"
//    }

    MouseArea {
        anchors.fill: parent

        //释放鼠标 判断单击或者双击
        onReleased: {
            if (m_timer.running) {
                //console.log("我双击了")
                if (window.visibility == ApplicationWindow.FullScreen) {
                    window.showNormal()
                    console.log("我恢复正常大小了")
                    menuBar.visible = true
                    header.visible = true
                } else if (window.visibility == ApplicationWindow.Windowed){
                    window.showFullScreen()
                    console.log("我全屏了")
                    menuBar.visible = false
                    header.visible = false
                }
                m_timer.stop()
            } else m_timer.restart()
        }

    }

    //定时器
    Timer {
        id: m_timer
        interval: 200
        repeat: false

        //单击后200ms没其他单击 判断为单击
        onTriggered: {
            //console.log("我单击了")
            if (mediaPlayer.playbackState == MediaPlayer.PlayingState) {
                mediaPlayer.pause()
                console.log("我暂停了")
            } else {
                mediaPlayer.play()
                console.log("我播放了")
            }
        }
    }

    //全局快捷键 space
    Shortcut {
        sequence: "space"

        onActivated: {
            if (mediaPlayer.playbackState == MediaPlayer.PlayingState) {
                mediaPlayer.pause()
                console.log("我暂停播放了")
            } else if (mediaPlayer.playbackState == MediaPlayer.PausedState) {
                mediaPlayer.play()
                console.log("我开始播放了")
            }
        }
    }
    //全局快捷键 esc
    Shortcut {
        sequence: "esc"

        onActivated: {
            if (window.visibility == ApplicationWindow.FullScreen) {
                window.showNormal()
                console.log("我恢复正常大小了")
                menuBar.visible = true
                header.visible = true
            }
        }
    }
    //打开视频
    FileDialog {
        id: playerDialog
        onAccepted: {
            mediaPlayer.source = "file://" + selectedFile
            mediaPlayer.stop()
            mediaPlayer.play()
        }
    }
    //播放器定义
    MediaPlayer {
        id: mediaPlayer
        source: "file:///root/tmp/Three.Little.Pigs.1933.avi"
        loops: MediaPlayer.Infinite
        audioOutput: audioOutPut
        videoOutput: videoOutput
    }

    AudioOutput {
        id: audioOutPut
    }

    Rectangle {
        id: rect
        color: "black"
        anchors.fill: parent

        //视频载体
        VideoOutput {
            id: videoOutput
            anchors.fill: parent
        }
    }

}

