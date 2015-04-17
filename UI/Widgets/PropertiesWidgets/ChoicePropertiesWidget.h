#ifndef CHOICEPROPERTIESWIDGET_H
#define CHOICEPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class Choice;
class StoryManager;
class IValidatorsProvider;

class ChoicePropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    Choice *m_CurrentItem;
    IValidatorsProvider *m_ValidatorsProvider;

public:
    explicit ChoicePropertiesWidget(IValidatorsProvider *validatorsProvider, QWidget *parent = 0);
    ~ChoicePropertiesWidget();

    void showPropertiesOf(Choice *choice);

    IIdValidator *createIdValidator() Q_DECL_OVERRIDE;

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // CHOICEPROPERTIESWIDGET_H
