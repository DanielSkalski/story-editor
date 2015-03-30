#include "Situation.h"

Situation::Situation(QObject *parent)
    : QObject(parent)
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
    if (m_Id != id)
    {
        QString oldId = m_Id;
        m_Id = id;

        emit idHasChanged(oldId, id);
        emit idHasChanged(id);
    }
}

void Situation::setTitle(const QString &title)
{
    if (m_Title != title)
    {
        m_Title = title;
        emit titleHasChanged(title);
    }
}

void Situation::setContent(const QString &content)
{
    if (m_Content != content)
    {
        m_Content = content;
        emit contentHasChanged(content);
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
