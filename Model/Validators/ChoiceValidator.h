#ifndef CHOICEVALIDATOR_H
#define CHOICEVALIDATOR_H

#include <QString>
#include <QObject>
#include "IIdValidator.h"

class StoryManager;
class Choice;
class Situation;
class ValidationResult;

class ChoiceValidator : public QObject, public IIdValidator
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    explicit ChoiceValidator(StoryManager *storyManager, QObject *parent = 0);

    QList<QString> validateSelectedSituations(Situation *from, Situation *to) const;
    QString validateId(ContentModelBase *model, const QString &id) const Q_DECL_OVERRIDE;

};

#endif // CHOICEVALIDATOR_H
