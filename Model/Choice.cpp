#include "Choice.h"

Choice::Choice()
{

}

Choice::Choice(QString id, QString content)
    : m_Id(id), m_Content(content)
{

}

QString Choice::id() const
{
    return m_Id;
}

QString Choice::content() const
{
    return m_Content;
}

Situation * Choice::from() const
{
    return m_From;
}

Situation * Choice::to() const
{
    return m_To;
}

void Choice::setId(const QString &id)
{
    m_Id = id;
}

void Choice::setContent(const QString &content)
{
    m_Content = content;
}

void Choice::setFrom(Situation * const from)
{
    m_From = from;
}

void Choice::setTo(Situation * const to)
{
    m_To = to;
}
