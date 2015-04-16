#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>

class Choice;
class Situation;
class StoryManager;
class ContentModelPropertiesWidget;
class ChoicePropertiesWidget;
class SituationPropertiesWidget;

class ItemPropertiesWidget : public QWidget
{
    Q_OBJECT

    StoryManager *m_StoryManager;

    ChoicePropertiesWidget *m_ChoiceProperties;
    SituationPropertiesWidget *m_SituationProperties;

    ContentModelPropertiesWidget *m_Current;

public:
    explicit ItemPropertiesWidget(StoryManager *storyManager, QWidget *parent = 0);
    ~ItemPropertiesWidget();

private:
    void switchCurrentTo(ContentModelPropertiesWidget *);

signals:

public slots:
    void showPropertiesOf(Situation *situation);
    void showPropertiesOf(Choice *choice);
};

#endif // ITEMPROPERTIESWIDGET_H
