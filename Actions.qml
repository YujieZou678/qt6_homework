import QtQuick
import QtQuick.Controls

Item {
    property alias openFileAction: openFile
    property alias openFolderAction: openFolder
    property alias aboutAction: about

    Action {
        id: openFile
        text: qsTr("&Add songs...")
        icon.name: "document-open"
    }

    Action {
        id: openFolder
        text: qsTr("Openfol&der...")
        icon.name: "document-open-recent"
    }

    Action {
        id: about
        text: qsTr("&About")
        icon.name: "help-about"
    }
}
