#include "mainwindow.h"
#include "Widgets/StoryGraphWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_StoryGraphWidget = new StoryGraphWidget(this);
    setCentralWidget(m_StoryGraphWidget);
}
