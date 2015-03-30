#ifndef SITUATION_H
#define SITUATION_H

#include <QString>
#include <QList>
#include <QPointF>
#include <QObject>

class Choice;

class Situation : public QObject
{
    Q_OBJECT

    QString m_Id;
    QString m_Title;
    QString m_Content;

    QList<Choice *> m_Choices;

public:
    Situation(QObject *parent = 0);
    Situation(QString id, QString title, QString content);

    QPointF position;

    QString id() const;
    QString title() const;
    QString content() const;
    QList<Choice *> choices() const;

    void addChoice(Choice * const &choice);
    void removeChoice(Choice * const &choice);

signals:
    void idHasChanged(const QString& newId);
    void idHasChanged(const QString& oldId, const QString& newId);
    void titleHasChanged(const QString& newTitle);
    void contentHasChanged(const QString& newContent);

public slots:
    void setId(const QString& id);
    void setTitle(const QString& title);
    void setContent(const QString& content);
};

#endif // SITUATION_H
