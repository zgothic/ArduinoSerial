SOURCES += \
    main.cpp

QT += serialport widgets core

HEADERS += \
    smarttable.h \
    task.h \
    mainwindow.h \
    tasklistwidget.h \
    newtaskwindow.h \
    lockdisplay.h

RESOURCES += \
    resource.qrc

DISTFILES += \
    style.qss \
    myrc.rc

CONFIG += qtestlib
