#ifndef CONTENTMODELPROPERTIESWIDGET_H
#define CONTENTMODELPROPERTIESWIDGET_H

#include <QWidget>
#include "Model/ContentModelBase.h"

class QLineEdit;
class QTextEdit;
class QGridLayout;


class ContentModelPropertiesWidget : public QWidget
{
    Q_OBJECT

    QLineEdit *m_IdEdit;
    QTextEdit *m_ContentEdit;

public:
    explicit ContentModelPropertiesWidget(QWidget *parent = 0);
    virtual ~ContentModelPropertiesWidget();

protected:
    void connectIdAndContentProperties(ContentModelBase *entity);
    void disconnectIdAndContentProperties(ContentModelBase *entity);
    void addIdEditToLayout(QGridLayout *layout, int row);
    void addContentEditToLayout(QGridLayout *layout, int row);

signals:
    void contentEditTextChanged(const QString &);

public slots:
    void contentEditTextChanged();
};

#endif // CONTENTMODELPROPERTIESWIDGET_H
