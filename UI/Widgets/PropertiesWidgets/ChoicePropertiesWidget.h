#ifndef CHOICEPROPERTIESWIDGET_H
#define CHOICEPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class Choice;

class ChoicePropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    Choice *m_CurrentItem;

public:
    explicit ChoicePropertiesWidget(QWidget *parent = 0);
    ~ChoicePropertiesWidget();

    void showPropertiesOf(Choice *choice);

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // CHOICEPROPERTIESWIDGET_H
