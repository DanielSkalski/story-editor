#ifndef SITUATIONVALIDATOR_H
#define SITUATIONVALIDATOR_H

#include <QObject>
#include "IIdValidator.h"

class StoryManager;

class SituationValidator : public QObject, public IIdValidator
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    explicit SituationValidator(StoryManager *storyManager, QObject *parent = 0);

    QString validateId(ContentModelBase *model, const QString &id) const Q_DECL_OVERRIDE;
};

#endif // SITUATIONVALIDATOR_H
