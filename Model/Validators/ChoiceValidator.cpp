#include "ChoiceValidator.h"

#include "Model/Choice.h"
#include "Model/StoryManager.h"
#include "ValidationResult.h"


ChoiceValidator::ChoiceValidator(StoryManager *storyManager, QObject *parent)
    : QObject(parent), m_StoryManager(storyManager)
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
