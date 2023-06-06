import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls

Item {
    property alias fileOpenDialog: openFile
    property alias folderOpenDialog: openFolder

    function openFileDialog() { openFile.open() }
    function openFolderDialog() { openFolder.open() }
    function openAboutDialog() { aboutDialog.open() }

    FileDialog {
        id: openFile
        title: "Select some song files"
        //currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        fileMode: FileDialog.OpenFiles
        nameFilters: [ "Music files (*.mp3 *.mp4)" ]
    }

    FolderDialog {
        id: openFolder
        //currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        title: "Select a music folder"
    }

    Dialog {
        id: aboutDialog
        title: qsTr("About")
        Label {
            anchors.fill: parent
            text: qsTr("A QML Music Viewer\n")
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
