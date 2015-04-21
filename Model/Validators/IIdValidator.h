#ifndef IIDVALIDATOR_H
#define IIDVALIDATOR_H

#include "Model/ContentModelBase.h"
#include <QString>
#include "ValidationResult.h"

class IIdValidator
{
public:
    virtual ~IIdValidator() {}

    virtual ValidationResult validateId(ContentModelBase *item, const QString &id) const = 0;
};

#endif // IIDVALIDATOR_H
