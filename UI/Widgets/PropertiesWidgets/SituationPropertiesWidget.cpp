#include "SituationPropertiesWidget.h"

#include "Model/Situation.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

SituationPropertiesWidget::SituationPropertiesWidget(QWidget *parent)
    : ContentModelPropertiesWidget(parent), m_CurrentItem(nullptr)
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

void SituationPropertiesWidget::setupLayout()
{
    QLabel *titleLabel = new QLabel(tr("Title"), this);

    QGridLayout *layout = new QGridLayout();
    addIdEditToLayout(layout, 0);
    layout->addWidget(titleLabel, 1, 0);
    layout->addWidget(m_TitleEdit, 1, 1);
    addContentEditToLayout(layout, 2);

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
