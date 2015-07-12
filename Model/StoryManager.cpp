#include "StoryManager.h"

#include "Situation.h"
#include "Choice.h"
#include "Story.h"
#include "Validators/ChoiceValidator.h"
#include "Validators/SituationValidator.h"
#include "Validators/ValidationResult.h"

#include <QString>
#include <QVector>
#include <QStringList>

StoryManager::StoryManager(QObject *parent)
    : QObject(parent), m_Story(nullptr)
{
    m_ChoiceValidator = new ChoiceValidator(this);
    m_SituationValidator = new SituationValidator(this);
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
    delete m_SituationValidator;
}

QList<Situation *> StoryManager::situations() const
{
    return m_Situations;
}

QList<Choice *> StoryManager::choices() const
{
    return m_Choices;
}

void StoryManager::load(Story *story)
{
    unload();

    m_Story = story;
    for (auto sit : story->situations())
    {
        m_Situations.append(sit);
        for (auto choice : sit->choices())
        {
            m_Choices.append(choice);
        }
    }

    emit loadedStory();
}

void StoryManager::unload()
{
    for (auto situation : m_Situations)
    {
        delete situation;
    }

    for (auto choice : m_Choices)
    {
        delete choice;
    }

    m_Situations.clear();
    m_Choices.clear();

    if (m_Story != nullptr)
        delete m_Story;
}

Story *StoryManager::story() const
{
    return m_Story;
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
    for (Choice *choice : m_Choices)
    {
        if (choice->id() == id)
        {
            result = choice;
            break;
        }
    }

    return result;
}

ChoiceValidator *StoryManager::getChoiceValidator() const
{
    return m_ChoiceValidator;
}

SituationValidator *StoryManager::getSituationValidator() const
{
    return m_SituationValidator;
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
