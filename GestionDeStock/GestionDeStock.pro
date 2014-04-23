#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T15:13:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GestionDeStock
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
		article.cpp\
		stock.cpp\
		comboboxcolor.cpp \
    comboboxcategory.cpp

HEADERS  += mainwindow.h\
		article.h\
		datasets.h\
		stock.h\
		comboboxcolor.h \
    comboboxcategory.h

FORMS    += mainwindow.ui
