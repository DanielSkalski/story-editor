#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>

class Situation;

class ItemPropertiesWidget : public QWidget
{
    Q_OBJECT

    QLineEdit *m_IdEdit;
    QTextEdit *m_ContentEdit;
    QLineEdit *m_TitleEdit;

public:
    explicit ItemPropertiesWidget(QWidget *parent = 0);
    ~ItemPropertiesWidget();

signals:

public slots:
    void selectedSituationChanged(Situation *situation);
};

#endif // ITEMPROPERTIESWIDGET_H
