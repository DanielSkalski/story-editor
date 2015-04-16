#ifndef CONTENTMODELPROPERTIESWIDGET_H
#define CONTENTMODELPROPERTIESWIDGET_H

#include <QWidget>

class IIdValidator;
class ContentModelBase;
class QLineEdit;
class QTextEdit;
class QGridLayout;
class QLabel;


class ContentModelPropertiesWidget : public QWidget
{
    Q_OBJECT

    QLabel *m_IdValidationError;

    QLineEdit *m_IdEdit;
    QTextEdit *m_ContentEdit;

    ContentModelBase *m_Item;

    QPalette m_ErrorPalette;
    QPalette m_NormalPalette;

public:
    explicit ContentModelPropertiesWidget(QWidget *parent = 0);
    virtual ~ContentModelPropertiesWidget();

protected:
    virtual IIdValidator *createIdValidator() = 0;

    void connectIdAndContentProperties(ContentModelBase *entity);
    void disconnectIdAndContentProperties(ContentModelBase *entity);

    void addIdEditToLayout(QGridLayout *layout, int &row);
    void addContentEditToLayout(QGridLayout *layout, int &row);

private:
    void hideIdValidationError();
    void showIdValidationError(const QString & error);

signals:
    void contentEditTextChanged(const QString &);

public slots:
    void applyChanges();

private slots:
    void contentEditTextChanged();
    bool validateId();
};

#endif // CONTENTMODELPROPERTIESWIDGET_H
