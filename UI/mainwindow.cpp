#include "mainwindow.h"

#include <QHBoxLayout>
#include <QDockWidget>
#include <QMenu>
#include <QtWidgets>

#include "Widgets/StoryGraphWidget.h"
#include "Widgets/ItemPropertiesWidget.h"
#include "Widgets/StoryItemsListWidget.h"
#include "Model/StoryManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_StoryManager = new StoryManager();

    m_StoryGraphWidget = new StoryGraphWidget(m_StoryManager, this);
    m_ItemPropertiesWidget = new ItemPropertiesWidget(m_StoryManager, this);
    m_StoryItemsListWidget = new StoryItemsListWidget(m_StoryManager, this);

    setCentralWidget(m_StoryGraphWidget);

    createActions();
    createMenus();
    createDockWindows();

    setWindowTitle(tr("Story Editor"));

    setUnifiedTitleAndToolBarOnMac(true);

    connect(m_StoryGraphWidget, SIGNAL(situationSelectionChanged(Situation*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Situation*)));

    connect(m_StoryGraphWidget, SIGNAL(choiceSelectionChanged(Choice*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Choice*)));

    connect(m_StoryItemsListWidget, SIGNAL(situationClicked(Situation*)),
            m_StoryGraphWidget, SLOT(markSituationAsSelected(Situation*)));

    connect(m_StoryItemsListWidget, SIGNAL(choiceClicked(Choice*)),
            m_StoryGraphWidget, SLOT(markChoiceAsSelected(Choice*)));

    connect(m_StoryGraphWidget, SIGNAL(situationSelectionChanged(Situation*)),
            m_StoryItemsListWidget, SLOT(markSituationAsSelected(Situation*)));

    connect(m_StoryGraphWidget, SIGNAL(choiceSelectionChanged(Choice*)),
            m_StoryItemsListWidget, SLOT(markChoiceAsSelected(Choice*)));
}

MainWindow::~MainWindow()
{
    delete m_StoryManager;
}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    storyItemsMenu = menuBar()->addMenu(tr("Story &Items"));

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
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
