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
    m_ChoiceValidator = m_StoryManager->getChoiceValidator();

    m_ErrorPalette.setColor(QPalette::Text, Qt::red);
    m_ErrorPalette.setColor(QPalette::WindowText, Qt::red);

    m_IdErrors = new QLabel(this);
    m_IdErrors->setPalette(m_ErrorPalette);
    m_IdErrors->hide();
    m_SituationsErrors = new QLabel(this);
    m_SituationsErrors->setPalette(m_ErrorPalette);
    m_SituationsErrors->hide();

    m_FromComboBox = new QComboBox(this);
    m_ToComboBox = new QComboBox(this);

    m_IdEdit = new QLineEdit(this);
    m_ContentEdit = new QTextEdit(this);

    m_CreateButton = new QPushButton(tr("Create"), this);
    m_CancelButton = new QPushButton(tr("Cancel"), this);

    setupLayout();

    populateComboBoxes();

    connect(m_IdEdit, SIGNAL(textChanged(QString)), this, SLOT(idEditTextChanged()));
    connect(m_FromComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fromComboBoxSelectionChanged()));
    connect(m_ToComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(toComboBoxSelectionChanged()));
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

    QVBoxLayout *layout = new QVBoxLayout();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_CreateButton);
    buttonsLayout->addWidget(m_CancelButton);

    QGridLayout *formLayout = new QGridLayout();
    formLayout->addWidget(fromLabel, 0, 0);
    formLayout->addWidget(m_FromComboBox, 0, 1);
    formLayout->addWidget(toLabel, 1, 0);
    formLayout->addWidget(m_ToComboBox, 1, 1);
    formLayout->addWidget(m_IdErrors, 2, 0, 1, 2);
    formLayout->addWidget(idLabel, 3, 0);
    formLayout->addWidget(m_IdEdit, 3, 1);
    formLayout->addWidget(contentLabel, 4, 0, 1, 1, Qt::AlignTop);
    formLayout->addWidget(m_ContentEdit, 4, 1);

    layout->addWidget(m_SituationsErrors);
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

Situation *CreateChoiceDialog::getSelectedSituation(QComboBox *comboBox) const
{
    Situation *result = nullptr;

    if (comboBox->currentIndex() > 0) // Not "None" option is selected.
    {
        QString selectedId = comboBox->currentText();
        result = m_StoryManager->findSituationById(selectedId);
    }

    return result;
}

Choice *CreateChoiceDialog::createChoice() const
{
    QString id = m_IdEdit->text();
    QString content = m_ContentEdit->toPlainText();
    Situation *from = getSelectedSituation(m_FromComboBox);
    Situation *to = getSelectedSituation(m_ToComboBox);

    Choice *choice = new Choice(id, content);
    choice->setFrom(from);
    choice->setTo(to);

    return choice;
}

bool CreateChoiceDialog::validateForm()
{
    bool isIdValid = validateId();
    bool isSituationsValid = validateSituations();

    return isIdValid && isSituationsValid;
}

bool CreateChoiceDialog::validateId()
{
    QString id = m_IdEdit->text();

    auto result = m_ChoiceValidator->validateId(nullptr, id);

    if (result.isCorrect())
    {
        hideIdValidationErrors();
    }
    else
    {
        showIdValidationErrors(result.errors().first());
    }

    return result.isCorrect();
}

bool CreateChoiceDialog::validateSituations()
{
    Situation *from = getSelectedSituation(m_FromComboBox);
    Situation *to = getSelectedSituation(m_ToComboBox);

    auto result = m_ChoiceValidator->validateSelectedSituations(from, to);

    if (result.isCorrect())
    {
        hideSituationsValidationErrors();
    }
    else
    {
        showSituationsValidationErrors(result.errors());
    }

    return result.isCorrect();
}

void CreateChoiceDialog::showSituationsValidationErrors(QList<QString> errors)
{
    QString joinedErrors;
    for (auto error : errors)
    {
        joinedErrors.append(error + "\n");
    }

    joinedErrors = joinedErrors.trimmed();

    m_SituationsErrors->setText(joinedErrors);

    m_SituationsErrors->show();
}

void CreateChoiceDialog::hideSituationsValidationErrors()
{
    m_SituationsErrors->hide();
}

void CreateChoiceDialog::showIdValidationErrors(QString error)
{
    m_IdErrors->setText(error);
    m_IdErrors->show();

    m_IdEdit->setPalette(m_ErrorPalette);
}

void CreateChoiceDialog::hideIdValidationErrors()
{
    m_IdErrors->hide();
    m_IdEdit->setPalette(m_NormalPalette);
}

void CreateChoiceDialog::idEditTextChanged()
{
    validateId();
}

void CreateChoiceDialog::fromComboBoxSelectionChanged()
{
    validateSituations();
}

void CreateChoiceDialog::toComboBoxSelectionChanged()
{
    validateSituations();
}

void CreateChoiceDialog::createButtonClicked()
{
    bool isFormValid = validateForm();

    if (isFormValid)
    {
        auto choice = createChoice();
        m_StoryManager->addChoice(choice);

        this->close();
    }
}

void CreateChoiceDialog::cancelButtonClicked()
{
    this->close();
}
