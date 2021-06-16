NAME         = QtUDT
TARGET       = $${NAME}

QT           = core
QT          -= gui
QT          += network
QT          += script
QT          += Essentials

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtudt.h

include ($${PWD}/UDT/UDT.pri)

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)
