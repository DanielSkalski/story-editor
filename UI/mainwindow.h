#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StoryGraphWidget;
class ItemPropertiesWidget;
class StoryItemsListWidget;
class StoryManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    StoryManager *m_StoryManager;

    StoryGraphWidget *m_StoryGraphWidget;
    ItemPropertiesWidget *m_ItemPropertiesWidget;
    StoryItemsListWidget *m_StoryItemsListWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
