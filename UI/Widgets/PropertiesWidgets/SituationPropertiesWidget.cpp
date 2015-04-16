#include "SituationPropertiesWidget.h"

#include "Model/Situation.h"
#include "Model/Validators/IValidatorsProvider.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

SituationPropertiesWidget::SituationPropertiesWidget(IValidatorsProvider *validatorsProvider, QWidget *parent)
     : ContentModelPropertiesWidget(parent), m_CurrentItem(nullptr), m_ValidatorsProvider(validatorsProvider)
{
    m_TitleEdit = new QLineEdit(this);

    setupLayout();
}

SituationPropertiesWidget::~SituationPropertiesWidget()
{

}

void SituationPropertiesWidget::showPropertiesOf(Situation *situation)
{
    disconnectCurrentItem();

    m_CurrentItem = situation;

    if (situation != nullptr)
    {
        connectIdAndContentProperties(situation);

        m_TitleEdit->setText(situation->title());
        m_TitleEdit->setReadOnly(false);

        connect(m_TitleEdit, SIGNAL(textChanged(QString)), situation, SLOT(setTitle(QString)));
    }
}

IIdValidator *SituationPropertiesWidget::createIdValidator()
{
    return m_ValidatorsProvider->getSituationValidator();
}

void SituationPropertiesWidget::setupLayout()
{
    QLabel *titleLabel = new QLabel(tr("Title"), this);

    int row = 0;

    QGridLayout *layout = new QGridLayout();
    addIdEditToLayout(layout, row);
    layout->addWidget(titleLabel, ++row, 0);
    layout->addWidget(m_TitleEdit, row, 1);
    addContentEditToLayout(layout, ++row);

    setLayout(layout);
}

void SituationPropertiesWidget::disconnectCurrentItem()
{
    if (m_CurrentItem != nullptr)
    {
        m_TitleEdit->disconnect(m_CurrentItem);
        disconnectIdAndContentProperties(m_CurrentItem);
    }
}
