#include "StoryManager.h"
#include "Situation.h"
#include "Choice.h"
#include <QString>

StoryManager::StoryManager()
{
    auto sit1 = new Situation("Sit1_ID", "Situation 1", "Content of Situation 1.");
    sit1->position = QPointF(-40, -150);
    auto sit2 = new Situation("Sit2_ID", "Situation 2", "Content of Situation 2.");
    sit2->position = QPointF(-150, 20);
    auto sit3 = new Situation("Sit3_ID", "Situation 3", "Content of Situation 3.");
    sit3->position = QPointF(50, 20);

    auto choice1 = new Choice("Sit1-Sit2", "Choice 1");
    choice1->setFrom(sit1);
    choice1->setTo(sit2);
    sit1->addChoice(choice1);

    auto choice2 = new Choice("Sit1-Sit3", "Choice 2");
    choice2->setFrom(sit1);
    choice2->setTo(sit3);
    sit1->addChoice(choice2);

    auto choice3 = new Choice("Sit2-Sit3", "Choice 3");
    choice3->setFrom(sit2);
    choice3->setTo(sit3);
    sit2->addChoice(choice3);

    m_Situations.append(sit1);
    m_Situations.append(sit2);
    m_Situations.append(sit3);

    m_Choices.append(choice1);
    m_Choices.append(choice2);
    m_Choices.append(choice3);
}

StoryManager::~StoryManager()
{
    for (auto situation : m_Situations)
    {
        delete situation;
    }

    for (auto choice : m_Choices)
    {
        delete choice;
    }
}

QVector<Situation *> StoryManager::situations() const
{
    return m_Situations;
}

QVector<Choice *> StoryManager::choices() const
{
    return m_Choices;
}
