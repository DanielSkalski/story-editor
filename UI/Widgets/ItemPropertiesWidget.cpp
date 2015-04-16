#include "ItemPropertiesWidget.h"

#include "Model/Situation.h"
#include "Model/Choice.h"
#include "PropertiesWidgets/ChoicePropertiesWidget.h"
#include "PropertiesWidgets/SituationPropertiesWidget.h"


ItemPropertiesWidget::ItemPropertiesWidget(StoryManager *storyManager, QWidget *parent)
    : QWidget(parent), m_StoryManager(storyManager), m_Current(nullptr)
{
    m_SituationProperties = new SituationPropertiesWidget(m_StoryManager, this);
    m_ChoiceProperties = new ChoicePropertiesWidget(m_StoryManager, this);

    m_SituationProperties->hide();
    m_ChoiceProperties->hide();

    setMinimumSize(300, 100);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{

}

void ItemPropertiesWidget::switchCurrentTo(ContentModelPropertiesWidget *widget)
{
    if (m_Current != nullptr)
    {
        m_Current->applyChanges();
    }

    m_Current = widget;
}

void ItemPropertiesWidget::showPropertiesOf(Situation *situation)
{
    switchCurrentTo(m_SituationProperties);

    m_ChoiceProperties->hide();
    m_SituationProperties->showPropertiesOf(situation);
    m_SituationProperties->show();
}

void ItemPropertiesWidget::showPropertiesOf(Choice *choice)
{
    switchCurrentTo(m_ChoiceProperties);

    m_SituationProperties->hide();
    m_ChoiceProperties->showPropertiesOf(choice);
    m_ChoiceProperties->show();
}
