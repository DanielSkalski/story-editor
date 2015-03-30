#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QVector>

class Choice;
class Situation;


class StoryManager
{
    QVector<Situation *> m_Situations;
    QVector<Choice *> m_Choices;

public:
    StoryManager();
    ~StoryManager();

    QVector<Situation *> situations() const;
    QVector<Choice *> choices() const;
};

#endif // STORYMANAGER_H
