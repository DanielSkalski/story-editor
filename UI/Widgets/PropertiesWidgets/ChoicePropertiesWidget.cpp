#include "ChoicePropertiesWidget.h"

#include "Model/Choice.h"

#include <QGridLayout>

ChoicePropertiesWidget::ChoicePropertiesWidget(QWidget *parent)
    : ContentModelPropertiesWidget(parent), m_CurrentItem(nullptr)
{
    setupLayout();
}

ChoicePropertiesWidget::~ChoicePropertiesWidget()
{

}

void ChoicePropertiesWidget::showPropertiesOf(Choice *choice)
{
    disconnectCurrentItem();

    m_CurrentItem = choice;

    if (m_CurrentItem != nullptr)
    {
        connectIdAndContentProperties(m_CurrentItem);
    }
}

void ChoicePropertiesWidget::setupLayout()
{
    QGridLayout *layout = new QGridLayout;
    addIdEditToLayout(layout, 0);
    addContentEditToLayout(layout, 1);

    setLayout(layout);
}

void ChoicePropertiesWidget::disconnectCurrentItem()
{
    if (m_CurrentItem != nullptr)
    {
        disconnectIdAndContentProperties(m_CurrentItem);
    }
}
