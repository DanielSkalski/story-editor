#include "StoryItemsListWidget.h"

#include "Model/StoryManager.h"
#include "Model/Situation.h"
#include "Model/Choice.h"
#include "UI/ListModels/ChoiceListModel.h"
#include "UI/ListModels/SituationListModel.h"
#include "UI/Dialogs/CreateChoiceDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QGroupBox>


StoryItemsListWidget::StoryItemsListWidget(StoryManager *storyManager, QWidget *parent)
    : QWidget(parent), m_StoryManager(storyManager)
{
    m_ChoicesListView = new QListView(this);
    m_SituationsListView = new QListView(this);

    m_CreateSituationButton = new QPushButton(tr("Create"), this);
    m_CreateChoiceButton = new QPushButton(tr("Create"), this);

    auto choicesList = m_StoryManager->choices();
    m_ChoiceListModel = new ChoiceListModel(choicesList);
    m_ChoicesListView->setModel(m_ChoiceListModel);

    auto situations = m_StoryManager->situations();
    m_SituationListModel = new SituationListModel(situations);
    m_SituationsListView->setModel(m_SituationListModel);

    setupLayout();

    connect(m_SituationsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(onSituationClicked(QModelIndex)));
    connect(m_ChoicesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(onChoiceClicked(QModelIndex)));

    connect(m_CreateSituationButton, SIGNAL(clicked()), this, SLOT(onCreateSituationButtonClicked()));
    connect(m_CreateChoiceButton, SIGNAL(clicked()), this, SLOT(onCreateChoiceButtonClicked()));

    connect(m_StoryManager, SIGNAL(addedSituation(Situation*)), this, SLOT(addSituation(Situation*)));
    connect(m_StoryManager, SIGNAL(addedChoice(Choice*)), this, SLOT(addChoice(Choice *)));
}

StoryItemsListWidget::~StoryItemsListWidget()
{
    delete m_ChoiceListModel;
    delete m_SituationListModel;
}

void StoryItemsListWidget::setupLayout()
{
    setMinimumSize(150, 200);
    setMaximumWidth(300);

    QGroupBox *situationsGroup = new QGroupBox(tr("Situations"), this);
    QGroupBox *choicesGroup = new QGroupBox(tr("Choices"), this);

    auto situationsGroupLayout = new QVBoxLayout();
    situationsGroupLayout->addWidget(m_SituationsListView);
    situationsGroupLayout->addWidget(m_CreateSituationButton);
    situationsGroup->setLayout(situationsGroupLayout);

    auto choicesGroupLayout = new QVBoxLayout();
    choicesGroupLayout->addWidget(m_ChoicesListView);
    choicesGroupLayout->addWidget(m_CreateChoiceButton);
    choicesGroup->setLayout(choicesGroupLayout);

    auto layout = new QVBoxLayout();
    layout->addWidget(situationsGroup);
    layout->addWidget(choicesGroup);

    setLayout(layout);
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

void StoryItemsListWidget::addChoice(Choice *choice)
{
    m_ChoiceListModel->addItem(choice);
}

void StoryItemsListWidget::onSituationClicked(const QModelIndex &modelIndex)
{
    auto situation = m_SituationListModel->getItem(modelIndex);
    markSituationAsSelected(situation);

    emit situationClicked(situation);
}

void StoryItemsListWidget::onChoiceClicked(const QModelIndex &modelIndex)
{
    auto choice = m_ChoiceListModel->getItem(modelIndex);
    emit choiceClicked(choice);
}

void StoryItemsListWidget::onCreateSituationButtonClicked()
{
    emit createSituationButtonClicked();
}

void StoryItemsListWidget::onCreateChoiceButtonClicked()
{
    emit createChoiceButtonClicked();
}
