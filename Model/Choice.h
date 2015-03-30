#ifndef CHOICE_H
#define CHOICE_H

#include <QString>

class Situation;

class Choice
{
    QString m_Id;
    QString m_Content;

    Situation* m_From;
    Situation* m_To;

public:
    Choice();
    Choice(QString id, QString content);

    QString id() const;
    QString content() const;

    Situation * from() const;
    Situation * to() const;

    void setId(const QString& id);
    void setContent(const QString& content);

    void setFrom(Situation *const from);
    void setTo(Situation *const to);
};

#endif // CHOICE_H
