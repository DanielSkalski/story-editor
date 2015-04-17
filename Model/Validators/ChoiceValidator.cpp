#include "ChoiceValidator.h"

#include "Model/Choice.h"
#include "Model/StoryManager.h"
#include "ValidationResult.h"


ChoiceValidator::ChoiceValidator(StoryManager *storyManager, QObject *parent)
    : IdValidatorBase(parent), m_StoryManager(storyManager)
{
}

QList<QString> ChoiceValidator::validateSelectedSituations(Situation *from, Situation *to) const
{
    QList<QString> result;

    if (from == nullptr)
    {
        result.append(tr("Situation 'from' must be selected"));
    }

    if (to == nullptr)
    {
        result.append(tr("Situation 'to' must be selected"));
    }
    else if (to == from)
    {
        result.append(tr("Situation 'to' must be different than 'from'"));
    }

    return result;
}

ContentModelBase *ChoiceValidator::findItemWithId(const QString &id) const
{
    return m_StoryManager->findChoiceById(id);
}
