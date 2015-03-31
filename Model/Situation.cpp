#include "Situation.h"

Situation::Situation(QObject *parent)
    : ContentModelBase(parent)
{
}

Situation::Situation(const QString &id, const QString &title, const QString &content, QObject *parent)
    : ContentModelBase(id, content, parent), m_Title(title)
{
}

QString Situation::title() const
{
    return m_Title;
}

QList<Choice *> Situation::choices() const
{
    return m_Choices;
}

void Situation::setTitle(const QString &title)
{
    if (m_Title != title)
    {
        m_Title = title;
        emit titleHasChanged(title);
    }
}

void Situation::addChoice(Choice * const &choice)
{
    m_Choices.append(choice);
}

void Situation::removeChoice(Choice * const &choice)
{
    m_Choices.removeAll(choice);
}
