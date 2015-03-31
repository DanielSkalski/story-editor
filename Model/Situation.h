#ifndef SITUATION_H
#define SITUATION_H

#include <QList>
#include <QPointF>
#include "ContentModelBase.h"

class Choice;

class Situation : public ContentModelBase
{
    Q_OBJECT

    QString m_Title;

    QList<Choice *> m_Choices;

public:
    explicit Situation(QObject *parent = 0);
    Situation(const QString &id, const QString &title, const QString &content, QObject *parent = 0);

    QPointF position;

    QString title() const;
    QList<Choice *> choices() const;

    void addChoice(Choice * const &choice);
    void removeChoice(Choice * const &choice);

signals:
    void titleHasChanged(const QString& newTitle);

public slots:
    void setTitle(const QString& title);
};

#endif // SITUATION_H
