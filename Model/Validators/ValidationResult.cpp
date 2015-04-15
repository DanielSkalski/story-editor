#include "ValidationResult.h"

ValidationResult::ValidationResult()
{
}

ValidationResult::~ValidationResult()
{
}

bool ValidationResult::isCorrect() const
{
    return m_Errors.values().size() == 0;
}

void ValidationResult::addError(const QString &fieldName, const QString &errorMessage)
{
    m_Errors[fieldName].append(errorMessage);
    m_AllErrors.append(errorMessage);
}

void ValidationResult::addErrors(const QString &fieldName, const QList<QString>& errors)
{
    m_Errors[fieldName].append(errors);
    m_AllErrors.append(errors);
}

QList<QString> ValidationResult::fieldsWithErrors() const
{
    return m_Errors.keys();
}

QList<QString> ValidationResult::errorsForField(const QString& fieldName) const
{
    return m_Errors[fieldName];
}

QList<QString> ValidationResult::allErrors() const
{
    return m_AllErrors;
}

