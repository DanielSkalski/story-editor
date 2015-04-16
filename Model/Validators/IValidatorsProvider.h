#ifndef IVALIDATORSPROVIDER_H
#define IVALIDATORSPROVIDER_H

#include "ChoiceValidator.h"
#include "SituationValidator.h"

class IValidatorsProvider
{
public:
    virtual ~IValidatorsProvider() {}

    virtual ChoiceValidator *getChoiceValidator() const = 0;
    virtual SituationValidator *getSituationValidator() const = 0;
};

#endif // IVALIDATORSPROVIDER_H
