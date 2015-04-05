#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>

class Choice;
class Situation;
class ChoicePropertiesWidget;
class SituationPropertiesWidget;

class ItemPropertiesWidget : public QWidget
{
    Q_OBJECT

    ChoicePropertiesWidget *m_ChoiceProperties;
    SituationPropertiesWidget *m_SituationProperties;

public:
    explicit ItemPropertiesWidget(QWidget *parent = 0);
    ~ItemPropertiesWidget();

signals:

public slots:
    void showPropertiesOf(Situation *situation);
    void showPropertiesOf(Choice *choice);
};

#endif // ITEMPROPERTIESWIDGET_H
