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
    Model/ContentModelBase.cpp \
    UI/GraphicsItems/Selectable.cpp \
    UI/GraphicsItems/StoryGraphItemBase.cpp \
    UI/Widgets/StoryItemsListWidget.cpp \
    UI/ListModels/ChoiceListModel.cpp \
    UI/ListModels/SituationListModel.cpp \
    UI/Widgets/PropertiesWidgets/SituationPropertiesWidget.cpp \
    UI/Widgets/PropertiesWidgets/ChoicePropertiesWidget.cpp \
    UI/Widgets/PropertiesWidgets/ContentModelPropertiesWidget.cpp \
    UI/Dialogs/CreateChoiceDialog.cpp \
    Model/Validators/ChoiceValidator.cpp \
    Model/Validators/ValidationResult.cpp \
    Model/Validators/IIdValidator.cpp \
    Model/Validators/SituationValidator.cpp

HEADERS  += UI/mainwindow.h \
    UI/Widgets/StoryGraphWidget.h \
    Model/Situation.h \
    Model/Choice.h \
    UI/GraphicsItems/SituationNode.h \
    UI/GraphicsItems/ChoiceEdge.h \
    Model/StoryManager.h \
    UI/Widgets/ItemPropertiesWidget.h \
    Model/ContentModelBase.h \
    UI/GraphicsItems/Selectable.h \
    UI/GraphicsItems/StoryGraphItemBase.h \
    UI/Widgets/StoryItemsListWidget.h \
    UI/ListModels/ChoiceListModel.h \
    UI/ListModels/SituationListModel.h \
    UI/Widgets/PropertiesWidgets/SituationPropertiesWidget.h \
    UI/Widgets/PropertiesWidgets/ChoicePropertiesWidget.h \
    UI/Widgets/PropertiesWidgets/ContentModelPropertiesWidget.h \
    UI/Dialogs/CreateChoiceDialog.h \
    Model/Validators/ChoiceValidator.h \
    Model/Validators/ValidationResult.h \
    Model/Validators/IIdValidator.h \
    Model/Validators/SituationValidator.h
