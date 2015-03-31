#include "Choice.h"

Choice::Choice(QObject *parent)
    : ContentModelBase(parent)
{

}

Choice::Choice(const QString &id, const QString &content, QObject *parent)
    : ContentModelBase(id, content, parent)
{

}

Situation *Choice::from() const
{
    return m_From;
}

Situation *Choice::to() const
{
    return m_To;
}

void Choice::setFrom(Situation * const from)
{
    m_From = from;
}

void Choice::setTo(Situation * const to)
{
    m_To = to;
}
