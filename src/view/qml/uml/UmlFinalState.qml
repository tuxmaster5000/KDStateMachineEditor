/*
  UmlFinalState.qml

  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

import QtQuick 2.0
import QtQuick.Controls 1.0

import "qrc:///kdsme/qml/util/"
import "qrc:///kdsme/qml/util/theme.js" as Theme

/**
 * Final State representation
 *
 * This is a node in the form of a double-circle
 */
UmlElement {
    id: root

    Rectangle {
        id: rect

        anchors.fill: parent

        color: Theme.stateBackgroundColor
        border.color: Theme.stateBorderColor
        radius: width

        Rectangle {
            anchors {
                fill: parent
                margins: 5
            }

            color: Qt.darker(Theme.stateBorderColor, 1.5)
            radius: parent.radius*0.5
        }
    }

    ChannelizedDropArea {
        id: dropArea

        keys: ["transition"]

        anchors.fill: parent
    }

    states: [
        State {
            when: dropArea.containsDrag
            PropertyChanges {
                target: rect
                color: "#DDDDDD"
            }
        }
    ]

}