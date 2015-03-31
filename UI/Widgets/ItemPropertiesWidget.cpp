#include "ItemPropertiesWidget.h"

#include "Model/Situation.h"
#include "Model/Choice.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent)
    : QWidget(parent), m_CurrentItem(nullptr)
{
    m_IdEdit = new QLineEdit(this);
    m_TitleEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    QLabel *idLabel = new QLabel("Id", this);
    QLabel *titleLabel = new QLabel("Title", this);
    QLabel *contentLabel = new QLabel("Content", this);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(idLabel, 0, 0);
    gridLayout->addWidget(m_IdEdit, 0, 1);
    gridLayout->addWidget(titleLabel, 1, 0);
    gridLayout->addWidget(m_TitleEdit, 1, 1);
    gridLayout->addWidget(contentLabel, 2, 0, 1, 2);
    gridLayout->addWidget(m_ContentEdit, 3, 0, 1, 2);

    setMinimumSize(300, 100);

    setLayout(gridLayout);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{

}

void ItemPropertiesWidget::showPropertiesOf(Situation *situation)
{
    disconnectCurrentItem();
    m_CurrentItem = situation;

    if (situation != nullptr)
    {
        connectIdAndContentProperties();

        m_TitleEdit->setText(situation->title());
        m_TitleEdit->setReadOnly(false);

        connect(m_TitleEdit, SIGNAL(textChanged(QString)), situation, SLOT(setTitle(QString)));
    }
}

void ItemPropertiesWidget::showPropertiesOf(Choice *choice)
{
    disconnectCurrentItem();
    m_CurrentItem = dynamic_cast<ContentModelBase *>(choice);

    if (choice != nullptr)
    {
        connectIdAndContentProperties();
        m_TitleEdit->clear();
        m_TitleEdit->setReadOnly(true);
    }
}

void ItemPropertiesWidget::connectIdAndContentProperties()
{
    m_IdEdit->setText(m_CurrentItem->id());
    m_ContentEdit->setText(m_CurrentItem->content());

    connect(m_IdEdit, SIGNAL(textChanged(QString)), m_CurrentItem, SLOT(setId(QString)));
    connect(m_ContentEdit, &QTextEdit::textChanged, [&]
    {
        m_CurrentItem->setContent(m_ContentEdit->toPlainText());
    });
}

void ItemPropertiesWidget::disconnectCurrentItem()
{
    if (m_CurrentItem != nullptr)
    {
        m_IdEdit->disconnect(m_CurrentItem);
        m_TitleEdit->disconnect(m_CurrentItem);
        m_ContentEdit->disconnect(m_CurrentItem);
    }
}
