import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("A simple Player")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: actions.openFileAction }
            MenuItem { action: actions.openFolderAction }
        }

        Menu {
            title: qsTr("&Help")
            MenuItem { action: actions.aboutAction }
        }
    }

    header: ToolBar {
        RowLayout {
            ToolButton { action: actions.openFileAction }
            ToolButton { action: actions.openFolderAction }
        }
    }



    //Actions
    Actions {
        id: actions
        openFileAction.onTriggered: { dialogs.openFileDialog() }
        openFolderAction.onTriggered: { dialogs.openFolderDialog() }
        aboutAction.onTriggered: { dialogs.openAboutDialog() }
    }

    Dialogs {
        id: dialogs
        fileOpenDialog.onAccepted: {
            content.setfilesModel(fileOpenDialog.selectedFiles)
        }
        folderOpenDialog.onAccepted: {
            content.setfolderModel(folderOpenDialog.selectedFolder)
        }
    }

    Content {
        id: content
        anchors.fill: parent
    }

}
