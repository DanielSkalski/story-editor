#ifndef CHOICEPROPERTIESWIDGET_H
#define CHOICEPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class Choice;
class StoryManager;

class ChoicePropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    Choice *m_CurrentItem;
    StoryManager *m_StoryManager;

public:
    explicit ChoicePropertiesWidget(StoryManager *storyManager,QWidget *parent = 0);
    ~ChoicePropertiesWidget();

    void showPropertiesOf(Choice *choice);

    IIdValidator *createIdValidator();

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // CHOICEPROPERTIESWIDGET_H
