#ifndef CONTENTMODELBASE_H
#define CONTENTMODELBASE_H

#include <QObject>

class ContentModelBase : public QObject
{
    Q_OBJECT

    QString m_Id;
    QString m_Content;

public:
    explicit ContentModelBase(QObject *parent = 0);
    ContentModelBase(const QString &id, const QString &content, QObject *parent = 0);

    QString id() const;
    QString content() const;

    virtual ~ContentModelBase();

signals:
    void idHasChanged(const QString& newId);
    void idHasChanged(const QString& oldId, const QString& newId);
    void contentHasChanged(const QString& newContent);

public slots:
    void setId(const QString& id);
    void setContent(const QString& content);
};

#endif // CONTENTMODELBASE_H
