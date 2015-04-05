#include "ItemPropertiesWidget.h"

#include "Model/Situation.h"
#include "Model/Choice.h"
#include "PropertiesWidgets/ChoicePropertiesWidget.h"
#include "PropertiesWidgets/SituationPropertiesWidget.h"


ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent)
    : QWidget(parent)
{
    m_SituationProperties = new SituationPropertiesWidget(this);
    m_ChoiceProperties = new ChoicePropertiesWidget(this);

    m_SituationProperties->hide();
    m_ChoiceProperties->hide();

    setMinimumSize(300, 100);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{

}

void ItemPropertiesWidget::showPropertiesOf(Situation *situation)
{
    m_ChoiceProperties->hide();
    m_SituationProperties->showPropertiesOf(situation);
    m_SituationProperties->show();
}

void ItemPropertiesWidget::showPropertiesOf(Choice *choice)
{
    m_SituationProperties->hide();
    m_ChoiceProperties->showPropertiesOf(choice);
    m_ChoiceProperties->show();
}
