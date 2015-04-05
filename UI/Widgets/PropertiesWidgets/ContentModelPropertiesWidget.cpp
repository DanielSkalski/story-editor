#include "ContentModelPropertiesWidget.h"

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>

ContentModelPropertiesWidget::ContentModelPropertiesWidget(QWidget *parent) : QWidget(parent)
{
    m_IdEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    connect(m_ContentEdit, SIGNAL(textChanged()), this, SLOT(contentEditTextChanged()));
}

ContentModelPropertiesWidget::~ContentModelPropertiesWidget()
{

}

void ContentModelPropertiesWidget::connectIdAndContentProperties(ContentModelBase *entity)
{
    m_IdEdit->setText(entity->id());
    m_ContentEdit->setText(entity->content());

    connect(m_IdEdit, SIGNAL(textChanged(QString)), entity, SLOT(setId(QString)));
    connect(this, SIGNAL(contentEditTextChanged(QString)), entity, SLOT(setContent(QString)));
}

void ContentModelPropertiesWidget::disconnectIdAndContentProperties(ContentModelBase *entity)
{
    m_IdEdit->disconnect(entity);
    this->disconnect(entity);
}

void ContentModelPropertiesWidget::addIdEditToLayout(QGridLayout *layout, int row)
{
    QLabel *label = new QLabel(tr("Id"), this);

    layout->addWidget(label, row, 0);
    layout->addWidget(m_IdEdit, row, 1);
}

void ContentModelPropertiesWidget::addContentEditToLayout(QGridLayout *layout, int row)
{
    QLabel *label = new QLabel(tr("Content"), this);

    layout->addWidget(label, row, 0, 1, 2);
    layout->addWidget(m_ContentEdit, row + 1, 0, 1, 2);
}

void ContentModelPropertiesWidget::contentEditTextChanged()
{
    emit contentEditTextChanged(m_ContentEdit->toPlainText());
}
