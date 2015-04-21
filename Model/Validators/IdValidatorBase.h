#ifndef IDVALIDATORBASE_H
#define IDVALIDATORBASE_H

#include <QObject>
#include "IIdValidator.h"
#include "ValidationResult.h"

class IdValidatorBase : public QObject, public IIdValidator
{
    Q_OBJECT

public:
    explicit IdValidatorBase(QObject *parent = 0);
    virtual ~IdValidatorBase();

    ValidationResult validateId(ContentModelBase *, const QString &id) const Q_DECL_OVERRIDE;

protected:
    virtual ContentModelBase *findItemWithId(const QString &id) const = 0;
};

#endif // IDVALIDATORBASE_H
