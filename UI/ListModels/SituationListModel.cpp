#include "SituationListModel.h"

#include "Model/Situation.h"

SituationListModel::SituationListModel(QList<Situation *> items, QObject *parent)
    : QAbstractListModel(parent), m_Items(items)
{

}

SituationListModel::~SituationListModel()
{

}

QVariant SituationListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return m_Items.at(index.row())->id();
}

int SituationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_Items.count();
}

Situation *SituationListModel::getItem(const QModelIndex &index) const
{
    return m_Items.at(index.row());
}

QModelIndex SituationListModel::getIndex(Situation *situation) const
{
    int row = m_Items.indexOf(situation);

    return createIndex(row, 0, situation);
}
