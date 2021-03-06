#include "ChoicePropertiesWidget.h"

#include "Model/Choice.h"
#include "Model/Validators/IValidatorsProvider.h"

#include <QGridLayout>

ChoicePropertiesWidget::ChoicePropertiesWidget(IValidatorsProvider *validatorsProvider, QWidget *parent)
    : ContentModelPropertiesWidget(parent), m_CurrentItem(nullptr), m_ValidatorsProvider(validatorsProvider)
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

IIdValidator *ChoicePropertiesWidget::createIdValidator()
{
    return m_ValidatorsProvider->getChoiceValidator();
}

void ChoicePropertiesWidget::setupLayout()
{
    int row = 0;

    QGridLayout *layout = new QGridLayout;
    addIdEditToLayout(layout, row);
    addContentEditToLayout(layout, ++row);

    setLayout(layout);
}

void ChoicePropertiesWidget::disconnectCurrentItem()
{
    if (m_CurrentItem != nullptr)
    {
        disconnectIdAndContentProperties(m_CurrentItem);
    }
}
