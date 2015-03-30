#ifndef SITUATION_H
#define SITUATION_H

#include <QString>
#include <QList>
#include <QPointF>

class Choice;

class Situation
{
    QString m_Id;
    QString m_Title;
    QString m_Content;

    QList<Choice *> m_Choices;

public:
    Situation();
    Situation(QString id, QString title, QString content);

    QPointF position;

    QString id() const;
    QString title() const;
    QString content() const;
    QList<Choice *> choices() const;

    void setId(const QString& id);
    void setTitle(const QString& title);
    void setContent(const QString& content);

    void addChoice(Choice * const &choice);
    void removeChoice(Choice * const &choice);
};

#endif // SITUATION_H
