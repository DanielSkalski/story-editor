#include "ValidationResult.h"

ValidationResult::ValidationResult()
{
}

ValidationResult::~ValidationResult()
{
}

bool ValidationResult::isCorrect() const
{
    return m_Errors.size() == 0;
}

void ValidationResult::addError(const QString &errorMessage)
{
    m_Errors.append(errorMessage);
}

QList<QString> ValidationResult::errors() const
{
    return m_Errors;
}

