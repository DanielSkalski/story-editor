#ifndef SITUATIONPROPERTIESWIDGET_H
#define SITUATIONPROPERTIESWIDGET_H

#include "ContentModelPropertiesWidget.h"

class QLineEdit;
class Situation;

class SituationPropertiesWidget : public ContentModelPropertiesWidget
{
    Q_OBJECT

    QLineEdit *m_TitleEdit;

    Situation *m_CurrentItem;

public:
    explicit SituationPropertiesWidget(QWidget *parent = 0);
    ~SituationPropertiesWidget();

    void showPropertiesOf(Situation *situation);

private:
    void setupLayout();
    void disconnectCurrentItem();

signals:

public slots:
};

#endif // SITUATIONPROPERTIESWIDGET_H
