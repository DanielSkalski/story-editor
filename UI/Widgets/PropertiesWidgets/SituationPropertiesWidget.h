#ifndef SITUATIONPROPERTIESWIDGET_H
#define SITUATIONPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class QLineEdit;
class Situation;
class StoryManager;

class SituationPropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    QLineEdit *m_TitleEdit;

    Situation *m_CurrentItem;
    StoryManager *m_StoryManager;

public:
    explicit SituationPropertiesWidget(StoryManager *storyManager, QWidget *parent = 0);
    ~SituationPropertiesWidget();

    void showPropertiesOf(Situation *situation);

protected:
    IIdValidator *createIdValidator();

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // SITUATIONPROPERTIESWIDGET_H
