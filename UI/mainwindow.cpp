#include "mainwindow.h"

#include <QHBoxLayout>
#include <QDockWidget>
#include <QMenu>
#include <QtWidgets>

#include "IO/StoryFile/StoryFileWriter.h"
#include "IO/StoryFile/StoryFileReader.h"

#include "Widgets/StoryGraphWidget.h"
#include "Widgets/ItemPropertiesWidget.h"
#include "Widgets/StoryItemsListWidget.h"
#include "Model/StoryManager.h"
#include "Model/Story.h"
#include "Dialogs/CreateChoiceDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_StoryManager = new StoryManager(this);
    m_StoryManager->load(Story::createEmptyStory());

    m_StoryFileWriter = new StoryFileWriter(this);
    m_StoryFileReader = new StoryFileReader(this);

    m_StoryGraphWidget = new StoryGraphWidget(m_StoryManager, this);
    m_ItemPropertiesWidget = new ItemPropertiesWidget(m_StoryManager, this);
    m_StoryItemsListWidget = new StoryItemsListWidget(m_StoryManager, this);

    setCentralWidget(m_StoryGraphWidget);

    createActions();
    createMenus();
    createDockWindows();

    setWindowTitle(tr("Story Editor"));

    setUnifiedTitleAndToolBarOnMac(true);

    connect(m_StoryManager, SIGNAL(loadedStory()),
            m_ItemPropertiesWidget, SLOT(hideProperties()));

    connect(m_StoryGraphWidget, SIGNAL(situationSelectionChanged(Situation*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Situation*)));

    connect(m_StoryGraphWidget, SIGNAL(choiceSelectionChanged(Choice*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Choice*)));

    connect(m_StoryGraphWidget, SIGNAL(situationSelectionChanged(Situation*)),
            m_StoryItemsListWidget, SLOT(markSituationAsSelected(Situation*)));

    connect(m_StoryGraphWidget, SIGNAL(choiceSelectionChanged(Choice*)),
            m_StoryItemsListWidget, SLOT(markChoiceAsSelected(Choice*)));


    connect(m_StoryItemsListWidget, SIGNAL(situationClicked(Situation*)),
            m_StoryGraphWidget, SLOT(markSituationAsSelected(Situation*)));

    connect(m_StoryItemsListWidget, SIGNAL(choiceClicked(Choice*)),
            m_StoryGraphWidget, SLOT(markChoiceAsSelected(Choice*)));


    connect(m_StoryItemsListWidget, SIGNAL(createSituationButtonClicked()),
            this, SLOT(createSituation()));

    connect(m_StoryItemsListWidget, SIGNAL(createChoiceButtonClicked()),
            this, SLOT(createChoice()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    newStoryAction = new QAction(tr("&New story"), this);
    newStoryAction->setShortcut(QKeySequence::New);
    connect(newStoryAction, SIGNAL(triggered()), this, SLOT(newStory()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save as..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exportToJsonAction = new QAction(tr("Export to json"), this);
    connect(exportToJsonAction, SIGNAL(triggered()), this, SLOT(exportToJson()));

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    createSituationAction = new QAction(tr("Create situation"), this);
    connect(createSituationAction, SIGNAL(triggered()), this, SLOT(createSituation()));

    createChoiceAction = new QAction(tr("Create choice"), this);
    connect(createChoiceAction, SIGNAL(triggered()), this, SLOT(createChoice()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newStoryAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exportToJsonAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    storyItemsMenu = menuBar()->addMenu(tr("Story &Items"));
    storyItemsMenu->addAction(createSituationAction);
    storyItemsMenu->addAction(createChoiceAction);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Properties"), this);
    dock->setWidget(m_ItemPropertiesWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Story items"), this);
    dock->setWidget(m_StoryItemsListWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::newStory()
{
    m_StoryManager->load(Story::createEmptyStory());
}

void MainWindow::open()
{

}

void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save Story"),
                QString(),
                "Story files (*.stf)");

    if (!filename.isEmpty())
    {
        m_StoryFileWriter->write(filename, m_StoryManager->story());
    }
}

void MainWindow::saveAs()
{

}

void MainWindow::exportToJson()
{

}

void MainWindow::about()
{
    QMessageBox::information(this, "About",
                             "Story Editor version 0.1\n"
                             "Author: Daniel Skalski");
}

void MainWindow::createSituation()
{
    m_StoryManager->createEmptySituation();
}

void MainWindow::createChoice()
{
    auto dialog = new CreateChoiceDialog(m_StoryManager, this);
    dialog->exec();
}
