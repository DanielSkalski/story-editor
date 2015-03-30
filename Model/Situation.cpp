#include "Situation.h"

Situation::Situation()
{
}

Situation::Situation(QString id, QString title, QString content)
    : m_Id(id), m_Title(title), m_Content(content)
{
}

QString Situation::id() const
{
    return m_Id;
}

QString Situation::title() const
{
    return m_Title;
}

QString Situation::content() const
{
    return m_Content;
}

QList<Choice *> Situation::choices() const
{
    return m_Choices;
}

void Situation::setId(const QString &id)
{
    m_Id = id;
}

void Situation::setTitle(const QString &title)
{
    m_Title = title;
}

void Situation::setContent(const QString &content)
{
    m_Content = content;
}

void Situation::addChoice(Choice * const &choice)
{
    m_Choices.append(choice);
}

void Situation::removeChoice(Choice * const &choice)
{
    m_Choices.removeAll(choice);
}
