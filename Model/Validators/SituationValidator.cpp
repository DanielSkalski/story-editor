#include "SituationValidator.h"

#include "Model/Situation.h"
#include "Model/StoryManager.h"

SituationValidator::SituationValidator(StoryManager *storyManager, QObject *parent)
    : IdValidatorBase(parent), m_StoryManager(storyManager)
{
}

ContentModelBase *SituationValidator::findItemWithId(const QString &id) const
{
    return m_StoryManager->findSituationById(id);
}

