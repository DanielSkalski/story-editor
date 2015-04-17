#ifndef SITUATIONPROPERTIESWIDGET_H
#define SITUATIONPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class QLineEdit;
class Situation;
class IValidatorsProvider;

class SituationPropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    QLineEdit *m_TitleEdit;

    Situation *m_CurrentItem;

    IValidatorsProvider *m_ValidatorsProvider;

public:
    explicit SituationPropertiesWidget(IValidatorsProvider *validatorsProvider, QWidget *parent = 0);
    ~SituationPropertiesWidget();

    void showPropertiesOf(Situation *situation);

protected:
    IIdValidator *createIdValidator() Q_DECL_OVERRIDE;

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // SITUATIONPROPERTIESWIDGET_H
