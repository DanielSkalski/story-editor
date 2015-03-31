#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T15:24:49
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StoryEditor
TEMPLATE = app


SOURCES += main.cpp\
        UI/mainwindow.cpp \
    UI/Widgets/StoryGraphWidget.cpp \
    Model/Situation.cpp \
    Model/Choice.cpp \
    UI/GraphicsItems/SituationNode.cpp \
    UI/GraphicsItems/ChoiceEdge.cpp \
    Model/StoryManager.cpp \
    UI/Widgets/ItemPropertiesWidget.cpp \
    Model/ContentModelBase.cpp

HEADERS  += UI/mainwindow.h \
    UI/Widgets/StoryGraphWidget.h \
    Model/Situation.h \
    Model/Choice.h \
    UI/GraphicsItems/SituationNode.h \
    UI/GraphicsItems/ChoiceEdge.h \
    Model/StoryManager.h \
    UI/Widgets/ItemPropertiesWidget.h \
    Model/ContentModelBase.h
