#include "mainwindow.h"

#include <QHBoxLayout>

#include "Widgets/StoryGraphWidget.h"
#include "Widgets/ItemPropertiesWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_StoryGraphWidget = new StoryGraphWidget(this);
    m_ItemPropertiesWidget = new ItemPropertiesWidget(this);

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(m_StoryGraphWidget);
    layout->addWidget(m_ItemPropertiesWidget);

    QWidget *layoutWidget = new QWidget();
    layoutWidget->setLayout(layout);

    setCentralWidget(layoutWidget);

    connect(m_StoryGraphWidget, SIGNAL(situationSelectionChanged(Situation*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Situation*)));

    connect(m_StoryGraphWidget, SIGNAL(choiceSelectionChanged(Choice*)),
            m_ItemPropertiesWidget, SLOT(showPropertiesOf(Choice*)));
}
