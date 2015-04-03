#ifndef SITUATIONLISTMODEL_H
#define SITUATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QModelIndex>

class Situation;

class SituationListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<Situation *> m_Items;

public:
    explicit SituationListModel(QList<Situation *> items, QObject *parent = 0);
    ~SituationListModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    Situation *getItem(const QModelIndex &index) const;

    QModelIndex getIndex(Situation *situation) const;

signals:

public slots:
};

#endif // SITUATIONLISTMODEL_H
