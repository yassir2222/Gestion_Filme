QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    afficher_billet.cpp \
    afficher_seance.cpp \
    billet.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    salle.cpp \
    seance.cpp

HEADERS += \
    afficher_billet.h \
    afficher_seance.h \
    billet.h \
    client.h \
    mainwindow.h \
    salle.h \
    seance.h

FORMS += \
    afficher_billet.ui \
    afficher_seance.ui \
    billet.ui \
    client.ui \
    mainwindow.ui \
    salle.ui \
    seance.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
