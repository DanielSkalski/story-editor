#ifndef STORY_H
#define STORY_H

#include <QObject>

class Situation;

class Story : public QObject
{
    Q_OBJECT

    QList<Situation *> m_Situations;

public:
    explicit Story(QObject *parent = 0);
    ~Story();

    QList<Situation *> situations() const;

    void add(Situation *situation);

    static Story *createEmptyStory();
};

#endif // STORY_H
