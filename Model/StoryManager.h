#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QObject>
#include "Model/Validators/IValidatorsProvider.h"

class Story;
class Choice;
class Situation;
class ChoiceValidator;
class SituationValidator;
class ValidationResult;

class StoryManager : public QObject, public IValidatorsProvider
{
    Q_OBJECT

    Story *m_Story;

    QList<Situation *> m_Situations;
    QList<Choice *> m_Choices;

    ChoiceValidator *m_ChoiceValidator;
    SituationValidator *m_SituationValidator;

public:
    explicit StoryManager(QObject *parent = 0);
    virtual ~StoryManager();

    Story *story() const;
    QList<Situation *> situations() const;
    QList<Choice *> choices() const;

    void load(Story* story);
    void unload();

    Situation *findSituationById(const QString &id) const;
    Choice *findChoiceById(const QString& id) const;

    ChoiceValidator *getChoiceValidator() const Q_DECL_OVERRIDE;
    SituationValidator *getSituationValidator() const Q_DECL_OVERRIDE;

private:
    QString findNextAvailableSituationId() const;

signals:
    void addedSituation(Situation *situation);
    void addedChoice(Choice *choice);
    void loadedStory();

public slots:
    void addSituation(Situation *situation);
    void addChoice(Choice *choice);

    void createEmptySituation();
};

#endif // STORYMANAGER_H
