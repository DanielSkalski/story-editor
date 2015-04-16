#include "SituationValidator.h"

#include "Model/Situation.h"
#include "Model/StoryManager.h"

SituationValidator::SituationValidator(StoryManager *storyManager, QObject *parent)
    : QObject(parent), m_StoryManager(storyManager)
{
}

QString SituationValidator::validateId(ContentModelBase *model, const QString &id) const
{
    QString error = "";
    Situation *situation = static_cast<Situation *>(model);

    if (id == "")
    {
        error = tr("Id is required");
    }
    else
    {
        auto situationWithSameId = m_StoryManager->findSituationById(id);

        if (situationWithSameId != nullptr && situationWithSameId != situation)
        {
            error = tr("Id is already used");
        }
    }

    return error;
}

