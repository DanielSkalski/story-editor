#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QVector>
#include <QObject>

class Choice;
class Situation;


class StoryManager : public QObject
{
    Q_OBJECT

    QVector<Situation *> m_Situations;
    QVector<Choice *> m_Choices;

    int m_NextAvailableSituationNumber;

public:
    StoryManager();
    ~StoryManager();

    QVector<Situation *> situations() const;
    QVector<Choice *> choices() const;

    Situation *findSituationById(QString id) const;

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
