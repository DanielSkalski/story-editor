#include "IdValidatorBase.h"

IdValidatorBase::IdValidatorBase(QObject *parent)
    : QObject(parent)
{
}

IdValidatorBase::~IdValidatorBase()
{
}

QString IdValidatorBase::validateId(ContentModelBase *model, const QString &id) const
{
    QString error = "";

    if (id == "")
    {
        error = tr("Id is required");
    }
    else
    {
        auto modelWithSameId = this->findItemWithId(id);

        if (modelWithSameId != nullptr && modelWithSameId != model)
        {
            error = tr("Id is already used");
        }
    }

    return error;
}

