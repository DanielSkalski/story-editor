#ifndef VALIDATIONRESULT_H
#define VALIDATIONRESULT_H

#include <QString>
#include <QMap>
#include <QList>

class ValidationResult
{
    QMap<QString, QList<QString> > m_Errors;
    QList<QString> m_AllErrors;

public:
    ValidationResult();
    ~ValidationResult();

    bool isCorrect() const;

    void addError(const QString& fieldName, const QString& errorMessage);
    void addErrors(const QString& fieldName, const QList<QString>& errors);

    QList<QString> fieldsWithErrors() const;
    QList<QString> errorsForField(const QString &fieldName) const;
    QList<QString> allErrors() const;
};

#endif // VALIDATIONRESULT_H
