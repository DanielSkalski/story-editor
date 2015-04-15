#include "CreateChoiceDialog.h"

#include "Model/Situation.h"
#include "Model/Choice.h"
#include "Model/StoryManager.h"
#include "Model/Validators/ValidationResult.h"

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
    m_Errors = new QLabel(this);

    m_FromComboBox = new QComboBox(this);
    m_ToComboBox = new QComboBox(this);

    m_IdEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    m_CreateButton = new QPushButton(tr("Create"), this);
    m_CancelButton = new QPushButton(tr("Cancel"), this);

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

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);
    m_Errors->setPalette(palette);
    m_Errors->hide();

    QVBoxLayout *layout = new QVBoxLayout();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_CreateButton);
    buttonsLayout->addWidget(m_CancelButton);

    QGridLayout *formLayout = new QGridLayout();
    formLayout->addWidget(fromLabel, 0, 0);
    formLayout->addWidget(m_FromComboBox, 0, 1);
    formLayout->addWidget(toLabel, 1, 0);
    formLayout->addWidget(m_ToComboBox, 1, 1);
    formLayout->addWidget(idLabel, 2, 0);
    formLayout->addWidget(m_IdEdit, 2, 1);
    formLayout->addWidget(contentLabel, 3, 0, 1, 1, Qt::AlignTop);
    formLayout->addWidget(m_ContentEdit, 3, 1);

    layout->addWidget(m_Errors);
    layout->addLayout(formLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);
}

void CreateChoiceDialog::populateComboBoxes()
{
    auto situations = m_StoryManager->situations();

    QStringList situationsTexts;
    situationsTexts.append(tr("None"));

    for (Situation *sit : situations)
    {
        situationsTexts.append(sit->id());
    }

    m_FromComboBox->addItems(situationsTexts);
    m_ToComboBox->addItems(situationsTexts);
}

Situation *CreateChoiceDialog::getSelectedSituation(QComboBox *comboBox)
{
    Situation *result = nullptr;

    if (comboBox->currentIndex() > 0) // Not "None" option is selected.
    {
        QString selectedId = comboBox->currentText();
        result = m_StoryManager->findSituationById(selectedId);
    }

    return result;
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
    Situation *from = getSelectedSituation(m_FromComboBox);
    Situation *to = getSelectedSituation(m_ToComboBox);

    Choice *choice = new Choice(id, content);
    choice->setFrom(from);
    choice->setTo(to);

    ValidationResult validationResult = m_StoryManager->ValidateChoice(choice);

    if (validationResult.isCorrect())
    {
        m_StoryManager->addChoice(choice);
        this->close();
    }
    else
    {
        QString errors;
        for(auto error : validationResult.allErrors())
        {
            errors.append(error + "\n");
        }

        m_Errors->setText(errors);

        m_Errors->show();
    }
}

void CreateChoiceDialog::cancelButtonClicked()
{
    this->close();
}
