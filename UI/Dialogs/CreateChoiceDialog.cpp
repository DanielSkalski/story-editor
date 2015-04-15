#include "CreateChoiceDialog.h"

#include "Model/Situation.h"
#include "Model/Choice.h"
#include "Model/StoryManager.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QComboBox>


CreateChoiceDialog::CreateChoiceDialog(StoryManager *storyManager, QWidget *parent)
    : QDialog(parent), m_StoryManager(storyManager)
{
    setupLayout();

    populateComboBoxes();

    connect(m_IdEdit, SIGNAL(textChanged(QString)), this, SLOT(idEditTextChanged()));
    connect(m_ContentEdit, SIGNAL(textChanged()), this, SLOT(contentEditTextChanged()));
    connect(m_CreateButton, SIGNAL(clicked()), this, SLOT(createButtonClicked()));
    connect(m_CancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
}

CreateChoiceDialog::~CreateChoiceDialog()
{

}

void CreateChoiceDialog::setupLayout()
{
    QLabel *idLabel = new QLabel(tr("Id"), this);
    QLabel *contentLabel = new QLabel(tr("Content"), this);
    QLabel *fromLabel = new QLabel(tr("From"), this);
    QLabel *toLabel = new QLabel(tr("To"), this);

    m_FromComboBox = new QComboBox(this);
    m_ToComboBox = new QComboBox(this);

    m_IdEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    m_CreateButton = new QPushButton(tr("Create"), this);
    m_CancelButton = new QPushButton(tr("Cancel"), this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_CreateButton);
    buttonsLayout->addWidget(m_CancelButton);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(fromLabel, 0, 0);
    layout->addWidget(m_FromComboBox, 0, 1);
    layout->addWidget(toLabel, 1, 0);
    layout->addWidget(m_ToComboBox, 1, 1);
    layout->addWidget(idLabel, 2, 0);
    layout->addWidget(m_IdEdit, 2, 1);
    layout->addWidget(contentLabel, 3, 0, 1, 1, Qt::AlignTop);
    layout->addWidget(m_ContentEdit, 3, 1);

    layout->addLayout(buttonsLayout, 4, 0, 1, 2, Qt::AlignJustify);

    setLayout(layout);
}

void CreateChoiceDialog::populateComboBoxes()
{
    auto situations = m_StoryManager->situations().toList();

    QStringList situationsTexts;
    for (Situation *sit : situations)
    {
        situationsTexts.append(sit->id());
    }

    m_FromComboBox->addItems(situationsTexts);
    m_ToComboBox->addItems(situationsTexts);
}

void CreateChoiceDialog::idEditTextChanged()
{

}

void CreateChoiceDialog::contentEditTextChanged()
{

}

void CreateChoiceDialog::createButtonClicked()
{
    QString id = m_IdEdit->text();
    QString content = m_ContentEdit->toPlainText();
    QString fromId = m_FromComboBox->currentText();
    Situation *from = m_StoryManager->findSituationById(fromId);
    QString toId = m_ToComboBox->currentText();
    Situation *to = m_StoryManager->findSituationById(toId);

    Choice *choice = new Choice(id, content);
    choice->setFrom(from);
    choice->setTo(to);

    m_StoryManager->addChoice(choice);

    this->close();
}

void CreateChoiceDialog::cancelButtonClicked()
{
    this->close();
}
