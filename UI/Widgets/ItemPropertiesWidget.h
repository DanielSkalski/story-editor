#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>

class QTextEdit;
class QLineEdit;
class Situation;
class Choice;
class ContentModelBase;

class ItemPropertiesWidget : public QWidget
{
    Q_OBJECT

    QLineEdit *m_IdEdit;
    QTextEdit *m_ContentEdit;
    QLineEdit *m_TitleEdit;

    ContentModelBase *m_CurrentItem;

public:
    explicit ItemPropertiesWidget(QWidget *parent = 0);
    ~ItemPropertiesWidget();

signals:

public slots:
    void showPropertiesOf(Situation *situation);
    void showPropertiesOf(Choice *choice);

private:
    void disconnectCurrentItem();
    void connectIdAndContentProperties();
};

#endif // ITEMPROPERTIESWIDGET_H
