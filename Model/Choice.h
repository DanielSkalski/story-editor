#ifndef CHOICE_H
#define CHOICE_H

#include "ContentModelBase.h"

class Situation;

class Choice : public ContentModelBase
{
    Q_OBJECT

    Situation *m_From;
    Situation *m_To;

public:
    explicit Choice(QObject *parent = 0);
    Choice(const QString &id, const QString &content, QObject *parent = 0);

    Situation *from() const;
    Situation *to() const;

public slots:
    void setFrom(Situation *const from);
    void setTo(Situation *const to);
};

#endif // CHOICE_H
