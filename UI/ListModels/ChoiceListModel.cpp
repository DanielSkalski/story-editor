#include "ChoiceListModel.h"

#include "Model/Choice.h"

ChoiceListModel::ChoiceListModel(QList<Choice *> items, QObject *parent)
    : QAbstractListModel(parent), m_Items(items)
{
}

ChoiceListModel::~ChoiceListModel()
{
}

QVariant ChoiceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    Choice* item = m_Items.at(index.row());

    return item->id();
}

int ChoiceListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_Items.count();
}

Choice *ChoiceListModel::getItem(const QModelIndex &index) const
{
    return m_Items.at(index.row());
}
