#ifndef IIDVALIDATOR_H
#define IIDVALIDATOR_H

#include "Model/ContentModelBase.h"
#include <QString>

class IIdValidator
{
public:
    IIdValidator();
    ~IIdValidator();

    virtual QString validateId(ContentModelBase *, const QString &id) const = 0;
};

#endif // IIDVALIDATOR_H
