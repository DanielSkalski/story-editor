#include "ChoiceValidator.h"

#include "Model/Choice.h"
#include "Model/StoryManager.h"
#include "ValidationResult.h"


ChoiceValidator::ChoiceValidator(StoryManager *storyManager, QObject *parent)
    : IdValidatorBase(parent), m_StoryManager(storyManager)
{
}

ValidationResult ChoiceValidator::validateSelectedSituations(Situation *from, Situation *to) const
{
    ValidationResult result;

    if (from == nullptr)
    {
        result.addError(tr("Situation 'from' must be selected"));
    }

    if (to == nullptr)
    {
        result.addError(tr("Situation 'to' must be selected"));
    }
    else if (to == from)
    {
        result.addError(tr("Situation 'to' must be different than 'from'"));
    }

    return result;
}

ContentModelBase *ChoiceValidator::findItemWithId(const QString &id) const
{
    return m_StoryManager->findChoiceById(id);
}
