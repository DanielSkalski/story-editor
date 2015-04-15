#include "StoryManager.h"

#include "Situation.h"
#include "Choice.h"
#include "Validators/ChoiceValidator.h"
#include "Validators/ValidationResult.h"

#include <QString>
#include <QVector>
#include <QStringList>

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

    m_ChoiceValidator = new ChoiceValidator(this);
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

    delete m_ChoiceValidator;
}

QList<Situation *> StoryManager::situations() const
{
    return m_Situations;
}

QList<Choice *> StoryManager::choices() const
{
    return m_Choices;
}

Situation *StoryManager::findSituationById(const QString &id) const
{
    Situation *result = nullptr;
    for (Situation *sit : m_Situations)
    {
        if (sit->id() == id)
        {
            result = sit;
            break;
        }
    }

    return result;
}

Choice *StoryManager::findChoiceById(const QString &id) const
{
    Choice *result = nullptr;
    for(Choice *choice : m_Choices)
    {
        if (choice->id() == id)
        {
            result = choice;
            break;
        }
    }

    return result;
}

ValidationResult StoryManager::ValidateChoice(Choice *choice) const
{
    return m_ChoiceValidator->Validate(choice);
}

QString StoryManager::findNextAvailableSituationId() const
{
    QString result;
    QString defaultSituationId = "Situation";
    QList<Situation *> elementsWithIdThatBeginsWithDefaultValue;

    for (Situation *situation : m_Situations)
    {
        if (situation->id().startsWith(defaultSituationId))
        {
            elementsWithIdThatBeginsWithDefaultValue.append(situation);
        }
    }

    if (elementsWithIdThatBeginsWithDefaultValue.count() > 0)
    {
        int highestIdNumber = 0;

        for (Situation *situation : elementsWithIdThatBeginsWithDefaultValue)
        {
            QStringList idParts = situation->id().split(" ");
            if (idParts.count() == 2)
            {
                bool isNumber = false;
                int idNum = idParts[1].toInt(&isNumber);
                if (isNumber)
                {
                   if (idNum > highestIdNumber)
                   {
                       highestIdNumber = idNum;
                   }
                }
            }
        }

        int nextIdNumber = highestIdNumber + 1;

        result = defaultSituationId + " " + QString::number(nextIdNumber);
    }
    else
    {
        result = defaultSituationId;
    }

    return result;
}

void StoryManager::addSituation(Situation *situation)
{
    m_Situations << situation;

    emit addedSituation(situation);
}

void StoryManager::addChoice(Choice *choice)
{
    m_Choices << choice;

    emit addedChoice(choice);
}

void StoryManager::createEmptySituation()
{
    QString situationId = findNextAvailableSituationId();

    Situation *emptySituation = new Situation(situationId, "", "");
    emptySituation->position = QPointF(0, 0);

    m_Situations << emptySituation;

    emit addedSituation(emptySituation);
}
