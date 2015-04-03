#include "StoryItemsListWidget.h"

#include "Model/StoryManager.h"
#include "Model/Situation.h"
#include "Model/Choice.h"
#include "UI/ListModels/ChoiceListModel.h"
#include "UI/ListModels/SituationListModel.h"

#include <QVBoxLayout>


StoryItemsListWidget::StoryItemsListWidget(StoryManager *storyManager, QWidget *parent)
    : QWidget(parent), m_StoryManager(storyManager)
{
    setMinimumSize(300, 100);

    m_ChoicesListView = new QListView(this);
    m_SituationsListView = new QListView(this);

    m_CreateSituationButton = new QPushButton(tr("Create"), this);

    auto choicesList = m_StoryManager->choices().toList();
    m_ChoiceListModel = new ChoiceListModel(choicesList);
    m_ChoicesListView->setModel(m_ChoiceListModel);

    auto situations = m_StoryManager->situations().toList();
    m_SituationListModel = new SituationListModel(situations);
    m_SituationsListView->setModel(m_SituationListModel);

    auto layout = new QVBoxLayout();
    layout->addWidget(m_SituationsListView);
    layout->addWidget(m_CreateSituationButton);
    layout->addWidget(m_ChoicesListView);

    connect(m_SituationsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(situationClicked(QModelIndex)));
    connect(m_ChoicesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(choiceClicked(QModelIndex)));

    connect(m_CreateSituationButton, SIGNAL(clicked()), this, SLOT(createSituationButtonClicked()));

    connect(m_StoryManager, SIGNAL(addedSituation(Situation*)), this, SLOT(addSituation(Situation*)));

    setLayout(layout);
}

StoryItemsListWidget::~StoryItemsListWidget()
{
    delete m_ChoiceListModel;
    delete m_SituationListModel;
}

void StoryItemsListWidget::markSituationAsSelected(Situation *situation)
{
    m_ChoicesListView->clearSelection();
    auto index = m_SituationListModel->getIndex(situation);
    m_SituationsListView->setCurrentIndex(index);
}

void StoryItemsListWidget::markChoiceAsSelected(Choice *choice)
{
    m_SituationsListView->clearSelection();
    auto index = m_ChoiceListModel->getIndex(choice);
    m_ChoicesListView->setCurrentIndex(index);
}

void StoryItemsListWidget::addSituation(Situation *situation)
{
    m_SituationListModel->addItem(situation);
}

void StoryItemsListWidget::situationClicked(const QModelIndex &modelIndex)
{
    auto situation = m_SituationListModel->getItem(modelIndex);
    markSituationAsSelected(situation);

    emit situationClicked(situation);
}

void StoryItemsListWidget::choiceClicked(const QModelIndex &modelIndex)
{
    auto choice = m_ChoiceListModel->getItem(modelIndex);
    emit choiceClicked(choice);
}

void StoryItemsListWidget::createSituationButtonClicked()
{
    m_StoryManager->createEmptySituation();
}
