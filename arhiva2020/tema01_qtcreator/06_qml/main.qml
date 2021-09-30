import QtQuick 2.6
import QtQuick.Controls 2.0
import io.qt.examples.backend 1.0

// Da bi spojili C++ backend sa QML frontendom potrebno je uraditi sledece stvari:
// 1) Dodati Q_PROPERTY u okviru backend klase (pogledati backend.h)
// 2) Definisati objekat u okviru QML-a (pogledati main.qml - ovaj fajl)
// 3) Registrovati backend klasu u okviru main.cpp (pogledati main.cpp)

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    // Backend QObject koji je implementiran u C++-u
    BackEnd {
        id: backend
    }

    TextField {
        y: 19
        anchors.horizontalCenterOffset: 0
        placeholderText: qsTr("Insert file name here...")
        anchors.horizontalCenter: parent.horizontalCenter

        onTextChanged: {
            // Zasto ne moze samo: content.text = backend.content?
            // 'backent.content = text' poziva setter sa argumentom text
            //      sto u ovom slucaju znaci da se postavlja sadrzaj datoteke
            //      ako ona postoji, a u suprotnom praznu nisku
            //
            // 'content.text = backed.content' samo postavlja tekst
            //
            // Prva linija mora da se izvrsi kako bi se pozvao setter koji
            // cita sadrzaj datoteke (ako ona postoji)
            backend.content = text
            content.text = backend.content
        }
    }

    Text {
        id: content
        x: 0
        y: 76
        width: 300
        height: 404
        text: ""
        font.family: "Courier"
        fontSizeMode: Text.Fit
    }
}
