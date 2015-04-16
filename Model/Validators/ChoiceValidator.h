#ifndef CHOICEVALIDATOR_H
#define CHOICEVALIDATOR_H

#include <QString>
#include <QObject>
#include "IIdValidator.h"

class StoryManager;
class Choice;
class ValidationResult;

class ChoiceValidator : public QObject, public IIdValidator
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    static const QString FromFieldName;
    static const QString ToFieldName;
    static const QString IdFieldName;

    explicit ChoiceValidator(StoryManager *storyManager, QObject *parent = 0);
    ~ChoiceValidator();

    ValidationResult validate(Choice *choice) const;
    QString validateId(ContentModelBase *model, const QString &id) const;

};

#endif // CHOICEVALIDATOR_H
