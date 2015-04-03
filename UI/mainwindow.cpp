#include "mainwindow.h"

#include <QHBoxLayout>

#include "Widgets/StoryGraphWidget.h"
#include "Widgets/ItemPropertiesWidget.h"
#include "Widgets/StoryItemsListWidget.h"
#include "Model/StoryManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_StoryManager = new StoryManager();

    m_StoryGraphWidget = new StoryGraphWidget(m_StoryManager, this);
    m_ItemPropertiesWidget = new ItemPropertiesWidget(this);
    m_StoryItemsListWidget = new StoryItemsListWidget(m_StoryManager, this);

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(m_StoryItemsListWidget);
    layout->addWidget(m_StoryGraphWidget);
    layout->addWidget(m_ItemPropertiesWidget);

    QWidget *layoutWidget = new QWidget();
    layoutWidget->setLayout(layout);

    setCentralWidget(layoutWidget);

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
