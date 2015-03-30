#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StoryGraphWidget;
class ItemPropertiesWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    StoryGraphWidget *m_StoryGraphWidget;
    ItemPropertiesWidget *m_ItemPropertiesWidget;

public:
    MainWindow(QWidget *parent = 0);
};

#endif // MAINWINDOW_H
