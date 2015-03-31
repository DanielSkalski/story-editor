#include "ContentModelBase.h"

ContentModelBase::ContentModelBase(QObject *parent)
    : QObject(parent)
{

}

ContentModelBase::ContentModelBase(const QString &id, const QString &content, QObject *parent)
    : QObject(parent), m_Id(id), m_Content(content)
{

}

ContentModelBase::~ContentModelBase()
{

}

QString ContentModelBase::id() const
{
    return m_Id;
}

QString ContentModelBase::content() const
{
    return m_Content;
}

void ContentModelBase::setId(const QString &id)
{
    if (m_Id != id)
    {
        QString oldId = m_Id;
        m_Id = id;

        emit idHasChanged(oldId, id);
        emit idHasChanged(id);
    }
}

void ContentModelBase::setContent(const QString &content)
{
    if (m_Content != content)
    {
        m_Content = content;
        emit contentHasChanged(content);
    }
}
