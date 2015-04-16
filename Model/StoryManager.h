#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QObject>

class Choice;
class Situation;
class ChoiceValidator;
class SituationValidator;
class ValidationResult;

class StoryManager : public QObject
{
    Q_OBJECT

    QList<Situation *> m_Situations;
    QList<Choice *> m_Choices;

    int m_NextAvailableSituationNumber;

    ChoiceValidator *m_ChoiceValidator;
    SituationValidator *m_SituationValidator;

public:
    StoryManager();
    ~StoryManager();

    QList<Situation *> situations() const;
    QList<Choice *> choices() const;

    Situation *findSituationById(const QString &id) const;
    Choice *findChoiceById(const QString& id) const;

    ValidationResult ValidateChoice(Choice *choice) const;

    ChoiceValidator *getChoiceValidator() const;
    SituationValidator *getSituationValidator() const;

private:
    QString findNextAvailableSituationId() const;

signals:
    void addedSituation(Situation *situation);
    void addedChoice(Choice *choice);

public slots:
    void addSituation(Situation *situation);
    void addChoice(Choice *choice);

    void createEmptySituation();
};

#endif // STORYMANAGER_H
