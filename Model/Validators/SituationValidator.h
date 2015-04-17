#ifndef SITUATIONVALIDATOR_H
#define SITUATIONVALIDATOR_H

#include "IdValidatorBase.h"

class StoryManager;

class SituationValidator : public IdValidatorBase
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    explicit SituationValidator(StoryManager *storyManager, QObject *parent = 0);

protected:
    ContentModelBase *findItemWithId(const QString &id) const Q_DECL_OVERRIDE;
};

#endif // SITUATIONVALIDATOR_H
