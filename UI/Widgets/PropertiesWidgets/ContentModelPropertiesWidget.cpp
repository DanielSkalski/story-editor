#include "ContentModelPropertiesWidget.h"

#include "Model/ContentModelBase.h"
#include "Model/Validators/IIdValidator.h"

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>

ContentModelPropertiesWidget::ContentModelPropertiesWidget(QWidget *parent) : QWidget(parent)
{
    m_IdEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);
    m_IdValidationError = new QLabel(this);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);
    m_IdValidationError->setPalette(palette);

    m_ErrorPalette.setColor(QPalette::Text, Qt::red);

    connect(m_IdEdit, SIGNAL(textChanged(QString)), this, SLOT(validateId()));
    connect(m_ContentEdit, SIGNAL(textChanged()), this, SLOT(contentEditTextChanged()));
}

ContentModelPropertiesWidget::~ContentModelPropertiesWidget()
{

}

void ContentModelPropertiesWidget::connectIdAndContentProperties(ContentModelBase *entity)
{
    m_Item = entity;

    m_IdEdit->setText(entity->id());
    m_ContentEdit->setText(entity->content());

    connect(this, SIGNAL(contentEditTextChanged(QString)), entity, SLOT(setContent(QString)));

    // if previous item had edited id to the same value as current item id
    // the event textChanged of m_IdEdit will not be triggered,
    // so we must hide id validation errors manualy.
    hideIdValidationError();
}

void ContentModelPropertiesWidget::disconnectIdAndContentProperties(ContentModelBase *entity)
{
    m_Item = nullptr;

    m_IdEdit->disconnect(entity);
    this->disconnect(entity);
}

void ContentModelPropertiesWidget::addIdEditToLayout(QGridLayout *layout, int& row)
{
    QLabel *label = new QLabel(tr("Id"), this);

    layout->addWidget(m_IdValidationError, row, 0, 1, 2);
    layout->addWidget(label, ++row, 0);
    layout->addWidget(m_IdEdit, row, 1);
}

void ContentModelPropertiesWidget::addContentEditToLayout(QGridLayout *layout, int& row)
{
    QLabel *label = new QLabel(tr("Content"), this);

    layout->addWidget(label, row, 0, 1, 2);
    layout->addWidget(m_ContentEdit, ++row, 0, 1, 2);
}

void ContentModelPropertiesWidget::hideIdValidationError()
{
    m_IdValidationError->hide();
    m_IdEdit->setPalette(m_NormalPalette);
}

void ContentModelPropertiesWidget::showIdValidationError(const QString &error)
{
    m_IdValidationError->setText(error);
    m_IdValidationError->show();

    m_IdEdit->setPalette(m_ErrorPalette);
}

void ContentModelPropertiesWidget::applyChanges()
{
    if (validateId())
    {
        QString id = m_IdEdit->text();
        m_Item->setId(id);
    }
}

void ContentModelPropertiesWidget::contentEditTextChanged()
{
    emit contentEditTextChanged(m_ContentEdit->toPlainText());
}

bool ContentModelPropertiesWidget::validateId()
{
    QString id = m_IdEdit->text();
    IIdValidator *validator = createIdValidator();

    QString error = validator->validateId(m_Item, id);

    bool isValid = (error == "");

    if (isValid)
    {
       hideIdValidationError();
    }
    else
    {
        showIdValidationError(error);
    }

    return isValid;
}
