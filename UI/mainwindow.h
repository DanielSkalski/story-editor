#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StoryGraphWidget;
class ItemPropertiesWidget;
class StoryItemsListWidget;
class StoryManager;
class StoryFileWriter;
class StoryFileReader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    StoryManager *m_StoryManager;

    StoryFileWriter *m_StoryFileWriter;
    StoryFileReader *m_StoryFileReader;

    StoryGraphWidget *m_StoryGraphWidget;
    ItemPropertiesWidget *m_ItemPropertiesWidget;
    StoryItemsListWidget *m_StoryItemsListWidget;

    QMenu *fileMenu;
    QMenu *storyItemsMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QAction *newStoryAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exportToJsonAction;
    QAction *quitAction;
    QAction *aboutAction;

    QAction *createSituationAction;
    QAction *createChoiceAction;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createDockWindows();

private slots:
    void newStory();
    void open();
    void save();
    void saveAs();
    void exportToJson();
    void about();
    void createSituation();
    void createChoice();
};

#endif // MAINWINDOW_H
