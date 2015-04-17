#ifndef CHOICEVALIDATOR_H
#define CHOICEVALIDATOR_H

#include "IdValidatorBase.h"

class StoryManager;
class Situation;

class ChoiceValidator : public IdValidatorBase
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    explicit ChoiceValidator(StoryManager *storyManager, QObject *parent = 0);

    QList<QString> validateSelectedSituations(Situation *from, Situation *to) const;

protected:
    ContentModelBase *findItemWithId(const QString& id) const Q_DECL_OVERRIDE;
};

#endif // CHOICEVALIDATOR_H
