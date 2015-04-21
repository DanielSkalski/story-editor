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

    QMenu *fileMenu;
    QMenu *storyItemsMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createDockWindows();
};

#endif // MAINWINDOW_H
