#ifndef CHOICELISTMODEL_H
#define CHOICELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>

class Choice;

class ChoiceListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<Choice *> m_Items;

public:
    explicit ChoiceListModel(QList<Choice *> items, QObject *parent = 0);
    ~ChoiceListModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    Choice *getItem(const QModelIndex &index) const;

    QModelIndex getIndex(Choice *choice) const;

    void addItem(Choice *item);

signals:

public slots:
};

#endif // CHOICELISTMODEL_H
