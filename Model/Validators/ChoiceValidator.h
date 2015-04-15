#ifndef CHOICEVALIDATOR_H
#define CHOICEVALIDATOR_H

#include <QString>
#include <QObject>

class StoryManager;
class Choice;
class ValidationResult;

class ChoiceValidator : public QObject
{
    Q_OBJECT

    StoryManager *m_StoryManager;

public:
    static const QString FromFieldName;
    static const QString ToFieldName;
    static const QString IdFieldName;

    explicit ChoiceValidator(StoryManager *storyManager, QObject *parent = 0);
    ~ChoiceValidator();

    ValidationResult Validate(Choice *choice) const;

private:
    QList<QString> ValidateId(Choice *choice, const QString &newId) const;

};

#endif // CHOICEVALIDATOR_H
