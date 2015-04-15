#include "ChoiceValidator.h"

#include "Model/Choice.h"
#include "Model/StoryManager.h"
#include "ValidationResult.h"


const QString ChoiceValidator::FromFieldName = "from";
const QString ChoiceValidator::ToFieldName = "to";
const QString ChoiceValidator::IdFieldName = "id";

ChoiceValidator::ChoiceValidator(StoryManager *storyManager, QObject *parent)
    : QObject(parent), m_StoryManager(storyManager)
{
}

ChoiceValidator::~ChoiceValidator()
{
}

ValidationResult ChoiceValidator::Validate(Choice *choice) const
{
    ValidationResult result;

    if (choice->from() == nullptr)
    {
        result.addError(FromFieldName, tr("Situation 'from' must be selected"));
    }

    if (choice->to() == nullptr)
    {
        result.addError(ToFieldName, tr("Situation 'to' must be selected"));
    }
    else if (choice->to() == choice->from())
    {
        result.addError(ToFieldName, tr("Situation 'to' must be different than 'from'"));
    }

    auto idErrors = ValidateId(choice, choice->id());
    if (idErrors.size() > 0)
    {
        result.addErrors(IdFieldName, idErrors);
    }

    return result;
}

QList<QString> ChoiceValidator::ValidateId(Choice *choice, const QString &id) const
{
    QList<QString> errors;

    if (id == "")
    {
        errors.append(tr("Id is required"));
    }
    else
    {
        auto choiceWithSameId = m_StoryManager->findChoiceById(id);

        if (choiceWithSameId != nullptr && choiceWithSameId != choice)
        {
            errors.append(tr("Id is already used"));
        }
    }

    return errors;
}
