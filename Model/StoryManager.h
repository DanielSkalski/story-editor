#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QVector>
#include <QObject>

class Choice;
class Situation;


class StoryManager : QObject
{
    Q_OBJECT

    QVector<Situation *> m_Situations;
    QVector<Choice *> m_Choices;

public:
    StoryManager();
    ~StoryManager();

    QVector<Situation *> situations() const;
    QVector<Choice *> choices() const;

signals:
    void addedSituation(Situation *situation);
    void addedChoice(Choice *choice);

public slots:
    void addSituation(Situation *situation);
    void addChoice(Choice *choice);
};

#endif // STORYMANAGER_H
