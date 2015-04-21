#include "IdValidatorBase.h"

IdValidatorBase::IdValidatorBase(QObject *parent)
    : QObject(parent)
{
}

IdValidatorBase::~IdValidatorBase()
{
}

ValidationResult IdValidatorBase::validateId(ContentModelBase *model, const QString &id) const
{
    ValidationResult result;

    if (id == "")
    {
        result.addError(tr("Id is required"));
    }
    else
    {
        auto modelWithSameId = this->findItemWithId(id);

        if (modelWithSameId != nullptr && modelWithSameId != model)
        {
            result.addError(tr("Id is already used"));
        }
    }

    return result;
}

