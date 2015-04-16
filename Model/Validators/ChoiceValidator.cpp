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

ValidationResult ChoiceValidator::validate(Choice *choice) const
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

    auto idError = validateId(choice, choice->id());
    if (idError != "")
    {
        result.addError(IdFieldName, idError);
    }

    return result;
}

QString ChoiceValidator::validateId(ContentModelBase *model, const QString &id) const
{
    QString error = "";
    Choice *choice = static_cast<Choice *>(model);

    if (id == "")
    {
        error = tr("Id is required");
    }
    else
    {
        auto choiceWithSameId = m_StoryManager->findChoiceById(id);

        if (choiceWithSameId != nullptr && choiceWithSameId != choice)
        {
            error = tr("Id is already used");
        }
    }

    return error;
}
