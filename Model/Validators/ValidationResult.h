#ifndef VALIDATIONRESULT_H
#define VALIDATIONRESULT_H

#include <QString>
#include <QList>

class ValidationResult
{
    QList<QString> m_Errors;

public:
    ValidationResult();
    ~ValidationResult();

    bool isCorrect() const;

    void addError(const QString& errorMessage);

    QList<QString> errors() const;
};

#endif // VALIDATIONRESULT_H
